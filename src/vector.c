#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

vector *vector_new(size_t size) {
  vector *v = (vector *)malloc(sizeof(*v));
  v->data = (unsigned *)malloc(size * sizeof(*(v->data)));
  v->size = 0;
  v->capacity = size;
  return v;
}

void vector_delete(vector *v) {
  free(v->data);
  free(v);
}

unsigned vector_resize(vector *v, size_t size) {
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

unsigned vector_push_back(vector *v, unsigned val) {
  if(!vector_resize(v, v->size + 1)) 
    return 0;
  v->data[v->size - 1] = val;
  return 1;
}

void vector_print(vector *v) {
  for (size_t i = 0; i < v->size; ++i)
    printf("%u ", v->data[i]);
  printf("\n");
}

vector *vector_add(vector *v1, vector *v2) {
  vector *res = vector_new(v1->size);
  for (size_t i = 0; i < res->capacity; ++i)
    vector_push_back(res, v1->data[i] + v2->data[i]);
  return res;
}

vector *vector_mult(vector *v1, vector *v2) {
  vector *res = vector_new(v1->size);
  for (size_t i = 0; i < res->capacity; ++i)
    vector_push_back(res, v1->data[i] * v2->data[i]);
  return res;
}

vector *vector_neg(vector *v) {
  vector *res = vector_new(v->size);
  for (size_t i = 0; i < res->capacity; ++i)
    vector_push_back(res, 1 - v->data[i]);
  return res;
}

vector *vector_mod(vector *v, size_t p) {
  for (size_t i = 0; i < v->capacity; ++i)
    v->data[i] %= p;
  return v;
}

size_t vector_sum(vector *v) {
  size_t res = 0;
  for (size_t i = 0; i < v->size; ++i)
    res += v->data[i];
  return res;
}

size_t vector_dotproduct(vector *v1, vector *v2) {
  vector *tmp = vector_mult(v1, v2);
  size_t res = vector_sum(tmp);
  vector_delete(tmp);
  return res;
}

vector *ones(size_t size) {
  vector *v = vector_new(size);
  for (size_t i = 0; i < size; ++i) 
    vector_push_back(v, 1);
  return v;
}

vector *base_vector(size_t n, size_t k) {
  size_t size = 1 << n;
  size_t reps = 1 << k;
  vector *v = vector_new(size);
  for (size_t j = 0; j < size; ++j) 
    vector_push_back(v, (j / reps) % 2);
  return v;
}