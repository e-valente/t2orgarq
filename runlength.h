/*
 * runlength.h
 *
 *  Created on: May 8, 2013
 *      Author: emanuel
 */

#ifndef RUNLENGTH_H_
#define RUNLENGTH_H_


void runlength_init(FILE*);
void runlength_row_process(int **, int row, int cols);
void runlength_compact(int **img_matrix, int row, int i, int count);

#endif /* RUNLENGTH_H_ */
