using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab5
{
    public class MyList
    {
        protected Node _start;
        protected int _length;

        public Node Start
        {
            get
            {
                return _start;
            }
        }

        public int Length
        {
            get
            {
                return _length;
            }
        }

        protected Node GetNode(int index)
        {
           
            if (index < 0 || index > Length - 1 )
            {
                throw new Exception("Index in list is out of range");
            }
            Node slider = _start;
            for (int i = 1; i <= index; i++)
            {
                slider = slider.Next;
            }
            
            return slider;
        }

        public int this[int index]
        {

            
            get
            {
                 return GetNode(index).Digit;
            }
            set
            {
                
                Node IndexNode = GetNode(index);
                IndexNode.Digit = value;
                                  
            }
        }

        public void Push (int digit)
        {
            if (_length == 0)
            {
                _start = new Node(digit);
                _length++;
            }
            else
            {
                Node NewNode = new Node(digit);
                NewNode.Previous = GetNode(_length - 1);
                NewNode.Previous.Next = NewNode;
                _length++;
            }
        }

        public void Pop()
        {
            if (Length != 0)
            {
                Node LastNode = GetNode(_length - 1);
                LastNode = null;
                _length--;
            }
        }

        public void InsertToStart(int digit)
        {
            if (_length == 0)
            {
                _start = new Node(digit);
                _length++;
            }
            else
            {
                Node NewNode = new Node(digit);
                NewNode.Next = _start;
                _start.Previous = NewNode;
                _start = NewNode;
                _length++; 
            }
        }

           
    }
}
