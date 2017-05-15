using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Huffman_archiver
{
    public enum PathChecking { correct_path, wants_to_skip, restored_the_file };
    public partial class FileNotFoundForm : Form
    {
        public  PathChecking SkipClicked { get; set; }
        public FileNotFoundForm(string message)
        {
            InitializeComponent();
            MessageLabel.Text = message;
            SkipClicked = PathChecking.wants_to_skip;
        }

        private void OKButton_Click(object sender, EventArgs e)
        {
            SkipClicked = PathChecking.restored_the_file;
            this.Close();
        }

        private void SkipButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        
    }
}
