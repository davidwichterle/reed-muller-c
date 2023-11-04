#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

vector *vector_new(size_t size) {
  vector *v = (vector *)malloc(sizeof(*v));
  v->data = (unsigned *)malloc(size * sizeof(*(v->data)));
  v->size = 0;
  v->capacity = size;
  return v;
}

vector *vector_str(const char *str) {
  size_t n = strlen(str);
  if (!n)
    return NULL;
  vector *v = vector_new(n);
  for (size_t i = 0; i < n; ++i) {
    if (str[i] != '0' && str[i] != '1') {
      vector_delete(v);
      return NULL;
    }
    vector_push_back(v, str[i] -'0');
  }
  return v;
}

vector *vector_vec(vector *dst, vector *src) {
  vector *tmp = dst;
  dst = src;
  vector_delete(tmp);
  return dst;
}

void vector_delete(vector *v) {
  free(v->data);
  free(v);
}

int vector_resize(vector *v, size_t size) {
  if (size > v->capacity) {
    size_t new_size = (v->capacity + 1) * 2;
    unsigned *new_data = (unsigned *)realloc(v->data, new_size * sizeof(*new_data));
    if (new_data) {
      v->capacity = new_size;
      v->data = new_data;
    } else {
      printf("error: not enough memory\n");
      return 0;
    }
  }
  v->size = size;
  return 1;
}

int vector_push_back(vector *v, unsigned val) {
  if(!vector_resize(v, v->size + 1)) 
    return 0;
  *vector_at(v, v->size - 1) = val;
  return 1;
}

int vector_insert(vector *v, size_t pos, unsigned val) {
  unsigned *i = vector_at(v, pos);
  if (!i)
    return 0;
  *i = val;
  v->size++;
  return 1;
}

unsigned *vector_at(vector *v, size_t pos)
{
  if (!v || pos < 0 || pos > v->capacity - 1)
    return NULL;
  return (v->data + pos);
}

vector *vector_slice(vector *v, size_t lo, size_t hi) {
  if (!v || lo < 0 || hi > v->capacity - 1 || lo > hi) 
    return NULL;
  vector *res = vector_new(hi - lo + 1);
  for (size_t i = lo; i <= hi; ++i)
    vector_push_back(res, *vector_at(v, i));
  return res; 
}

void vector_print(vector *v) {
  printf("[ ");
  for (size_t i = 0; i < v->size; ++i)
    printf("%u ", *vector_at(v, i));
  printf("]");
}

vector *vector_add(vector *v1, vector *v2) {
  vector *res = vector_new(v1->size);
  for (size_t i = 0; i < res->capacity; ++i)
    vector_push_back(res, *vector_at(v1, i) + *vector_at(v2, i));
  return res;
}

vector *vector_mult(vector *v1, vector *v2) {
  vector *res = vector_new(v1->size);
  for (size_t i = 0; i < res->capacity; ++i)
    vector_push_back(res, *vector_at(v1, i) * *vector_at(v2, i));
  return res;
}

vector *vector_neg(vector *v) {
  vector *res = vector_new(v->size);
  for (size_t i = 0; i < res->capacity; ++i)
    vector_push_back(res, 1 - *vector_at(v, i));
  return res;
}

vector *vector_mod(vector *v, size_t p) {
  for (size_t i = 0; i < v->capacity; ++i)
    *vector_at(v, i) %= p;
  return v;
}

size_t vector_sum(vector *v) {
  size_t res = 0;
  for (size_t i = 0; i < v->size; ++i)
    res += *vector_at(v, i);
  return res;
}

size_t vector_dotproduct(vector *v1, vector *v2) {
  vector *tmp = vector_mult(v1, v2);
  size_t res = vector_sum(tmp);
  vector_delete(tmp);
  return res;
}

vector *vector_ones(size_t size) {
  vector *v = vector_new(size);
  for (size_t i = 0; i < size; ++i) 
    vector_push_back(v, 1);
  return v;
}

vector *vector_base(size_t n, size_t k) {
  size_t size = 1 << n;
  size_t reps = 1 << k;
  vector *v = vector_new(size);
  for (size_t j = 0; j < size; ++j) 
    vector_push_back(v, (j / reps) % 2);
  return v;
}