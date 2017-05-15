using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Huffman_archiver
{

    public class Node
    {



        public Int64 Priority { get; set; }
        public bool IsLeft { get; set; }

        public byte Character { get; set; }
        public Code Code { get; set; }
        public Node LeftChild { get; set; }
        public Node RightChild { get; set; }

        public bool IsLeaf => LeftChild == null && RightChild == null;

        public Node(byte character, Int64 priority) //создаем лист
        {
            Character = character;
            Priority = priority;
            Code = new Code();
        }

        public Node(Node node1, Node node2)
        {
            if (node1.Priority <= node2.Priority)
            {
                LeftChild = node1;
                RightChild = node2;
                node1.IsLeft = true;
                node2.IsLeft = false;
            }
            else
            {
                LeftChild = node2;
                RightChild = node1;
                node1.IsLeft = false;
                node2.IsLeft = true;
            }

            Priority = node1.Priority + node2.Priority;
        }


        static public int Compare(Node node1, Node node2)
        {
            if (node1.Priority > node2.Priority)
            {
                return 1;
            }
            else
            {
                if (node1.Priority < node2.Priority)
                {
                    return -1;
                }
                else
                {
                    return 0;
                }
            }
        }


    }
}
