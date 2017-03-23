using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab6
{
    static class Ask
    {
        private delegate void function();

        public static void AskForChanges(BinaryTree MyBinTree, MyList MyList1)
        {
            bool Change = true;
            Console.WriteLine("\nif you want to change the stack of binary tree enter \"true\" else enter \"false\" \n");
            Input.InputValidated<bool>(ref Change);

            while (Change)
            {
               
                Console.Clear();
                Console.WriteLine("Please, choose the operation\n1.Push an element to the stack\n2.Pop an element from the stack\n3.Change an element of the stack\n4.Delete an element from the stack\n5.Add an element to the tree\n6.Delete an element from the tree\n");
                int TypeOfOperation = 0;
                Input.MyIntParseInterval(ref TypeOfOperation, 1, 6);
                function operation = null; ;
                switch(TypeOfOperation)
                {
                    case 1:
                        {
                            operation = MyList1.AskForAdding;
                            break;
                        }
                    case 2:
                        {
                            operation = MyList1.Pop;
                            break;
                        }
                    case 3:
                        {
                            operation = MyList1.AskForChanging;
                            break;
                        }
                    case 4:
                        {
                            operation = MyList1.AskForDeleting;
                            break;
                        }
                    case 5:
                        {
                            Console.WriteLine("\nenter the string you want to add\n");
                            string StringToAdd = Console.ReadLine();
                            MyBinTree.Add(StringToAdd);
                            if(SumOfCodes.EvenSum(StringToAdd))
                            {
                                MyList1.Push(StringToAdd);
                            }

                            break;
                            
                        }
                    case 6:
                        {
                            Console.WriteLine("\nenter the string you want to delete\n");
                            string StringToDelete = Console.ReadLine();
                            if (!MyBinTree.Delete(StringToDelete))
                            {
                                Console.WriteLine("\nthere is no such string in the tree\n");
                                break;
                            }
                            if(SumOfCodes.EvenSum(StringToDelete))
                            {
                                MyList1.Delete(StringToDelete);
                            }
                            break;
                        }

                }

                if(TypeOfOperation != 5 && TypeOfOperation != 6)
                {
                    operation();
                }
                
                MyBinTree.PrintElements();
                Console.WriteLine("\n\n");
                MyList1.Print();
                Console.WriteLine("\n\n");
                Console.WriteLine("\nif you want to continue changing the stack or binary tree enter \"true\" else enter \"false\"\n");
                Input.InputValidated<bool>(ref Change);


            }
        }
    }
}
