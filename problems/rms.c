/*--------------------------------------------------------------------

  clear right most bit set
  
  --------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>

int find_rset(int n) {
    
    int count = -1;
    while (n) {
            count+=1;        
            if (n & 0x01)
                break;
            n>>=1;
    }
    return count;    
    
}

int find_rset_fast(int n) {
    
        if (!n)
                return -1;
                
        n = n & (-n);
        return log2(n);
}

int clear_rm(int n) {
    
        int k = find_rset_fast(n);
        if (k < 0) 
            return k;
        
        return (n & ~(1U << k));
}

int main() {
    
	printf("%d\n", clear_rm(5));    
	return 0;
}
