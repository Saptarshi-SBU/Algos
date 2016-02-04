/*--------------------------------------------------------------------

    reverse bits
  
  --------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>

unsigned int reverse(unsigned int n) {
    int i;
    unsigned int k = 0;
    
    for (i = 0; i < sizeof(int)*8; i++) {
      
        if (n & (1 << i))
            k = k | 0x01;
        
        if (i == (sizeof(int)*8 - 1))
             break;
             
        k = k << 1;
    }
    
    return k;
}

void bin(unsigned int n) {
    
    if (!n)
        return;
    
    bin(n/2);
    printf("%u", n % 2);
    return;
}

int main(void) {
    int n = 0x80000000;
    bin(n);
    printf("\n");
    int k = reverse(n);
    bin(k);
    return 0;
}