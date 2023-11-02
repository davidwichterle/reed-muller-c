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
 * @param G pointer to the generator matrix
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
 * @return binom(m, 0) + ... + binom(m, r) i.e. number of rows of the generator matrix
*/
size_t RM_dim(size_t r, size_t m);

/**
 * Creates new RM(r, m) code
 * @param r order
 * @param m code length is 2^m
 * @return pointer to the new RM(r, m) code
*/
RM *RM_new(size_t r, size_t m);

/**
 * Delete RM(r, m) code
 * @param rm RM(r, m) code pointer
*/
void RM_delete(RM *rm);

/**
 * Creates generator matrix for the RM(r, m) code
 * @param rm RM(r, m) code pointer
 * @return pointer to the created generator matrix
*/
matrix *RM_gen_matrix(RM *rm);

/**
 * Computes strength of RM(r, m) code i.e. number of errors we can correct
 * @param rm RM(r, m) code pointer
 * @return 2^(m - r - 1) - 1
*/
size_t RM_str(RM *rm);

/**
 * Splits generator matrix into r + 1 parts, where each part contains vectors of same order
 * @param rm RM(r, m) code pointer
 * @return vector pointer, where each value is index of last row to be associated with r-order rows
*/
vector *RM_split(RM *rm);

/**
 * For each row of generator matrix, find base vectors not represented in the row
 * @param rm RM(r, m) code pointer
 * @return matrix pointer, where each row is vector of indices of base vectors not represented in row of generator matrix
*/
matrix *RM_missing(RM *rm);

/**
 * Majority logic table - for each row of generator matrix, create list of vectors, which are 
 * combinations of base vectors not represented in the row
 * @param rm RM(r, m) code pointer
 * @return array of matrix pointers, used in majority logic voting in decoding process 
*/
matrix **RM_ml_table(RM *rm);

#endif