/*
 * runlength.h
 *
 *  Created on: May 8, 2013
 *      Author: emanuel
 */

#ifndef RUNLENGTH_H_
#define RUNLENGTH_H_

FILE *fp_in, *fp_out;
void runlength_compress(char*);
void runlength_row_process(int **, int row, int cols);
void runlength_flush(int **img_matrix, int row, int i, int count);

#endif /* RUNLENGTH_H_ */
