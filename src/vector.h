#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>

/**
 * Structure emulating C++ std::vector<unsigned>
 * @param data array of unsigned integers
 * @param size current size
 * @param capacity current capacity
*/
typedef struct vector {
  unsigned *data;
  size_t size;
  size_t capacity;
} vector;

/**
 * Creates new vector
 * @param size capacity of the vector
 * @return pointer to the new vector
*/
vector *v_new(size_t size);

/**
 * Converts C string to vector
 * @param str const char array of 0's and 1's
 * @return pointer to the vector converted from C string
*/
vector *v_str(const char *str);

/**
 * Delete vector
 * @param v vector pointer
*/
void v_delete(vector *v);

/**
 * Resize vector - reallocate memory if necessary
 * @param v vector pointer
 * @param size new capacity of the vector
 * @return 0 on error, 1 on success
*/
unsigned v_resize(vector *v, size_t size);

/**
 * Add element to the end of vector
 * @param v vector pointer
 * @param val element to be inserted
 * @return 0 on error, 1 on success
*/
unsigned v_push_back(vector *v, unsigned val);

/**
 * Display vector
 * @param v vector pointer
*/
void v_print(vector *v);

/**
 * Vector addition
 * @param v1 first vector poinetr 
 * @param v2 second vector pointer
 * @return pointer to vector v1 + v2
*/
vector *v_add(vector *v1, vector *v2);

/**
 * Vector multiplication
 * @param v1 first vector
 * @param v2 second vector
 * @return pointer to vector v1 * v2
*/
vector *v_mult(vector *v1, vector *v2);

/**
 * Vector negation over Z_2 (0 -> 1, 1 -> 0)
 * @param v vector pointer
 * @return pointer to negation of original vector
*/
vector *v_neg(vector *v);

/**
 * Reduce vector over provided modulo
 * @param v vector pointer
 * @param p modulo
 * @return pointer to vector reduced by p
*/
vector *v_mod(vector *v, size_t p);

/**
 * Sums vector contents
 * @param v vector
 * @return sum i.e. (v[1] + ... + v[n]) 
*/
size_t v_sum(vector *v);

/**
 * Computes dot product of 2 vectors
 * @param v1 first vector
 * @param v2 second vector
 * @return dot product i.e. (v1[1] * v2[1] + ... + v1[n] * v2[n]) 
*/
size_t v_dotproduct(vector *v1, vector *v2);

/**
 * Creates vector of ones
 * @param size size of the vector
 * @return [1] * size  
*/
vector *v_ones(size_t size);

/**
 * Creates base vector
 * @param n size of the vector is 2^n
 * @param k number 0's and 1's in each pattern
 * @return pointer to vector [[0] * 2^k + [1] * 2^k] * 2^(n - k - 1)
*/
vector *v_base(size_t n, size_t k);

#endif // VECTOR_H