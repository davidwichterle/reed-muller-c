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
  rm->G = RM_gen_matrix(rm);
  return rm;
}

void RM_delete(RM *rm) {
  m_delete(rm->G);
  free(rm);
}

matrix *RM_gen_matrix(RM *rm) {
  matrix *base = m_base(rm->m);
  matrix *gen = m_new(rm->k);
  for (size_t i = 0; i <= rm->r; ++i) {
    for (size_t j = 0; j < rm->n; ++j) {
      if (i == one_bits(j)) {
        vector *v = v_ones(rm->n);
        for (size_t k = 0; k < rm->m; ++k) {
          if (j & (1 << k)) {
            vector *tmp = v;
            v = v_mult(tmp, base->rows[k]);
            v_delete(tmp);
          }
        }
        m_push_back(gen, v);
      }
    }
  }
  m_delete(base);
  return gen;
}

size_t RM_str(RM *rm) {
  return ((1 << (rm->m - rm->r - 1)) - 1);
}

vector *RM_split(RM *rm) {
  vector *v = v_new(rm->r + 1);
  v_push_back(v, 0);
  for (size_t i = 1; i <= rm->r; ++i)
    v_push_back(v, v->data[i - 1] + binom(rm->m, i));
  return v;
}

matrix *RM_missing(RM *rm) {
  matrix *m = m_new(rm->k);
  vector *v = v_new(rm->m);
  for (size_t i = 0; i <= rm->r; ++i) {
    for (size_t j = 0; j < rm->n; ++j) {
      if (i == one_bits(j)) {
        v = v_new(rm->m);
        for (size_t k = 0; k < rm->m; ++k) {
          if (!(j & (1 << k)))
            v_push_back(v, k);
        }
        m_push_back(m, v);
      }
    }
  }
  return m;
}

matrix **RM_ml_table(RM *rm) {
  matrix **ml = (matrix **)malloc(rm->k * sizeof(*ml));
  matrix *m = RM_missing(rm);
  for (size_t i = 0; i < rm->k; ++i) {
    matrix *ml_row = m_new(1 << m->rows[i]->size);
    m_push_back(ml_row, v_ones(rm->n));
    for (size_t j = 0; j < m->rows[i]->size; ++j) {
      vector *v = v_base(rm->m, m->rows[i]->data[j]);
      vector *not_v = v_neg(v);
      matrix *ml_row_new = m_new(1 << m->rows[i]->size);
      for (size_t k = 0; k < ml_row->size; ++k) {
        m_push_back(ml_row_new, v_mult(v, ml_row->rows[k]));
        m_push_back(ml_row_new, v_mult(not_v, ml_row->rows[k]));
      }
      matrix *tmp = ml_row;
      ml_row = ml_row_new;
      m_delete(tmp);
    }
    ml[i] = ml_row;
  }
  return ml;
}

int main() {
  RM *rm = RM_new(2, 3);
  m_print(rm->G);
  printf("\n");
  matrix **m = RM_ml_table(rm);
  for (size_t i = 0; i < rm->k; ++i) {
    m_print(m[i]);
    printf("\n");
  }
  RM_delete(rm);
  return 0;
}

// 0000
// 0001
// 0010
// 0011
// 0100
// 0101
// 0110
// 0111
// 1000
// 1001
// 1010
// 1011
// 1100
// 1101
// 1110
// 1111


//          0 1 2 3 
// 0        1 2 3 
// 1        0 2 3
// 2        0 1 3 
// 3        0 1 2 
// 0 1      2 3      
// 0 2      1 3 
// 1 2      0 3 
// 0 3      1 2 
// 1 3      0 2 
// 2 3      0 1 









 

