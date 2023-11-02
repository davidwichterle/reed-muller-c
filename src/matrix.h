#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

/**
 * Structure emulating C++ std::vector<std::vector<unsigned>>
 * @param rows array of row pointers
 * @param size current size
 * @param capacity current capacity
*/
typedef struct matrix {
  vector **rows;
  size_t size;
  size_t capacity;
} matrix;

/**
 * Creates new matrix
 * @param size capacity of the matrix
 * @return pointer to the new matrix
*/
matrix *matrix_new(size_t size);

/**
 * Delete matrix
 * @param m matrix pointer
*/
void matrix_delete(matrix *m);

/**
 * Resize matrix - reallocate memory if necessary
 * @param m matrix pointer
 * @param size new capacity of the matrix
 * @return 0 on error, 1 on success
*/
unsigned matrix_resize(matrix *m, size_t size);

/**
 * Add row to the end of matrix
 * @param m matrix pointer
 * @param val vector pointer to be inserted
 * @return 0 on error, 1 on success
*/
unsigned matrix_push_back(matrix *m, vector *val);

/**
 * Display matrix
 * @param m matrix pointer
 * @param del const char array, row delimeter
*/
void matrix_print(matrix *m, const char *del);

/**
 * Creates base matrix
 * @param size number of rows
 * @return matrix pointer, whose rows are base vectors
*/
matrix *matrix_base(size_t size);

/**
 * Transposes matrix
 * @param m matrix pointer
 * @return matrix pointer to the transposition of the original matrix
*/
matrix *matrix_transpose(matrix *m);

#endif // MATRIX_H