using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Huffman_archiver
{

    class HuffmanBinaryTree
    {
        private Node _root;

        private Dictionary<byte, Code> _cash = new Dictionary<byte, Code>();
        private Dictionary<Code, byte> _code_dict = new Dictionary<Code, byte>();

        public Dictionary<Code, byte> CodeDict
        {
            get
            {
                return _code_dict;
            }
        }

        public uint MinCodeLength { get; set; }

       

        public Node Root
        {
            get
            {
                return _root;
            }
        }

        private Node CreateTree(Dictionary<byte, long> byte_priorities)
        {
            var nodes = new List<Node>();

            foreach (var kvp in byte_priorities)
            {
                nodes.Add(new Node(kvp.Key, kvp.Value));
            }

            while (nodes.Count > 1)
            {
                nodes.Sort(Node.Compare);

                nodes[0] = new Node(nodes[0], nodes[1]);
                nodes.RemoveAt(1);
            }
            if (nodes.Count == 0)
            {
                return null;
            }
            return nodes[0];
        }

        public HuffmanBinaryTree(Dictionary<byte, long> byte_priorities)
        {
            _root = CreateTree(byte_priorities);
            EncodeTree();
        }

        public Code GetCode(Node node1, byte character)
        {
            if (!_cash.ContainsKey(character))
            {
                Code temp = ReturnCode(node1, character);
                _cash.Add(character, temp);
                _code_dict.Add(temp, character);
                if (temp.BitNumber < MinCodeLength)
                {
                    MinCodeLength = temp.BitNumber;
                }
                return temp;

            }
            else
            {
                return _cash[character];
            }

        }

        private Code ReturnCode(Node node1, byte character)
        {

            Code temp = null;
            if (node1.LeftChild != null)
            {
                temp = ReturnCode(node1.LeftChild, character);
            }
            if (temp == null)
            {
                if (node1.RightChild != null)
                {
                    temp = ReturnCode(node1.RightChild, character);
                }
            }
            if (node1.IsLeaf && node1.Character == character)
            {
                temp = node1.Code;
            }
            return temp;

        }

        private void EncodeTree(Node node1)
        {
            uint next_bit;


            if (node1.IsLeft)
            {
                next_bit = 0;
            }
            else
            {
                next_bit = 1;
            }
            WriteToLeaves(node1, next_bit);
            if (node1.LeftChild != null)
            {
                EncodeTree(node1.LeftChild);
            }
            if (node1.RightChild != null)
            {
                EncodeTree(node1.RightChild);
            }


        }

        private void WriteToLeaves(Node node1, uint Bit)
        {
            if (node1.IsLeaf)
            {
                node1.Code.Number = node1.Code.Number * 2 + Bit;
                node1.Code.BitNumber++;
            }
            else
            {
                if (node1.LeftChild != null)
                {
                    WriteToLeaves(node1.LeftChild, Bit);
                }
                if (node1.RightChild != null)
                {
                    WriteToLeaves(node1.RightChild, Bit);
                }

            }
        }

        private void EncodeTree()
        {
            if(Root == null)
            {
                return;
            }
            if (Root.LeftChild != null)
            {
                EncodeTree(Root.LeftChild);
            }
            if (Root.RightChild != null)
            {
                EncodeTree(Root.RightChild);
            }
            if (Root.IsLeaf)
            {
                EncodeTree(Root);
            }
        }



    }
}
