using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Huffman_archiver
{
    static class Program
    {
        /// <summary>
        /// Главная точка входа для приложения.
        /// </summary>
        /// 
        
        [STAThread]
        static void Main()
        {
           
             
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            ArchiveForm main_form = new ArchiveForm();          
            Application.Run(main_form);
            
        }
    }
}
