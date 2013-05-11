/*
 * runlength_decompress.h
 *
 *  Created on: May 9, 2013
 *      Author: emanuel
 */

#ifndef RUNLENGTH_DECOMPRESS_H_
#define RUNLENGTH_DECOMPRESS_H_

FILE *fp_in, *fp_out;
void runlength_decompress(char*);
void runlength_decompress_process_row(FILE *fp_in, FILE *fp_out, int i);
void runlength_decompress_flush_repeated(FILE *fp_in, FILE *fp_out);


#endif /* RUNLENGTH_DECOMPRESS_H_ */
