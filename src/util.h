#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>

/**
 * Counts number of 1's in the binary form of number
 * @param val number
 * @return number of set bits
*/
size_t one_bits(size_t val);

/**
 * Computes binomial coefficient
 * @param n 
 * @param k 
 * @return n! / ((n - k)! * k!)
*/
size_t binom(size_t n, size_t k);

#endif // UTIL_H