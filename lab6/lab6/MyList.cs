using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab6
{
    internal class NodeOfList
    {
        public string Info { get; set; }
        public NodeOfList Previous { get; set; }
        public NodeOfList Next { get; set; }
        private int _sum_codes;
        public int SumCodes
        {
            get
            {
                return _sum_codes;
            }
        }

        public NodeOfList(string info)
        {
            Previous = null;
            Next = null;
            Info = info;
            _sum_codes = SumOfCodes.GetSumOfCodes(info);
        }

    }

    public class MyList
    {
        private NodeOfList _start;
        private int _length;

      

        public int Length
        {
            get
            {
                return _length;
            }
        }

        private NodeOfList GetNodeOfList(int index)
        {

            if (index < 0 || index > Length - 1)
            {
                throw new Exception("Index in list is out of range");
            }
            NodeOfList slider = _start;
            for (int i = 1; i <= index; i++)
            {
                slider = slider.Next;
            }

            return slider;
        }

        private NodeOfList GetNodeOfList(string s)
        {
            
            NodeOfList slider = _start;
            for (int i = 1; i <= _length; i++)
            {
                if(slider.Info == s)
                {
                    return slider;
                }
                slider = slider.Next;
            }

            return null;

        }

        public string this[string s]
        {


            set
            {

                NodeOfList IndexNodeOfList = GetNodeOfList(s);
                if (IndexNodeOfList != null)
                {
                    IndexNodeOfList.Info = value;
                }

            }
        }

        public void Push(string some_string)
        {
            if (_length == 0)
            {
                _start = new NodeOfList(some_string);
                _length++;
            }
            else
            {
                NodeOfList NewNodeOfList = new NodeOfList(some_string);
                NewNodeOfList.Previous = GetNodeOfList(_length - 1);
                NewNodeOfList.Previous.Next = NewNodeOfList;
                _length++;
            }
        }

        public void Pop()
        {
            if (Length != 0)
            {
                NodeOfList LastNodeOfList = GetNodeOfList(_length - 1);
                if (_length != 1)
                {
                    LastNodeOfList.Previous.Next = null;
                }
               _length--;
            }
        }

        public bool Delete(string s)
        {
            NodeOfList NeededNode = GetNodeOfList(s);
            if(NeededNode == null)
            {
                return false;
            }

            if(NeededNode.Next == null)
            {
                Pop();
            }
            else
            {
                if (NeededNode.Previous != null)
                {
                    NeededNode.Previous.Next = NeededNode.Next;
                }
                else
                {
                    _start = NeededNode.Next;
                }
                NeededNode.Next.Previous = NeededNode.Previous;
                _length--;
                
            }
            return true;

        }

       
        public void Print()
        {
            Console.WriteLine("\nelements of the stack are\n\n");
            NodeOfList slider = _start;
            if(_length == 0)
            {
                Console.WriteLine("\nthe stack is empty\n");
                return;
            }
            for(int i = 0; i < Length; i++)
            {
                Console.WriteLine(slider.Info + " sum of codes is " + slider.SumCodes.ToString() +  "\n");
                slider = slider.Next;
            }
            Console.WriteLine("\n");
          
        }

        public MyList(BinaryTree MyBinaryTree)
        {
            MyBinaryTree.MakeAList(this);
        }

        internal void Push(Node node1)
        {
            if (SumOfCodes.EvenSum(node1.Info))
            {
                this.Push(node1.Info);
            }
        }

        public void AskForAdding()
        {
            Console.WriteLine("\n please enter the string you want to add\n");
            Push(Console.ReadLine());
        }   

        

        public void AskForChanging()
        {
            Console.WriteLine("\nplease enter the string you want to change\n");
            string Changable = Console.ReadLine();
            Console.WriteLine("\nplease enter the new string\n");
            this[Changable] = Console.ReadLine();   
        }

        public void AskForDeleting()
        {
            Console.WriteLine("\nplease enter the string you want to delete\n");
            string StringToDelete = Console.ReadLine();
            if(!Delete(StringToDelete))
            {
                Console.WriteLine("\nthere is no such string in the stack\n");
            }
        }
            

    }       
}

