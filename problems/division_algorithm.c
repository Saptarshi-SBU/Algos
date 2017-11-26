/*-------------------------------------------------------------------------------
 *  Safe division : This program divides two integers without using
 *  multiplication, division and mod operator. Includes overflow checks
 *  during division. Returns INT_MAX on overflow
 *
 *  Algorithm :
 *
 *    +) Division by subtraction O(N)
 *    +) Long Division O(nr of bits) = O(1)
 *
 *  Division Overflow :
 *
 *    The 2's complement of INT_MIN cannot be performed as there are no
 *    more bits in an integer . Therefore, when we divide INT_MIN by -1,
 *    this causes overflow.
 *
 * Note :
 * https://www.gnu.org/software/libc/manual/html_node/Absolute-Value.html
 * Most computers use a two’s complement integer representation, in which the
 * absolute value of INT_MIN (the smallest possible int) cannot be represented;
 * thus, abs (INT_MIN) is not defined.
 * ----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <limits.h>

//#define DEBUG

// overflow conditions while division
bool
check_overflow(int dividend, int divisor) {
   if (divisor == 0) {
       goto overflow;
   }
   if ((dividend == INT_MIN) && (divisor == -1)) {
       goto overflow;
   }
   return false;

overflow:
   return true;
}

//O(n)
int
divide_by_subtraction(int dividend, int divisor) {
   int q = 0;
   if (check_overflow(dividend, divisor)) {
       return INT_MAX;
   }
   while ((dividend -= divisor) >= 0) q++;
   return q;
}

// O(1)
int
long_division(int dividend, int divisor) {
   int sign  = 0;
   int shift = 0;
   int cur_result = 0;

   if (check_overflow(dividend, divisor)) {
       return INT_MAX;
   }

   // cases when result will be < 0
   if (((dividend >= 0) && (divisor < 0)) ||
       ((dividend < 0) && (divisor > 0))) {
       sign = 1;
   }

   //using 'long' to prevent overflows due to bitshift.
   //This takes care of a case where dividend is INT_MAX/INT_MIN
   long pdividend = labs((long)dividend);
   long pdivisor  = labs((long)divisor);

   //Left-shift to inflate divisor
   while (pdividend >= pdivisor) {
       // inflate divisor
       shift++;
       pdivisor <<= 1;
   }

   assert(pdivisor);

   //align divisor to dividend
   if (shift) {
      shift -= 1;
      pdivisor >>= 1;
   }

   //Perform binary division by long method
   while (shift >= 0 && pdividend) {
#     ifdef DEBUG
      printf ("N : 0x%08x D :0x%08x Bit :0x%08x\n",
         pdividend, pdivisor, shift);
#     endif
      if (pdividend >= pdivisor) {
          pdividend -= pdivisor;
          // cur_result holds the bit positions
          // coef for the binary polynomial
          cur_result |= (1 << shift);
      }
      //deflate divisor
      pdivisor >>= 1;
      //quoitent's next bit position
      shift--;
#     ifdef DEBUG
      printf ("Q : 0x%08x\n", cur_result);
#     endif
   }
   return sign == 0 ? cur_result : -cur_result;
}

int main(void) {
#  if DEBUG
   int x = 0xFFFFFFFF;
   printf ("min:0x%08x -min:0x%08x max:0x%08x -max:0x%08x -1:%d\n",
      INT_MIN, -INT_MIN, INT_MAX, -INT_MAX, x);
#  endif
   printf("ans :%d\n", long_division(100, 3));
   printf("ans :%d\n", long_division(-INT_MIN, 1));
   return 0;
}
