#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

vector *v_new(size_t size) {
  vector *v = (vector *)malloc(sizeof(*v));
  v->data = (unsigned *)malloc(size * sizeof(*(v->data)));
  v->size = 0;
  v->capacity = size;
  return v;
}

vector *v_str(const char *str) {
  size_t n = strlen(str);
  if (!n)
    return NULL;
  vector *v = v_new(n);
  for (size_t i = 0; i < n; ++i) {
    if (str[i] != '0' && str[i] != '1') {
      v_delete(v);
      return NULL;
    }
    v_push_back(v, str[i] -'0');
  }
  return v;
}

void v_delete(vector *v)
{
  free(v->data);
  free(v);
}

unsigned v_resize(vector *v, size_t size) {
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

unsigned v_push_back(vector *v, unsigned val) {
  if(!v_resize(v, v->size + 1)) 
    return 0;
  v->data[v->size - 1] = val;
  return 1;
}

void v_print(vector *v) {
  for (size_t i = 0; i < v->size; ++i)
    printf("%u ", v->data[i]);
  printf("\n");
}

vector *v_add(vector *v1, vector *v2) {
  vector *res = v_new(v1->size);
  for (size_t i = 0; i < res->capacity; ++i)
    v_push_back(res, v1->data[i] + v2->data[i]);
  return res;
}

vector *v_mult(vector *v1, vector *v2) {
  vector *res = v_new(v1->size);
  for (size_t i = 0; i < res->capacity; ++i)
    v_push_back(res, v1->data[i] * v2->data[i]);
  return res;
}

vector *v_neg(vector *v) {
  vector *res = v_new(v->size);
  for (size_t i = 0; i < res->capacity; ++i)
    v_push_back(res, 1 - v->data[i]);
  return res;
}

vector *v_mod(vector *v, size_t p) {
  for (size_t i = 0; i < v->capacity; ++i)
    v->data[i] %= p;
  return v;
}

size_t v_sum(vector *v) {
  size_t res = 0;
  for (size_t i = 0; i < v->size; ++i)
    res += v->data[i];
  return res;
}

size_t v_dotproduct(vector *v1, vector *v2) {
  vector *tmp = v_mult(v1, v2);
  size_t res = v_sum(tmp);
  v_delete(tmp);
  return res;
}

vector *v_ones(size_t size) {
  vector *v = v_new(size);
  for (size_t i = 0; i < size; ++i) 
    v_push_back(v, 1);
  return v;
}

vector *v_base(size_t n, size_t k) {
  size_t size = 1 << n;
  size_t reps = 1 << k;
  vector *v = v_new(size);
  for (size_t j = 0; j < size; ++j) 
    v_push_back(v, (j / reps) % 2);
  return v;
}