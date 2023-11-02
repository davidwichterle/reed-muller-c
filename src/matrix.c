#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "vector.h"

matrix *matrix_new(size_t size) {
  matrix *m = (matrix *)malloc(sizeof(*m));
  m->rows = (vector **)malloc(size * sizeof(*(m->rows)));
  m->size = 0;
  m->capacity = size;
  return m; 
}

void matrix_delete(matrix *m) {
  for (size_t i = 0; i < m->size; ++i)
    vector_delete(m->rows[i]);
  free(m->rows);
  free(m);
}

unsigned matrix_resize(matrix *m, size_t size) {
  if (size > m->capacity) {
    size_t new_size = (m->capacity + 1) * 2;
    vector **new_rows = (vector **)realloc(m->rows, new_size * sizeof(*new_rows));
    if (new_rows) {
      m->capacity = new_size;
      m->rows = new_rows;
    } else {
      printf("error: not enough memory\n");
      return 0;
    }
  }
  m->size = size;
  return 1;
}

unsigned matrix_push_back(matrix *m, vector *val) {
  if(!matrix_resize(m, m->size + 1)) 
    return 0;
  m->rows[m->size - 1] = val;
  return 1;
}

void matrix_print(matrix *m, const char *del) {
  for (size_t i = 0; i < m->size; ++i) {
    vector_print(m->rows[i]);
    printf("%s", del);
  }
}

matrix *matrix_base(size_t size) {
  matrix *m = matrix_new(size);
  for (size_t i = 0; i < size; ++i)
    matrix_push_back(m, vector_base(size, i));
  return m;
}

matrix *matrix_transpose(matrix *m) {
  matrix *res = matrix_new(m->rows[0]->size);
  for (size_t i = 0; i < res->capacity; ++i)
    matrix_push_back(res, vector_new(m->size));
  for (size_t i = 0; i < res->capacity; ++i) {
    for (size_t j = 0; j < res->rows[0]->capacity; ++j) {
      *vector_at(res->rows[i], j) = *vector_at(m->rows[j], i);
    }
  }
  return res;
}
