using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab5
{
    public class Node
    {
        public int Digit { get; set;}
        public Node Previous { get; set; }
        public Node Next { get; set; }

        public Node(int digit)
        {
            Digit = digit;
            Previous = null;
            Next = null;
        }

    }
}
