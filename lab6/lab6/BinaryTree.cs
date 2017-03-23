using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace lab6
{
   
    internal class Node
    {


        public string Info { get; set; }
        public Node LeftChild;//{ get; set;}
        public Node RightChild;//{ get; set; }
        private int _sum_codes;
        public int SumCodes
        {
            get
            {
                return _sum_codes;
            }
        }
        public bool IsLeaf
        {
            get
            {
                if(LeftChild == null && RightChild == null)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
      
        

        public Node(string s)
        {
            LeftChild = null;
            RightChild = null;
            Info = s;
            _sum_codes = SumOfCodes.GetSumOfCodes(s);

        }

       
    }

    public class BinaryTree
    {
        private Node _root;
              

        internal Node Root
        {
            get
            {
                return _root;
            }
        }

        
        public BinaryTree()
        {
            _root = new Node(Console.ReadLine());
            Console.WriteLine("\npress any key\n");
            Console.ReadKey();
            Console.Clear();
            CreateTree();
              
        }

        private void CreateTree()
        {
            bool WantContinue = true;
            Console.WriteLine("if you want to add a new element enter \"true\" else enter \"false\"\n");
            Input.InputValidated<bool>(ref WantContinue);
            while(WantContinue)
            {
                Add(Console.ReadLine());
                Console.WriteLine("\npress any key\n");
                Console.ReadKey();
                Console.Clear();
                Console.WriteLine("if you want to add a new element enter \"true\" else enter \"false\"");
                Input.InputValidated<bool>(ref WantContinue);
            }
        }
        
                

        private Node GetNode(Node node1, string s )
        {
            Node temp = null;
            if (node1 != null)
            {
                if (node1.Info == s)
                {
                    temp = node1;
                }
                else
                {
                    if (node1.LeftChild != null)
                    {
                        temp = GetNode(node1.LeftChild, s);
                    }
                    if (temp == null)// если не нашли в левой ветке
                    {
                        if (node1.RightChild != null)
                        {
                            temp = GetNode(node1.RightChild, s);
                        }
                    }
                }
            }
            else
            {
                return null;
            }

            return temp;
        }



        public string this[string s]
        { 
           
            set
            {
                Node temp = GetNode(_root, s);
                if (temp != null)
                {
                    temp.Info = value;
                }
            }

        }

        private void PrintNodeInfo(Node node1)
        {
            Console.WriteLine(node1.Info + "  sum of codes is " + (node1.SumCodes).ToString() + "\n");
        }

        
        internal void Add(Node node1, string s)
        {

            if(SumOfCodes.GetSumOfCodes(s) <= node1.SumCodes )
            {
                if (node1.LeftChild == null)
                {
                    node1.LeftChild = new Node(s);
                }
                else
                {
                    Add(node1.LeftChild, s);
                }
            }
            else
            {
                if(node1.RightChild == null)
                {
                    node1.RightChild = new Node(s);
                }
                else
                {
                    Add(node1.RightChild, s);
                }
            }

        }

       

      

        public  bool  Delete(string s)
        { 
            if(_root == null)
            {
                return false;
            }
            TypedReference NodePtr = __makeref(_root);
            int SumCodesForS = SumOfCodes.GetSumOfCodes(s);
            while (__refvalue(NodePtr, Node).Info != s)
            {
                if (SumCodesForS <= __refvalue(NodePtr, Node).SumCodes && __refvalue(NodePtr, Node).Info != s)
                {
                    NodePtr = __makeref(__refvalue(NodePtr, Node).LeftChild);
                }
                else
                {  
                     NodePtr = __makeref(__refvalue(NodePtr, Node).RightChild);
                }

                if (__refvalue(NodePtr, Node) == null)
                {
                    return false;
                }
            }
            Node CopyOfNeededNode = __refvalue(NodePtr, Node);
           
            if(CopyOfNeededNode.IsLeaf)
            {
                __refvalue(NodePtr, Node) = null;
                return true;
            }

            TypedReference ChangeToPtr;
            if (CopyOfNeededNode.LeftChild != null)
            {
                ChangeToPtr = __makeref(__refvalue(NodePtr, Node).LeftChild);
                while (__refvalue(ChangeToPtr, Node).RightChild != null)
                {
                    ChangeToPtr = __makeref(__refvalue(ChangeToPtr, Node).RightChild);
                }
            }

            else
            {
                ChangeToPtr = __makeref(__refvalue(NodePtr, Node).RightChild);
                while (__refvalue(ChangeToPtr, Node).LeftChild != null)
                {
                    ChangeToPtr = __makeref(__refvalue(ChangeToPtr, Node).LeftChild);
                }
            }

            string temp = __refvalue(ChangeToPtr, Node).Info;
            __refvalue(NodePtr, Node).Info = __refvalue(ChangeToPtr, Node).Info;
            __refvalue(ChangeToPtr, Node).Info = temp;
            __refvalue(ChangeToPtr, Node) = null;

            return true;



        }

        

        public void Add(string s)
        {
            if (_root == null)
            {
                _root = new Node(s);
            }
            else
            {
                Add(_root, s);
            }
        }

        internal delegate void function(Node node1);

        internal void DoSomethingWithNodes(Node node1, function f )
        {
            if(node1 != null)
            {
                f.Invoke(node1);
                if(node1.LeftChild != null)
                {
                    DoSomethingWithNodes(node1.LeftChild, f);
                }
                if(node1.RightChild != null)
                {
                    DoSomethingWithNodes(node1.RightChild,f );
                }
            }
        }

        public void PrintElements()
        {
            Console.WriteLine("\n\nelements of the tree are\n\n");
            function f = PrintNodeInfo;
            DoSomethingWithNodes(_root, f);
            Console.WriteLine("\n");
        }

        public void MakeAList(MyList some_list)
        {

            function f = some_list.Push;
            DoSomethingWithNodes(_root, f);
            Console.WriteLine("\n\n");

        }

       

       


    }
}
