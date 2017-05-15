namespace Huffman_archiver
{
    partial class ArchiveForm
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.CancelButton = new System.Windows.Forms.Button();
            this.OKButton = new System.Windows.Forms.Button();
            this.EntireProgressBar = new System.Windows.Forms.ProgressBar();
            this.PartialProgressBar = new System.Windows.Forms.ProgressBar();
            this.CurrentFilePathLabel = new System.Windows.Forms.Label();
            this.TypeComboBox = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // CancelButton
            // 
            this.CancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.CancelButton.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.CancelButton.Location = new System.Drawing.Point(268, 125);
            this.CancelButton.Name = "CancelButton";
            this.CancelButton.Size = new System.Drawing.Size(119, 23);
            this.CancelButton.TabIndex = 23;
            this.CancelButton.Text = "Cancel";
            this.CancelButton.UseVisualStyleBackColor = true;
            this.CancelButton.Click += new System.EventHandler(this.CancelButton_Click);
            // 
            // OKButton
            // 
            this.OKButton.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.OKButton.Location = new System.Drawing.Point(430, 125);
            this.OKButton.Name = "OKButton";
            this.OKButton.Size = new System.Drawing.Size(119, 23);
            this.OKButton.TabIndex = 22;
            this.OKButton.Text = "OK";
            this.OKButton.UseVisualStyleBackColor = true;
            this.OKButton.Click += new System.EventHandler(this.OKButton_Click);
            // 
            // EntireProgressBar
            // 
            this.EntireProgressBar.ForeColor = System.Drawing.Color.Lime;
            this.EntireProgressBar.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.EntireProgressBar.Location = new System.Drawing.Point(21, 93);
            this.EntireProgressBar.Name = "EntireProgressBar";
            this.EntireProgressBar.Size = new System.Drawing.Size(376, 10);
            this.EntireProgressBar.TabIndex = 20;
            // 
            // PartialProgressBar
            // 
            this.PartialProgressBar.Location = new System.Drawing.Point(21, 45);
            this.PartialProgressBar.Name = "PartialProgressBar";
            this.PartialProgressBar.Size = new System.Drawing.Size(376, 10);
            this.PartialProgressBar.TabIndex = 24;
            // 
            // CurrentFilePathLabel
            // 
            this.CurrentFilePathLabel.AutoSize = true;
            this.CurrentFilePathLabel.Location = new System.Drawing.Point(19, 9);
            this.CurrentFilePathLabel.Name = "CurrentFilePathLabel";
            this.CurrentFilePathLabel.Size = new System.Drawing.Size(0, 13);
            this.CurrentFilePathLabel.TabIndex = 29;
            // 
            // TypeComboBox
            // 
            this.TypeComboBox.AutoCompleteCustomSource.AddRange(new string[] {
            "Add to archive",
            "Derive from archive"});
            this.TypeComboBox.Items.AddRange(new object[] {
            "Add to archive",
            "Derive from archive"});
            this.TypeComboBox.Location = new System.Drawing.Point(430, 45);
            this.TypeComboBox.Name = "TypeComboBox";
            this.TypeComboBox.Size = new System.Drawing.Size(121, 21);
            this.TypeComboBox.TabIndex = 30;
            this.TypeComboBox.SelectedIndexChanged += new System.EventHandler(this.TypeComboBox_SelectedIndexChanged);
            // 
            // ArchiveForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(579, 171);
            this.Controls.Add(this.TypeComboBox);
            this.Controls.Add(this.CurrentFilePathLabel);
            this.Controls.Add(this.PartialProgressBar);
            this.Controls.Add(this.CancelButton);
            this.Controls.Add(this.OKButton);
            this.Controls.Add(this.EntireProgressBar);
            this.Name = "ArchiveForm";
            this.Text = "Archiver";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button CancelButton;
        private System.Windows.Forms.Button OKButton;
        public  System.Windows.Forms.ProgressBar EntireProgressBar;
        public  System.Windows.Forms.ProgressBar PartialProgressBar;
        private System.Windows.Forms.Label CurrentFilePathLabel;
        private System.Windows.Forms.ComboBox TypeComboBox;
    }
}

