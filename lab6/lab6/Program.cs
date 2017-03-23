using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab6
{
    class Program
    {

        

        

        static void Main(string[] args)
        {
           
            
            Console.WriteLine("please enter your strings");

            BinaryTree MyBinTree = new BinaryTree();
            MyBinTree.PrintElements();

            MyList MyList1 = new MyList(MyBinTree);
            MyList1.Print();

            Console.WriteLine("\npress any key\n");
            Console.ReadKey();
            Console.Clear();

            Ask.AskForChanges(MyBinTree, MyList1);

            Console.WriteLine("\npress any key\n");
            Console.ReadKey();
        }
    }
}
