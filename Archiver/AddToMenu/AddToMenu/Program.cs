using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Win32;

namespace AddToMenu
{
    class Program
    {
        static void Main(string[] args)
        {
            string MenuName = "Folder\\shell\\NewMenuOption";
            string Command = "Folder\\shell\\NewMenuOption\\command";

            string path;
            Console.WriteLine(@"Please, enter the path of your application, for example E:\folder\MyProgram.exe");
            path = Console.ReadLine();
            string name;
            Console.WriteLine("Enter the name of a new item");
            name = Console.ReadLine();

            for (int i = 0; i < 2; i++)
            {
                RegistryKey regmenu = null;
                RegistryKey regcmd = null;
                try
                {
                    regmenu = Registry.ClassesRoot.CreateSubKey(MenuName);
                    if (regmenu != null)
                    {
                        regmenu.SetValue("", name);
                    }
                    regcmd = Registry.ClassesRoot.CreateSubKey(Command);
                    if (regcmd != null)
                    {
                        regcmd.SetValue("", path + " %1 ");
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.Message);
                    Console.ReadKey();
                    Environment.Exit(1);
                }
                MenuName = "*\\shell\\NewMenuOption";
                Command = "*\\shell\\NewMenuOption\\command";

            }

            Console.WriteLine("Done");
            Console.ReadKey();
        }
    }
}
