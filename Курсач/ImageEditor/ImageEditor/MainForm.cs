using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ImageEditor
{
    public partial class MainForm : Form
    {

        public event ImageProcessingEventHandler AdjustmentCall;

        protected virtual void OnAdjustmentCall()
        {
            AdjustmentCall?.Invoke(this, new ImageProcessingEventArgs(workingCopy));
        }

        public delegate void CustomFilterEventHandler(object sender, CustomFilterEventArgs e);

        public event CustomFilterEventHandler CustomFilterCall;

        protected virtual void OnCustomFilterCall(CustomFilter filter, CustomFilterAdjustment adjustment)
        {
            CustomFilterCall?.Invoke(this, new CustomFilterEventArgs(workingCopy, adjustment, filter));
        }


        public delegate void FilterEventHandler(object sender, FilterEventArgs e);

        public event FilterEventHandler FilterCall;

        protected virtual void OnFilterCall(ConvolutionMatrix filterKernel)
        {
            FilterCall?.Invoke(this, new FilterEventArgs(workingCopy, filterKernel));
        }


        FileOperations fileOperations;
        Filter filter;
        BrightnessContrastForm brightnessContrastForm;
        ExposureForm exposureForm;
        CustomFilterForm customFilterForm;
        ColorBalanceForm colorBalanceForm;
        ThresholdForm thresholdForm;


        public MainForm()
        {
            InitializeComponent();

            fileOperations = new FileOperations();

            fileOperations.FileOpened += ReceiveImage;

            filter = new ImageEditor.Filter();
            this.FilterCall += filter.ApplyFilter;

            filter.ProcessingCompleted += ViewProcessedImage;
            filter.ProcessingCompleted += ApproveProcessing;
            brightnessContrastForm = new BrightnessContrastForm();

            this.AdjustmentCall += brightnessContrastForm.SetInputImage;

            brightnessContrastForm.ProcessingApproved += ApproveProcessing;
            brightnessContrastForm.ProcessingCanceled += CancelProcessing;
            brightnessContrastForm.ProcessingCompleted += ViewProcessedImage;
 
            colorBalanceForm = new ColorBalanceForm();
            this.AdjustmentCall += colorBalanceForm.SetInputImage;

            colorBalanceForm.ProcessingApproved += ApproveProcessing;
            colorBalanceForm.ProcessingCanceled += CancelProcessing;
            colorBalanceForm.ProcessingCompleted += ViewProcessedImage;

            thresholdForm = new ThresholdForm();
            this.AdjustmentCall += thresholdForm.SetInputImage;

            thresholdForm.ProcessingApproved += ApproveProcessing;
            thresholdForm.ProcessingCanceled += CancelProcessing;
            thresholdForm.ProcessingCompleted += ViewProcessedImage;

            customFilterForm = new CustomFilterForm();
            this.CustomFilterCall += customFilterForm.SetInputImage;

            customFilterForm.ProcessingApproved += ApproveProcessing;
            customFilterForm.ProcessingCanceled += CancelProcessing;
            customFilterForm.ProcessingCompleted += ViewProcessedImage;

            exposureForm = new ExposureForm();
            this.AdjustmentCall += exposureForm.SetInputImage;

            exposureForm.ProcessingApproved += ApproveProcessing;
            exposureForm.ProcessingCanceled += CancelProcessing;
            exposureForm.ProcessingCompleted += ViewProcessedImage;
        }


        private void MainForm_Load(object sender, EventArgs e)
        {
            DisableButtons();
        }

        private Bitmap original;
        private Bitmap workingCopy;
        private Bitmap backup;

        private void BackUpWorkingCopy()
        {
            backup = (Bitmap)workingCopy.Clone();
        }

        private void RestoreBackupWorkingCopy()
        {
            workingCopy = (Bitmap)backup.Clone();
        }

        private void ReceiveImage(object sender, FileOperations.OpenEventArgs e)
        {
            if (e.Input == null)
                return; 

            original = e.Input;
            workingCopy = new Bitmap(original);
            backup = new Bitmap(original);
            EnableButtons();       
        }

        private void EnableButtons()
        {
            this.adjustmentsToolStripMenuItem.Enabled = true;
            this.imageToolStripMenuItem.Enabled = true;
            this.filterToolStripMenuItem.Enabled = true;
            this.photoFilterToolStripMenuItem.Enabled = true;
            this.saveAsToolStripMenuItem.Enabled = true;
            this.closeToolStripMenuItem.Enabled = true;
        }

        private void DisableButtons()
        {
            this.adjustmentsToolStripMenuItem.Enabled = false;
            this.imageToolStripMenuItem.Enabled = false;
            this.filterToolStripMenuItem.Enabled = false;
            this.photoFilterToolStripMenuItem.Enabled = false;
            this.saveAsToolStripMenuItem.Enabled = false;
            this.closeToolStripMenuItem.Enabled = false;
        }

        private void ViewOriginalImage()
        {
            pictureBox.Image = original;
        }

        private void ViewProcessedImage(object sender, ImageProcessingEventArgs e)
        {
            pictureBox.Image = e.Image;
        }

        private void ViewWorkingCopy()
        {
            pictureBox.Image = workingCopy;
        }

        private void ApproveProcessing(object sender, ImageProcessingEventArgs e)
        {
            workingCopy = (Bitmap)pictureBox.Image;
        }

        private void CancelProcessing(object sender, ImageProcessingEventArgs e)
        {
            pictureBox.Image = workingCopy;
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            fileOperations.OpenImageFile();
            ViewOriginalImage();
        }

        private void brightnessContrastToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BackUpWorkingCopy();
            OnAdjustmentCall();
            brightnessContrastForm.ShowDialog();
        }

        

        private void colorBalanceToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BackUpWorkingCopy();
            OnAdjustmentCall();
            colorBalanceForm.ShowDialog();
        }

        private void erosionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BackUpWorkingCopy();

            CustomFilter customFilter = new CustomFilter();
            CustomFilterAdjustment adjustment = new CustomFilterAdjustment(customFilter.Erosion);

            OnCustomFilterCall(customFilter, adjustment);

            customFilterForm.ShowDialog();
        }

        private void dilutionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BackUpWorkingCopy();

            CustomFilter customFilter = new CustomFilter();
            CustomFilterAdjustment adjustment = new CustomFilterAdjustment(customFilter.Dilution);

            OnCustomFilterCall(customFilter, adjustment);

            customFilterForm.ShowDialog();
        }

        private void invertToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BackUpWorkingCopy();
            Adjustments adjustment = new ImageEditor.Adjustments();
            adjustment.Invert(workingCopy, 0);
            ViewWorkingCopy();
        }

        private void sepiaToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BackUpWorkingCopy();
            Adjustments adjustment = new ImageEditor.Adjustments();
            adjustment.Sepia(workingCopy, 0);
            ViewWorkingCopy();
        }

        private void blackAndWhiteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BackUpWorkingCopy();
            Adjustments adjustment = new ImageEditor.Adjustments();
            adjustment.BlackAndWhite(workingCopy, 0);
            ViewWorkingCopy();
        }

        private void thresholdToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BackUpWorkingCopy();
            OnAdjustmentCall();
            thresholdForm.ShowDialog();
        }

        private void exposureToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BackUpWorkingCopy();
            OnAdjustmentCall();
            exposureForm.ShowDialog();
        }

        private void sharpenToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            backup = workingCopy;
            OnFilterCall(Filter.LightSharpenMatrix());
        }

        private void sharpenMoreToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BackUpWorkingCopy();
            OnFilterCall(Filter.SharpenMatrix());
        }

        private void unsharpMaskToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BackUpWorkingCopy();
            OnFilterCall(Filter.UnsharpMasking());
        }

        private void boxBlurToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BackUpWorkingCopy();
            OnFilterCall(Filter.BoxBlur());
        }

        private void gaussianBlurToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BackUpWorkingCopy();
            OnFilterCall(Filter.GaussianBlur());
        }

        private void edgeDetectionToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BackUpWorkingCopy();
            OnFilterCall(Filter.EdgeDetection());
        }

        
        private void undoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            RestoreBackupWorkingCopy();
            ViewWorkingCopy();
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            fileOperations.SaveImageFileAs(workingCopy);
        }

        private void exitToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void closeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            pictureBox.Image = pictureBox.ErrorImage;
            DisableButtons();
        }

        private void averageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BackUpWorkingCopy();

            CustomFilter customFilter = new CustomFilter();
            CustomFilterAdjustment adjustment = new CustomFilterAdjustment(customFilter.Blur);

            OnCustomFilterCall(customFilter, adjustment);

            customFilterForm.ShowDialog();
        }
    }
    
}
