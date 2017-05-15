using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text.RegularExpressions;
using System.Threading;
//using System.Windows.Forms;


namespace Huffman_archiver
{
    [Serializable]
    public class DecodingInfo
    {

        public string PathForDecoded { get; set; }
        public Dictionary<Code, byte> CodeDict { get; set; }
        public UInt64 NumberOfCharacters { get; set; }
        public uint MinCodeLength { get; set; }

        public DecodingInfo()
        {
            CodeDict = new Dictionary<Code, byte>();
        }
     
    }

    class Huffman
    {

        private CancellationToken canc_token;

        private ArchiveForm controller;
        private const int  interval = 300000;
        private const int interval_for_priorities = 3 * interval;

        private void EntirePerformStep(int step) => controller.Invoke(controller.PerformStepDelegate, controller.EntireProgressBar, step);
        private void PartialPerformStep(int step) => controller.Invoke(controller.PerformStepDelegate, controller.PartialProgressBar, step);
        private void ResetPartial(int maximum, string current_file_path) => controller.Invoke(controller.ResetProgressBarDelegate, maximum, current_file_path, controller.PartialProgressBar);

        public Huffman(ArchiveForm form)
        {
            controller = form;
            canc_token = form._canc_token; 
        }

        private Dictionary<byte, long> CountPriorities(byte[] source)
        {
            canc_token.ThrowIfCancellationRequested();
            int processed = 0;

            Dictionary<byte, long> charDictionary = new Dictionary<byte, long>();
            foreach (byte character in source)
            {
                if (!charDictionary.ContainsKey(character))
                {
                    charDictionary.Add(character, 1);
                }
                else
                {
                    charDictionary[character] = charDictionary[character] + 1;
                }

                processed++;

                if (canc_token.IsCancellationRequested)
                {
                    canc_token.ThrowIfCancellationRequested();
                }

                if (processed % interval_for_priorities == 0)
                {
                    PartialPerformStep(1);
                }


            }
            return charDictionary;
        }

       /* private HuffmanBinaryTree CreateTree(Dictionary<byte, long> byte_priorities)
        {
            var nodes = new List<Node>();

            foreach (var kvp in byte_priorities)
            {
                nodes.Add(new Node(kvp.Key, kvp.Value));
            }

            while (nodes.Count > 1)
            {
                nodes.Sort(Node.Compare);

                nodes[0] = new Node(nodes[0], nodes[1]);
                nodes.RemoveAt(1);
            }
            if(nodes.Count == 0)
            {
                return new HuffmanBinaryTree(null);
            }
            return new HuffmanBinaryTree(nodes[0]);
        }*/

        private byte[] FillInByteDestination(byte[] source, HuffmanBinaryTree binaryTree)
        {

            canc_token.ThrowIfCancellationRequested();

            int position = 0;
            Byte temp = 0;
            Code a;
            

            List<byte> destination = new List<byte>();

            int processed = 0;
            foreach (byte character in source)
            {

                a = binaryTree.GetCode(binaryTree.Root, character);




                for (int j = 0; j < a.BitNumber; j++)
                {
                    byte CurrentBit = a.Number.GetBit((int)(32 - a.BitNumber + j));
                    if (position < 8)
                    {
                        temp = (Byte)(temp * 2 + CurrentBit);
                        position++;
                    }
                    if (position == 8)
                    {
                        destination.Add(temp);
                        temp = 0;
                        position = 0;
                    }

                }


                processed = processed + 1;

                if (processed % interval == 0)
                {
                    PartialPerformStep(1);
                }

                if (position != 0 && processed == source.Length)
                {
                    while (position < 8)
                    {
                        temp = (Byte)(temp * 2);
                        position++;
                    }

                    destination.Add(temp);
                }

                if (canc_token.IsCancellationRequested)
                {
                    canc_token.ThrowIfCancellationRequested();
                }

            }

            return destination.ToArray();
        }

        private byte[] DecodeBytes(byte[] source, DecodingInfo dictionary)
        {
            canc_token.ThrowIfCancellationRequested();

            uint processed = 0;
            Code temp_code = new Code();
            uint number_of_bits = 0;
            uint temp_code_value = 0;
            List<byte> destination = new List<byte>();
            byte temp = 0;

            foreach (var @byte in source)
            {
                for (byte i = 0; i < 8; i++)
                {
                    temp_code_value = temp_code_value * 2 + @byte.GetBit(i);
                    number_of_bits++;

                    if (number_of_bits < dictionary.MinCodeLength)
                    {
                        continue;
                    }

                    temp_code.Number = temp_code_value;
                    temp_code.BitNumber = number_of_bits;
                    if (dictionary.CodeDict.TryGetValue(temp_code, out temp))
                    {
                        destination.Add(temp);
                        temp_code_value = 0;
                        number_of_bits = 0;
                        processed++;
                       
                    }

                    if (processed == dictionary.NumberOfCharacters)
                    {
                        return destination.ToArray();
                    }

                    if (canc_token.IsCancellationRequested)
                    {
                        canc_token.ThrowIfCancellationRequested();
                    }

                }

                if (processed % interval == 0)
                {
                    PartialPerformStep(1);
                }
            }


            return destination.ToArray();

        }

        private void EncodeBytes(byte[] source, string dictionary_file_path, string destination_file_path, ref DecodingInfo info)
        {


            var priorities = CountPriorities(source);        
            var binaryTree = new HuffmanBinaryTree(priorities);

           
            byte[] destinationBytes = FillInByteDestination(source, binaryTree);

            File.WriteAllBytes(destination_file_path, destinationBytes);


            info.CodeDict = binaryTree.CodeDict;
            info.MinCodeLength = binaryTree.MinCodeLength;

            IFormatter formatter = new BinaryFormatter();
            Stream DictStream = new FileStream(dictionary_file_path, FileMode.Create, FileAccess.Write, FileShare.None);
            formatter.Serialize(DictStream, info);
            File.SetAttributes(dictionary_file_path, FileAttributes.Hidden);

            DictStream.Close();

        }
        
    

        public void Decode(string source_directory_path, string desination_folder_path)
        {
            canc_token.ThrowIfCancellationRequested();

            string message = "The file " + source_directory_path + " was deleted or renamed.\n" + "Please, restore it or skip it's archiving\n";

            while (true)
            {

                PathChecking checked_correctness = (PathChecking)controller.Invoke(controller.OfferToSkip, source_directory_path, message); //source_file_or_folder_path);
                if (checked_correctness == PathChecking.wants_to_skip)
                {
                    return;
                }
                if (checked_correctness == PathChecking.correct_path)
                {
                    break;
                }
            }

            string[] file_to_decode = null;
            try
            {
                file_to_decode = Directory.GetFiles(source_directory_path, "*.bin");//an array of files because it must contain encoded file and a hidden dictionary
            }
            catch
            {
                throw new Exception("Please,select an archive folder\n");
            }

            while (true)
            {

                if (file_to_decode.Length >= 2)
                {


                    int dictionary_index = 0;


                    Regex dictionary_regex = new Regex(@"(dictionary.bin){1}$");

                    if (dictionary_regex.Match(file_to_decode[1]).Value != "")
                    {
                        dictionary_index = 1;
                    }

                    byte[] source = File.ReadAllBytes(file_to_decode[1 - dictionary_index]);

                    ResetPartial(source.Length / interval + 1, file_to_decode[1 - dictionary_index]);

                    DecodingInfo info = null;
                    try
                    {
                        IFormatter formatter = new BinaryFormatter();
                        Stream DictStream = new FileStream(file_to_decode[dictionary_index], FileMode.Open, FileAccess.Read, FileShare.Read);
                        info = (DecodingInfo)formatter.Deserialize(DictStream);
                        DictStream.Close();
                    }
                    catch
                    {
                        string message2 = "The folder " + source_directory_path + " has been modified and does not contain an archived file\nPlease,restore it or skip it's archiving\n";
                        PathChecking checked_correctness2 = (PathChecking)controller.Invoke(controller.OfferToSkip, source_directory_path, message); //source_file_or_folder_path);
                        if (checked_correctness2 == PathChecking.wants_to_skip)
                        {
                            return;
                        }
                        if (checked_correctness2 == PathChecking.restored_the_file)
                        {
                            continue;
                        }
                    }


                    byte[] destinationBytes = DecodeBytes(source, info);



                    WriteAll(desination_folder_path + info.PathForDecoded, destinationBytes);

                    PartialPerformStep(controller.PartialProgressBar.Maximum - controller.PartialProgressBar.Value);
                    EntirePerformStep(1);
                    return;

                }
                else
                {
                    string[] subdirs = Directory.GetDirectories(source_directory_path);

                    foreach (var subdir in subdirs)
                    {
                        Decode(subdir, desination_folder_path);
                    }

                    return;

                }

            }
        }

       
        private void WriteAll(string file_path, byte[] info)
        {
            string parent_folder = PathFunctions.GetParentFolderPath(file_path);
            CreateAllFolders(parent_folder);
            File.WriteAllBytes(file_path, info);
        }

        private void CreateAllFolders(string folder_path)
        {
            if(!Directory.Exists(folder_path))
            {
                string parent_folder = PathFunctions.GetParentFolderPath(folder_path);
                CreateAllFolders(parent_folder);
                Directory.CreateDirectory(folder_path);
            }
        }

        private string[] SetPathsEncodingFile(string source_file_or_folder_path, string path_for_decoded_folder, string directory_path_for_encoded)//ref string path_for_decoded_file, ref string destination_dicrionary_path, ref string destination_file_path)
        {
            Regex expansion_regex = new Regex(@"(\.{1}[^\\]{1,})$");
            Match expansion = expansion_regex.Match(source_file_or_folder_path);

            Regex regex_safe_file_name = new Regex(@"([^\\]{1,}\.{1}[^\\]{1,})$");
            string safe_file_name = regex_safe_file_name.Match(source_file_or_folder_path).Value;
            string safe_file_name_woexp = safe_file_name.Substring(0, safe_file_name.Length - expansion.Length);

            string path_for_decoded_file = path_for_decoded_folder + "\\" + safe_file_name_woexp + expansion;

            string destination_directory_path = directory_path_for_encoded + "\\" + safe_file_name;
            Directory.CreateDirectory(destination_directory_path);

            string destination_file_path = destination_directory_path + "\\" + safe_file_name_woexp + ".bin";
            string destination_dictionary_path = destination_directory_path + "\\dictionary.bin";

            string[] result = new string[3];
            result[0] = path_for_decoded_file;
            result[1] = destination_dictionary_path;
            result[2] = destination_file_path;

            return result;
        }

        private string[] SetPathsEncodingDirectory(string source_file_or_folder_path, string path_for_decoded_folder, string directory_path_for_encoded)
        {
            Regex current_dir_name_regex = new Regex(@"([^\\]{1,})$");
            string current_dir_name = current_dir_name_regex.Match(source_file_or_folder_path).Value;

            string directory_path_for_decoded = path_for_decoded_folder + "\\" + current_dir_name;

            string new_directory_path_for_encoded = directory_path_for_encoded + "\\" + current_dir_name;
            Directory.CreateDirectory(new_directory_path_for_encoded);

            return new string[] { new_directory_path_for_encoded, directory_path_for_decoded };

        }

        public void Encode(string source_file_or_folder_path, string path_for_decoded_folder, string directory_path_for_encoded)
        {
            canc_token.ThrowIfCancellationRequested();
            string message = "The file " + source_file_or_folder_path + " was deleted or renamed.\n" + "Please, restore it or skip it's archiving\n";

            while (true)
            {

                PathChecking checked_correctness = (PathChecking)controller.Invoke(controller.OfferToSkip, source_file_or_folder_path, message); //source_file_or_folder_path);
                if (checked_correctness == PathChecking.wants_to_skip)
                {
                    return;
                }
                if(checked_correctness == PathChecking.correct_path)
                {
                    break;
                }
            }

            if (!Directory.Exists(source_file_or_folder_path))//if it is not a directory but a file
            {
                byte[] source = File.ReadAllBytes(source_file_or_folder_path);

                string[] paths = SetPathsEncodingFile(source_file_or_folder_path, path_for_decoded_folder, directory_path_for_encoded);

                string path_for_decoded_file = paths[0];
                string destination_dictionary_path = paths[1];
                string destination_file_path = paths[2];

                DecodingInfo info = new DecodingInfo();
                info.PathForDecoded = path_for_decoded_file;

                ResetPartial((int)((source.Length / interval + 1) / 0.75), source_file_or_folder_path);//25 процентов времени занимает подсчет приоритетов, далее progress_bar performstep для каждых interval байтов + 1 если длина файла меньше interval

                info.NumberOfCharacters = (ulong)source.Length;

                EncodeBytes(source, destination_dictionary_path, destination_file_path, ref info);

                PartialPerformStep(controller.PartialProgressBar.Maximum - controller.PartialProgressBar.Value);
               
                EntirePerformStep(1);


            }
            else
            {
                string[] sub_dirs = Directory.GetDirectories(source_file_or_folder_path);
                string[] sub_files = Directory.GetFiles(source_file_or_folder_path);

                List<string> current_folder_content = new List<string>();
                current_folder_content.AddRange(sub_dirs);
                current_folder_content.AddRange(sub_files);

                string[] paths = SetPathsEncodingDirectory(source_file_or_folder_path, path_for_decoded_folder, directory_path_for_encoded);
                string new_directory_path_for_encoded = paths[0];
                string directory_path_for_decoded = paths[1];

                foreach (var sub_path in current_folder_content)
                {
                    Encode(sub_path, directory_path_for_decoded, new_directory_path_for_encoded);
                }

            }
            

        }
    }
}



