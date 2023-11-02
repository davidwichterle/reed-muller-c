#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"
#include "vector.h"
#include "reedmuller.h"
#include "util.h"

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
  rm->G = RM_gen(rm);
  rm->G_T = matrix_transpose(rm->G);
  rm->ml = RM_ml(rm);
  return rm;
}

void RM_delete(RM *rm) {
  matrix_delete(rm->G);
  matrix_delete(rm->G_T);
  for (size_t i = 0; i < rm->k; ++i)
    matrix_delete(rm->ml[i]);
  free(rm->ml);
  free(rm);
}

matrix *RM_gen(RM *rm) {
  matrix *base = matrix_base(rm->m);
  matrix *gen = matrix_new(rm->k);
  for (size_t i = 0; i <= rm->r; ++i) {
    for (size_t j = 0; j < rm->n; ++j) {
      if (i == one_bits(j)) {
        vector *v = vector_ones(rm->n);
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

size_t RM_strength(RM *rm) {
  return ((1 << (rm->m - rm->r - 1)) - 1);
}

vector *RM_split(RM *rm) {
  vector *v = vector_new(rm->r + 1);
  vector_push_back(v, 0);
  for (size_t i = 1; i <= rm->r; ++i)
    vector_push_back(v, *vector_at(v, i - 1) + binom(rm->m, i));
  return v;
}

matrix *RM_missing(RM *rm) {
  matrix *m = matrix_new(rm->k);
  for (size_t i = 0; i <= rm->r; ++i) {
    for (size_t j = 0; j < rm->n; ++j) {
      if (i == one_bits(j)) {
        vector *v = vector_new(rm->m);
        for (size_t k = 0; k < rm->m; ++k) {
          if (!(j & (1 << k)))
            vector_push_back(v, k);
        }
        matrix_push_back(m, v);
      }
    }
  }
  return m;
}

matrix **RM_ml(RM *rm) {
  matrix **ml = (matrix **)malloc(rm->k * sizeof(*ml));
  matrix *m = RM_missing(rm);
  for (size_t i = 0; i < rm->k; ++i) {
    matrix *ml_row = matrix_new(1 << m->rows[i]->size);
    matrix_push_back(ml_row, vector_ones(rm->n));
    for (size_t j = 0; j < m->rows[i]->size; ++j) {
      vector *v = vector_base(rm->m, *vector_at(m->rows[i], j));
      vector *not_v = vector_neg(v);
      matrix *ml_row_new = matrix_new(1 << m->rows[i]->size);
      for (size_t k = 0; k < ml_row->size; ++k) {
        matrix_push_back(ml_row_new, vector_mult(v, ml_row->rows[k]));
        matrix_push_back(ml_row_new, vector_mult(not_v, ml_row->rows[k]));
      }
      matrix *tmp = ml_row;
      ml_row = ml_row_new;
      matrix_delete(tmp);
      vector_delete(v);
      vector_delete(not_v);
    }
    ml[i] = ml_row;
  }
  matrix_delete(m);
  return ml;
}

void RM_ml_print(RM *rm) {
  for (size_t i = 0; i < rm->k; ++i) {
    matrix_print(rm->ml[i], " ");
    printf("\n");
  }
}

vector *RM_encode(RM *rm, const char *str) {
  if (rm->k != strlen(str))
    return NULL;
  vector *message = vector_str(str);
  vector *code_word = vector_new(rm->n);
  for (size_t i = 0; i < rm->n; ++i) 
    vector_push_back(code_word, vector_dotproduct(message, rm->G_T->rows[i]) % 2);
  vector_delete(message);
  return code_word;
}

vector *RM_decode(RM *rm, const char *str) {
  if (rm->n != strlen(str))
    return NULL;
  vector *code_word = vector_str(str);
  vector *message = vector_new(rm->k);
  vector *indices = RM_split(rm);
  for (size_t i = rm->r; i >= 0; ++i) {
    size_t lo = i == 0 ? 0 : *vector_at(indices, i - 1) + 1;
    size_t hi = *vector_at(indices, i);
    for (size_t j = lo; j <= hi; ++j) {
      size_t zeros = 0;
      size_t ones = 0;
      for (size_t k = 0; k < rm->ml[j]->size; ++k) {
        if (vector_dotproduct(code_word, rm->ml[j]->rows[k]) % 2 == 0)
          zeros++;
        else
          ones++;
      }
      if (zeros == ones)
        return NULL;
      *vector_at(message, j) = zeros > ones ? 0 : 1;  
    }

  }

  return NULL;
}

int main() {
  RM *rm = RM_new(2, 3);
  matrix_print(rm->G, "\n");
  printf("\n");
  // RM_ml_print(rm);
  vector_delete(v);
  RM_delete(rm);
  return 0;
}

