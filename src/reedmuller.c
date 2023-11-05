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
          if (j & (1 << k))
            v = vector_vec(v, vector_mult(v, *matrix_at(base, k)));
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
    matrix *ml_row = matrix_new(1 << (*matrix_at(m, i))->size);
    matrix_push_back(ml_row, vector_ones(rm->n));
    for (size_t j = 0; j < (*matrix_at(m, i))->size; ++j) {
      vector *v = vector_base(rm->m, *vector_at(m->rows[i], j));
      vector *not_v = vector_neg(v);
      matrix *ml_row_new = matrix_new(1 << (*matrix_at(m, i))->size);
      for (size_t k = 0; k < ml_row->size; ++k) {
        matrix_push_back(ml_row_new, vector_mult(v, *matrix_at(ml_row, k)));
        matrix_push_back(ml_row_new, vector_mult(not_v, *matrix_at(ml_row, k)));
      }
      ml_row = matrix_mat(ml_row, ml_row_new);
      vector_delete(v);
      vector_delete(not_v);
    }
    ml[i] = ml_row;
  }
  matrix_delete(m);
  return ml;
}

int RM_ml_vote(RM *rm, vector *code_word, size_t pos) {
  size_t zeros = 0;
  size_t ones = 0;
  for (size_t i = 0; i < rm->ml[pos]->size; ++i) {
    if (!(vector_dotproduct(code_word, *matrix_at(rm->ml[pos], i)) % 2))
      zeros++;
    else
      ones++;
  }
  if (zeros == ones)
    return -1;
  return zeros > ones ? 0 : 1;
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
  vector *codeword = vector_new(rm->n);
  for (size_t i = 0; i < rm->n; ++i) 
    vector_push_back(codeword, vector_dotproduct(message, *matrix_at(rm->G_T, i)) % 2);
  vector_delete(message);
  return codeword;
}

vector *RM_decode(RM *rm, const char *str) {
  if (rm->n != strlen(str))
    return NULL;
  vector *codeword = vector_str(str);
  vector *message = vector_new(rm->k);
  vector *indices = RM_split(rm);
  for (int i = rm->r; i >= 0; --i) {
    size_t lo = i == 0 ? 0 : *vector_at(indices, i - 1) + 1;
    size_t hi = *vector_at(indices, i);
    for (size_t j = lo; j <= hi; ++j) {
      int vote = RM_ml_vote(rm, codeword, j);
      if (vote == -1)
        return NULL;
      vector_insert(message, j, vote);
    }
    vector *res = vector_new(rm->n);
    vector *m = vector_slice(message, lo, hi);
    for (size_t k = 0; k < rm->G_T->size; ++k) {
      vector *col = vector_slice(*matrix_at(rm->G_T, k), lo, hi);
      vector_push_back(res, vector_dotproduct(m, col) % 2);
      vector_delete(col);
    }
    codeword = vector_vec(codeword, vector_mod(vector_add(codeword, res), 2));
    vector_delete(m);
    vector_delete(res);
  }
  vector_delete(codeword);
  vector_delete(indices);
  return message;
}

int main() {
  RM *rm = RM_new(2, 3);
  matrix_print(rm->G, "\n");
  vector *v = RM_decode(rm, "00000110");
  vector_print(v, "\n");
  vector_delete(v);
  RM_delete(rm);
  return 0;
}

