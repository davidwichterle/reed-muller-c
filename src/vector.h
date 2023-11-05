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
vector *vector_new(size_t size);

/**
 * Converts C string to vector
 * @param str const char array of 0's and 1's
 * @return pointer to the vector converted from C string
*/
vector *vector_str(const char *str);

/**
 * Initialises vector from vector
 * @param dst vector pointer to be initialised
 * @param src vector template pointer
 * @return vector pointer initialised from the vector template pointer
*/
vector *vector_vec(vector *dst, vector *src);

/**
 * Deletes vector
 * @param v vector pointer
*/
void vector_delete(vector *v);

/**
 * Returns address of element in vector
 * @param v vector pointer
 * @param pos position
 * @return NULL if position is invalid, else address of element at the position 
*/
unsigned *vector_at(vector *v, size_t pos);

/**
 * Resizes vector - reallocates memory if necessary
 * @param v vector pointer
 * @param size new capacity of the vector
 * @return 0 on error, 1 on success
*/
int vector_resize(vector *v, size_t size);

/**
 * Inserts element to the end of vector
 * @param v vector pointer
 * @param val element to be inserted
 * @return 0 on error, 1 on success
*/
int vector_push_back(vector *v, unsigned val);

/**
 * Inserts element to position in vector
 * @param v vector pointer
 * @param pos position 
 * @param val element to be inserted
 * @return 0 on error, 1 on success
*/
int vector_insert(vector *v, size_t pos, unsigned val);

/**
 * Returns slice of the vector
 * @param v vector pointer
 * @param lo lower position
 * @param hi higher position
 * @return NULL if any position is invalid, else v[lo:hi] with higer position included
*/
vector *vector_slice(vector *v, size_t lo, size_t hi);

/**
 * Displays vector
 * @param v vector pointer
 * @param del const char array, delimeter
*/
void vector_print(vector *v, const char *del);

/**
 * Vector addition
 * @param v1 first vector poinetr 
 * @param v2 second vector pointer
 * @return pointer to vector v1 + v2
*/
vector *vector_add(vector *v1, vector *v2);

/**
 * Vector multiplication
 * @param v1 first vector
 * @param v2 second vector
 * @return pointer to vector v1 * v2
*/
vector *vector_mult(vector *v1, vector *v2);

/**
 * Vector negation over Z_2 (0 -> 1, 1 -> 0)
 * @param v vector pointer
 * @return pointer to negation of original vector
*/
vector *vector_neg(vector *v);

/**
 * Reduces vector over provided modulo in place
 * @param v vector pointer
 * @param p modulo
 * @return pointer to vector reduced by p
*/
vector *vector_mod(vector *v, size_t p);

/**
 * Sums vector contents
 * @param v vector
 * @return sum i.e. (v[1] + ... + v[n]) 
*/
size_t vector_sum(vector *v);

/**
 * Computes dot product of two vectors
 * @param v1 first vector
 * @param v2 second vector
 * @return dot product i.e. (v1[1] * v2[1] + ... + v1[n] * v2[n]) 
*/
size_t vector_dotproduct(vector *v1, vector *v2);

/**
 * Creates vector of ones
 * @param size size of the vector
 * @return [1] * size  
*/
vector *vector_ones(size_t size);

/**
 * Creates base vector
 * @param n size of the vector is 2^n
 * @param k number 0's and 1's in each pattern
 * @return pointer to vector [[0] * 2^k + [1] * 2^k] * 2^(n - k - 1)
*/
vector *vector_base(size_t n, size_t k);

#endif // VECTOR_H