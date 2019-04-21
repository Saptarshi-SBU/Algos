/*
 *  A C implementation of radix sort (LSD)
 *
 *  Complexity : Time O(n*k), Space O(n+k)
 *
 *  Copyright(C) 2019 Saptarshi Sen
 *
 *  Date : 04/21/2019
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>

#define BASE_RADIX 10

//#define DEBUG

#ifdef DEBUG
#define dbg_printf(fmt, ...) printf(fmt, __VA_ARGS__);
#else
#define dbg_printf(fmt, ...) do { } while (0);
#endif

long bins[BASE_RADIX];

long nth_digit(long number, int n) {
        int i;

        for (i = 1; i < n; i++)
                number /= BASE_RADIX;

        return number % BASE_RADIX;
}

long n_digits(long number) {
        int d = 0;

        while (number) {
                d++;
                number /= BASE_RADIX;
        }
        return d;
}

int radix_sort(long array[], size_t nr) {
        long i, k, d, p, np, n_max = 0;

        long *reorder_array = (long *) calloc(nr, sizeof(long));
        if (!reorder_array)
                return -ENOMEM;

        // largest number
        for (i = 0; i < nr; i++)
                n_max = n_max < array[i] ? array[i] : n_max;

        np = n_digits(n_max);

        for (p = 1; p <= np; p++) {
                long prev;

                // binning
                for (i = 0; i < nr; i++) {
                        d = nth_digit(array[i], p);
                        assert (d < BASE_RADIX);
                        bins[d] += 1;
                        dbg_printf("binning > bins[%d] :%ld data :%ld\n",
                                   d, bins[d], array[i]);
                }

                // prefix sum
                for (i = 1; i < BASE_RADIX; i++) {
                        bins[i] += bins[i - 1];
                        assert(bins[i] <= nr);
                        dbg_printf ("prefix sum > bins[%d] :%ld\n", i, bins[i]);
                }

                // rebinning
                for (i = 0, prev = 0; i < BASE_RADIX; i++) {
                        long tmp = bins[i];
                        bins[i] = prev;
                        prev = tmp;
                        dbg_printf ("rebinning > bins[%d] :%ld\n", i, bins[i]);
                }

                // reorder
                for (i = 0; i < nr; i++) {
                        d = nth_digit(array[i], p);
                        k = bins[d];
                        reorder_array[k] = array[i];
                        dbg_printf ("reordering > bin[%d] :%d buf index :%d data :%ld\n",
                                    d, bins[d], k, array[i]);
                        bins[d] = bins[d] + 1;
                }

                memset((char *) bins, 0, sizeof(long) * BASE_RADIX);

                memcpy((char *)array, (char *)reorder_array, nr * sizeof(long));
                for(i = 0; i < nr; i++)
                        dbg_printf("round %d > [%d] %ld\n", p, i, array[i]);
     }

     free(reorder_array);

     for (i = 0; i < nr; i++)
          printf("round %d\t\t[%d]\t\t%ld\n", p, i, array[i]);

     return 0;
}

int main(int argc, char *argv[]) {
        size_t i, nr_max;

        if (argc < 2)
                return -EINVAL;

        nr_max = atol(argv[1]);

        srand(time(NULL));

        long *arrayp = malloc(sizeof(long) * nr_max);
        if (!arrayp)
                return -ENOMEM;

        for (i = 0; i < nr_max; i++)
                arrayp[i] = rand();

        radix_sort(arrayp, nr_max);

        free(arrayp);

        return 0;
}
