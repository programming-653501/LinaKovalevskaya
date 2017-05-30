using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace ImageEditor
{
    public class CustomFilter: ImageFilter
    {
        public delegate byte ComputeRgbComponentValue(byte[] neighborhood);

        public new void SetUp(int size)
        {
            base.SetUp(size);
        }

        ComputeRgbComponentValue computeRgbComponentValue;


        protected override byte ComputeNewRgbComponentValue(byte[] neighborhood)
        {
            return computeRgbComponentValue(neighborhood);
        }


        private  byte ApplyDilution(byte[] neighborhood)
        {
            byte minimum = neighborhood[0];

            for (int i = 0; i < neighborhoodSize; ++i)
                if (neighborhood[i] < minimum)
                    minimum = neighborhood[i];

            return minimum;
        }


        private byte ApplyErosion(byte[] neighborhood)
        {
            byte maximum = neighborhood[0];

            for (int i = 0; i < neighborhoodSize; ++i)
                if (neighborhood[i] > maximum)
                    maximum = neighborhood[i];

            return maximum;
        }

        private byte ApplyBlur(byte[] neighborhood)
        {
            int sum = 0;

            for (int i = 0; i < neighborhoodSize; ++i)
                sum += neighborhood[i];

            return RgbComponentOperations.ControlOverflow(sum/neighborhoodSize);
        }


        public Bitmap Erosion(Bitmap input)
        {
            computeRgbComponentValue = new ComputeRgbComponentValue(ApplyErosion);
            Bitmap output = new Bitmap(input.Width, input.Height);
            Apply(input, output);
            return output;
        }


        public Bitmap Dilution(Bitmap input)
        {
            computeRgbComponentValue = new ComputeRgbComponentValue(ApplyDilution);
            Bitmap output = new Bitmap(input.Width, input.Height);
            Apply(input, output);
            return output;
        }

        public Bitmap Blur(Bitmap input)
        {
            computeRgbComponentValue = new ComputeRgbComponentValue(ApplyBlur);
            Bitmap output = new Bitmap(input.Width, input.Height);
            Apply(input, output);
            return output;
        }
    }
}
