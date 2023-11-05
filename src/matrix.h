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
 * Initialises matrix from matrix
 * @param dst matrix pointer to be initialised
 * @param src matrix template pointer
 * @return matrix pointer initialised from the matrix pointer template
*/
matrix *matrix_mat(matrix *dst, matrix *src);

/**
 * Deletes matrix
 * @param m matrix pointer
*/
void matrix_delete(matrix *m);

/**
 * Returns address of row in matrix
 * @param m matrix pointer
 * @param pos position
 * @return NULL if position is invalid, else address of row at the position 
*/
vector **matrix_at(matrix *m, size_t pos);

/**
 * Resizes matrix - reallocates memory if necessary
 * @param m matrix pointer
 * @param size new capacity of the matrix
 * @return 0 on error, 1 on success
*/
int matrix_resize(matrix *m, size_t size);

/**
 * Insert row to the end of matrix
 * @param m matrix pointer
 * @param val vector pointer to be inserted
 * @return 0 on error, 1 on success
*/
int matrix_push_back(matrix *m, vector *val);

/**
 * Displays matrix
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