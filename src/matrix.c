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

matrix *matrix_mat(matrix *dst, matrix *src) {
  matrix *tmp = dst;
  dst = src;
  matrix_delete(tmp);
  return dst;
}

void matrix_delete(matrix *m) {
  for (size_t i = 0; i < m->size; ++i)
    vector_delete(*matrix_at(m, i));
  free(m->rows);
  free(m);
}

int matrix_resize(matrix *m, size_t size) {
  if (size > m->capacity) {
    size_t new_capacity = (m->capacity + 1) * 2;
    vector **new_rows = (vector **)realloc(m->rows, new_capacity * sizeof(*new_rows));
    if (!new_rows) {
      printf("error: not enough memory\n");
      return 0;
    }
    m->capacity = new_capacity;
    m->rows = new_rows;
  }
  m->size = size;
  return 1;
}

vector **matrix_at(matrix *m, size_t pos) {
  if (!m || pos < 0 || pos > m->capacity - 1) 
    return NULL;
  return m->rows + pos; 
}

int matrix_push_back(matrix *m, vector *val) {
  if(!matrix_resize(m, m->size + 1)) 
    return 0;
  *matrix_at(m, m->size - 1) = val;
  return 1;
}

void matrix_print(matrix *m, const char *del) {
  for (size_t i = 0; i < m->size; ++i)
    vector_print(*matrix_at(m, i), del);
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
    for (size_t j = 0; j < (*matrix_at(res, 0))->capacity; ++j)
      vector_insert(*matrix_at(res, i), j, *vector_at(*matrix_at(m, j), i));
  }
  return res;
}
