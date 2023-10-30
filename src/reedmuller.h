#ifndef REEDMULLER_H
#define REEDMULLER_H

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

/**
 * Reed-Muller code RM(r, m)
 * @param r order
 * @param m code length is 2^m
 * @param n code length i.e. 2^m
 * @param k message length i.e. dim(RM(r, m))
 * @param G pointer to generator matrix
*/
typedef struct RM {
  size_t r;
  size_t m;
  size_t n;
  size_t k;
  matrix *G;
} RM;

/**
 * Computes dimension of the RM(r, m) code
 * @param r order
 * @param m code length is 2^m
 * @return binom(m, 0) + ... + binom(m, r) i.e. number of rows of generator matrix
*/
size_t RM_dim(size_t r, size_t m);

/**
 * Creates new RM(r, m) code
 * @param r order
 * @param m code length is 2^m
 * @return pointer to the created RM(r, m) code
*/
RM *RM_new(size_t r, size_t m);

/**
 * Delete RM code
 * @param rm code
*/
void RM_delete(RM *rm);

/**
 * Creates generator matrix for the RM(r, m) code
 * @param rm RM(r, m) code
 * @return pointer to the created generator matrix
*/
matrix *RM_generator_matrix(RM *rm);

/**
 * Computes strength of RM(r, m) code i.e. number of errors we can correct
 * @param rm RM(r, m) code
 * @return 2^(m - r - 1) - 1
*/
size_t RM_str(RM *rm);

/**
 * Splits generator matrix into r + 1 parts, matrices, which are associated with r-order terms
 * @param rm RM(r, m) code
 * @return vector of indices of rows, which are the last to be associated with with r-order terms
*/
vector *RM_split(RM *rm);

#endif