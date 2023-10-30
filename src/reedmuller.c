#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "reedmuller.h"
#include "util.h"
#include "vector.h"

size_t RM_dim(size_t r, size_t m) {
  size_t res = 1;
  for (size_t i = 1; i <= r; ++i)
    res += binom(m, i);
  return res; 
}

RM *RM_new(size_t r, size_t m) {
  RM *rm = (RM *)malloc(sizeof(*rm));
  rm->r = r;
  rm->m = m;
  rm->n = (1 << m);
  rm->k = RM_dim(r, m);
  rm->G = RM_generator_matrix(rm);
  return rm;
}

void RM_delete(RM *rm) {
  matrix_delete(rm->G);
  free(rm);
}

matrix *RM_generator_matrix(RM *rm) {
  matrix *base = base_matrix(rm->m);
  matrix *gen = matrix_new(rm->k);
  for (size_t i = 0; i <= rm->r; ++i) {
    for (size_t j = 0; j < rm->n; ++j) {
      if (i == one_bits(j)) {
        vector *v = ones(rm->n);
        for (size_t k = 0; k < rm->m; ++k) {
          if (j & (1 << k)) {
            vector *tmp = v;
            v = vector_mult(tmp, base->rows[k]);
            vector_delete(tmp);
          }
        }
        matrix_push_back(gen, v);
      }
    }
  }
  matrix_delete(base);
  return gen;
}

size_t RM_str(RM *rm) {
  return ((1 << (rm->m - rm->r - 1)) - 1);
}

vector *RM_split(RM *rm) {
  vector *v = vector_new(rm->r + 1);
  vector_push_back(v, 0);
  for (size_t i = 1; i <= rm->r; ++i)
    vector_push_back(v, v->data[i - 1] + binom(rm->m, i));
  return v;
}

int main() {
  RM *rm = RM_new(2, 4);
  matrix_print(rm->G);
  vector *v = RM_split(rm);
  vector_print(v);
  RM_delete(rm);
  vector_delete(v);
  return 0;
}