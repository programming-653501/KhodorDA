using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Huffman_archiver
{
    public static class BitForUint
    {
        public static uint BitsToLeft(this uint number, long number_of_bits)
        {
            return number << (int)number_of_bits;
        }

        public static uint BitsToRight(this uint number, long number_of_bits)
        {
            return number >> (int)number_of_bits;
        }

        public static byte GetBit(this uint number, int index_of_bit)
        {
            var bit = (number & (1 << (31 - index_of_bit))) != 0;
            return bit ? (byte)1 : (byte)0;

        }
    }

    public static class BitForByte
    {
        public static byte GetBit(this byte number, byte index_of_bit)
        {
            var bit = (number & (1 << (7 - index_of_bit))) != 0;
            return bit ? (byte)1 : (byte)0;
        }

    }
}
