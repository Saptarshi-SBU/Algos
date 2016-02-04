/*--------------------------------------------------------------------

  multiply 3.5
  
  --------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>

// 3.5 = (8 - 1)/2
int mul() {
    int n = 6;
    n = n * ((1 << 3) - 1);
    n = n >> 1;
	printf("%d\n", n);    
	return 0;
}

int find_rsb(int n) {
    
    if (!n)
        return -1;
        
    int c = -n;
    int r = n & c;
    return log2(r);
}

int next_greater_num(int n) {
    
    int k = find_rsb(n);
    
    if (k < 0)
        return -1;
    
    if (k == sizeof(int) - 1)
        return -1;
        
    int p = find_rsb(~(n >> k)) + k;
            
    //printf("%d\n", k);
    //printf("%d\n", p);
    
    n = n & ~(1 << k);
    n = n |  (1 << p);
    return n;
 
}

int count_bits(int n) {
    
    int c = 0;
    while(n) {
            c = c + 1;
            n = n & (n - 1);
    } 
    return c;
    
}

int count_bits_array(int arr[], size_t size) {
    
    int i;
    int c = 0;
    
    for (i = 0; i < size; i++)
        c =  c + count_bits(arr[i]);
    
    return c;
}

int smallest3(int x, int y, int z) {
    
    int n1 = x;
    int n2 = y;
    int n3 = z;
    
    while (n1 || n2 || n3) {
        
            if (!n1)
                return x;
            else if (!n2)
                return y;
            else if (!n3)
                return z;
        
            n1 = n1 >> 1;
            n2 = n2 >> 1;
            n3 = n3 >> 1;
    }            
    
    return -1;
}

int swap_bits(int n, int p, int q) {
    
    int p_mask = (1 << p);
    int q_mask = (1 << q);
    
    if (((n & p_mask) && (n & q_mask)) || (!(n & p_mask) && !(n & q_mask)))
        return 0;
    
    if (n & p_mask) {
        n = n & (~p_mask);
        n = n | q_mask;    
    } else {
        n = n & (~q_mask);
        n = n | p_mask;
    }    

    printf("new swapped bits : %d\n",n);
    return 0;
}

void bin(int n) {
    
    if (!n) {
            return;
    }
    bin(n/2);
    printf("%d", n % 2);  
    
}
int main(void) {
    int a[] = {7 , 7};
    printf("%d\n", next_greater_num(5));   
    printf("%d\n", count_bits_array(a, 2));
    printf("%d\n", smallest3(1, 0, 10));
    swap_bits(4, 2, 1);
    bin(6);
    return 0;
}