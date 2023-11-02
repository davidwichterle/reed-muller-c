#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "vector.h"

matrix *m_new(size_t size) {
  matrix *m = (matrix *)malloc(sizeof(*m));
  m->rows = (vector **)malloc(size * sizeof(*(m->rows)));
  m->size = 0;
  m->capacity = size;
  return m; 
}

void m_delete(matrix *m) {
  for (size_t i = 0; i < m->size; ++i)
    v_delete(m->rows[i]);
  free(m->rows);
  free(m);
}

unsigned m_resize(matrix *m, size_t size) {
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

unsigned m_push_back(matrix *m, vector *val) {
  if(!m_resize(m, m->size + 1)) 
    return 0;
  m->rows[m->size - 1] = val;
  return 1;
}

void m_print(matrix *m) {
  for (size_t i = 0; i < m->size; ++i) 
    v_print(m->rows[i]);
}

matrix *m_base(size_t size) {
  matrix *m = m_new(size);
  for (size_t i = 0; i < size; ++i)
    m_push_back(m, v_base(size, i));
  return m;
}

matrix *m_transpose(matrix *m) {
  matrix *res = m_new(m->rows[0]->size);
  for (size_t i = 0; i < res->capacity; ++i)
    res->rows[i] = v_new(m->size);
  for (size_t i = 0; i < res->capacity; ++i) {
    for (size_t j = 0; j < res->rows[0]->capacity; ++j) {
      res->rows[i]->data[j] =  m->rows[j]->data[i];
    }
  }
  return res;
}
