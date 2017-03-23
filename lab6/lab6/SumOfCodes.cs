using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab6
{
    static class SumOfCodes
    {
        public static int GetSumOfCodes(string some_string)
        {
            if(some_string == null)
            {
                return -1;
            }
            uint sum = 0;
            for(int i = 0; i < some_string.Length; i++)
            {
                sum += (uint)some_string[i];
            }

            return (int)sum;
        }

        public static bool EvenSum(string some_string)
        {
            
                if(GetSumOfCodes(some_string) % 2 == 0)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            
        }
    }
}
