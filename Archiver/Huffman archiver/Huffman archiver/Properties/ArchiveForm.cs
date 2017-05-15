using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Text.RegularExpressions;
using System.Diagnostics;
using System.IO;
using System.Threading;
using System.Security.AccessControl;
using System.Security.Principal;

namespace Huffman_archiver
{
    public partial class ArchiveForm : Form
    {
        
        private Huffman _encoder_decoder;

        private string _source_file_or_folder_path = null;
        private string _destination_folder_path = null;

        private int _amount_of_files = 0;

        private Task _calculation_task = null;
        private enum TypeOfOperation { encode, decode };
        private TypeOfOperation _type;
        

        private CancellationTokenSource _token_source = null;
        public CancellationToken _canc_token;

        public delegate void Reset(int new_maximum, string current_file_path, ProgressBar progress_bar);
        public delegate void Perform(ProgressBar progress_bar, int step);
        public delegate PathChecking Message(string path, string message);


        public ArchiveForm()
        {

            InitializeComponent();
           
            string[] args = Environment.GetCommandLineArgs();
            _source_file_or_folder_path = args[1];          
            InitializeFormFields();


        }

        private PathChecking ShowFileNotFoundForm(string message)
        {
            FileNotFoundForm message_form = new FileNotFoundForm(message);
            message_form.ShowDialog();

            
            return message_form.SkipClicked;
        }

        private void DeleteFolders()
        {
            if (Directory.Exists(_destination_folder_path))
            {
                Directory.Delete(_destination_folder_path, true);
            }
        }

        public static string SetDestinationFolderPath(string source_path)
        {
            int i = 1;

            while (true)
            {
                
                string destination_path = (source_path + "_" + i.ToString());
                if (Directory.Exists(destination_path))
                {
                    i++;
                }
                else
                {
                    Directory.CreateDirectory(destination_path);
                    return destination_path;
                }
            }
        }

        private void PerformStep(ProgressBar progress_bar, int step)
        {
            try
            {
                progress_bar.Value += step;
            }
            catch
            {
                return;
            }
        }

        private void ResetProgressBar(int new_maximum, string current_file_path, ProgressBar progress_bar)
        {
            progress_bar.Value = 0;
            progress_bar.Maximum = new_maximum;
            CurrentFilePathLabel.Text = current_file_path;
        }

        public Reset ResetProgressBarDelegate { get; private set; }
        public Perform PerformStepDelegate { get; private set; }
        public Message OfferToSkip { get; private set; }

        private Action[] _operations = null;

        private void PerformOperation()
        {
            _encoder_decoder = new Huffman(this);

            try
            {
                _operations[(int)_type]();//массив делегатов, содержащий вызов методов Encode либо Decode объекта класса Huffman
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
                Application.Exit();
            }
            
        }

        private void Encode()
        {
            _encoder_decoder.Encode(_source_file_or_folder_path, "", _destination_folder_path);
        }

        private void Decode()
        {
            _encoder_decoder.Decode(_source_file_or_folder_path, _destination_folder_path);
        }

        private void CountAmountOfFiles()
        {
            if (Directory.Exists(_source_file_or_folder_path))
            {
                _amount_of_files = Directory.GetFiles(_source_file_or_folder_path, "*.*", SearchOption.AllDirectories).Length;
            }
            else
            {
                _amount_of_files = 1;
            }
        }

        public PathChecking CheckIfCorrectPath(string path, string message)
        {
            if (!Directory.Exists(path) && !File.Exists(path))
            {           
                return ShowFileNotFoundForm(message);     
            }
            return PathChecking.correct_path;
               
        }

        private void InitializeFormFields()
        {
            _operations = new Action[2];
            _operations[(int)TypeOfOperation.encode] = Encode;
            _operations[(int)TypeOfOperation.decode] = Decode;

            Application.ApplicationExit += new EventHandler(this.OnApplicationExit);

            _token_source = new CancellationTokenSource();
            _canc_token = _token_source.Token;

            ResetProgressBarDelegate = new Reset(ResetProgressBar);
            PerformStepDelegate = new Perform(PerformStep);
            OfferToSkip = new Message(CheckIfCorrectPath);
            _destination_folder_path = PathFunctions.SetDestinationFolderPath(_source_file_or_folder_path);
        }


        private void OKButton_Click(object sender, EventArgs e)
        {
            PathChecking checked_correctness = CheckIfCorrectPath(_source_file_or_folder_path, "The file " + _source_file_or_folder_path + " was deleted or renamed.\n" + "Please, restore it or skip it's archiving\n");
            if (checked_correctness == PathChecking.correct_path)
            {
                OKButton.Visible = false;
                CountAmountOfFiles();
                
                if(_type == TypeOfOperation.encode)
                {
                    EntireProgressBar.Maximum = _amount_of_files;
                }
                else
                {
                    EntireProgressBar.Maximum = _amount_of_files/2;
                }

                _calculation_task = Task.Factory.StartNew(() => this.PerformOperation(), _token_source.Token).ContinueWith((prev_task) => Application.Exit() );//запускается поток для обработки файлов
            }
            else
            {
                if(checked_correctness == PathChecking.wants_to_skip)
                {
                    Application.Exit();
                }
            }
        }
        

        private void CancelButton_Click(object sender, EventArgs e)
        {            
            Application.Exit();                              
        }

        private void OnApplicationExit(object sender, EventArgs e)
        {
            if (_calculation_task != null)//если обработка файлов уже началась...
            {
                if (!_calculation_task.IsCompleted)//...но еще не закончилась
                {
                    _token_source.Cancel();
                    DeleteFolders();
                }
                else
                {
                    var dir = new DirectoryInfo(_destination_folder_path);
                    dir.Attributes = dir.Attributes & ~FileAttributes.Hidden;
                }
            }
            else
            {
                DeleteFolders();//удаляем все результаты работы
            }
            
        }

        private void TypeComboBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            _type = (TypeOfOperation)TypeComboBox.SelectedIndex;
        }
    }

    public class PathFunctions
    {
        public static string GetParentFolderPath(string source_path)
        {
            Regex file_or_folder_pattern = new Regex(@"([^\\]{1,})$");
            string file_or_folder_name = file_or_folder_pattern.Match(source_path).Value;
            return source_path.Substring(0, source_path.Length - file_or_folder_name.Length - 1);
        }

        public static string SetDestinationFolderPath(string source_path)
        {
            int i = 1;
 
            while(true)
            {
                string destination_path = ( source_path + "_" + i );
                if(Directory.Exists(destination_path))
                {
                    i++;
                }
                else
                {
                    DirectoryInfo dir = Directory.CreateDirectory(destination_path);
                    dir.Attributes = FileAttributes.Directory | FileAttributes.Hidden;
                    return destination_path;
                } 
            }
        }
    }
}
