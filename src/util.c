
#include <stdio.h>
#include <stdlib.h>

#include "util.h"

size_t one_bits(size_t val) {
  size_t res = 0;
  while (val) {
      val &= (val - 1);
      res++;
  }
  return res;
}

size_t binom(size_t n, size_t k) {
  if (k < 0 || k > n)
    return 0;
  if (k > n - k)
    k = n - k;
  size_t res = 1;
  for (size_t i = 0; i < k; ++i) {
    res *= (n - i);
    res /= (i + 1);
  }
  return res;
}