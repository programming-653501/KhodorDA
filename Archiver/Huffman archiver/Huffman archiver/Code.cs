using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Huffman_archiver
{
    [Serializable]
    public class Code
    {
        public uint Number { get; set; }
        public uint BitNumber { get; set; }
        public Code()
        {
            Number = 0;
            BitNumber = 0;
        }

        public Code(uint code, uint bit_number)
        {
            Number = code;
            BitNumber = bit_number;
        }

        public override bool Equals(Object code2)
        {
            Code CodeObj = code2 as Code;
            return (Number == CodeObj.Number) && (BitNumber == CodeObj.BitNumber);
        }

        public override int GetHashCode()
        {
            return Number.GetHashCode();
        }

    }
}
