/*
 * runlength_decompress.c
 *
 *  Created on: May 9, 2013
 *      Author: emanuel
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "runlength_decompress.h"

void runlength_decompress(char *filename_in)
{
	int i, rows, cols, range;
	char img_magic_number[2];
	char ch, *filename_out;
	char *pgmformat = ".pgm";


	fp_in = fopen(filename_in, "r");

	if(!fp_in){
		printf("Falha ao abrir arquivo %s\n ", filename_in);
		return;
	}



	//handling file out (compressed)
	filename_out = (char*)malloc(sizeof(char) * strlen(filename_in));
	strcpy(filename_out, "\0");
	strncat(filename_out, filename_in, strlen(filename_in) -4);
	strcat(filename_out, pgmformat);



	fp_out = fopen(filename_out, "w");
	//fp_out = fopen("vai.pgm", "w");

	//get the magic number, cols, and rows
	fscanf(fp_in, "%s", img_magic_number);
	fscanf(fp_in, "%d %d", &cols, &rows);
	fscanf(fp_in, "%d", &range);

	//write magic number cols and rows
	fprintf(fp_out,"%s\n", "P1");
	fprintf(fp_out,"%d %d\n", cols, rows);
	fprintf(fp_out, "%d\n", range);



	//decompress
	//remove a quebra de linha da segunda linha
	//e volta um caracter (1 byte) caso nao for a quebra
	ch = fgetc(fp_in);
	if(ch != '\n')fseek(fp_in, -1, SEEK_CUR);

	for(i = 0; i < rows; i++)
	{
		runlength_decompress_process_row(fp_in, fp_out, i);
		printf("\n");
		fprintf(fp_out, "\n");

	}


	free(filename_out);
	fclose(fp_in);
	fclose(fp_out);

}

void runlength_decompress_process_row(FILE *fp_in, FILE *fp_out, int i)
{
	char ch;

	do{
		ch = fgetc(fp_in);
		if(ch != '\n'){
			if(ch == 'f') {
				ch = fgetc(fp_in);
				//printf("repetiu! ");
				runlength_decompress_flush_repeated(fp_in, fp_out);
			}
			else {
				if(ch != ' '){
					printf("%d ", atoi(&ch));
					fprintf(fp_out, "%d ", atoi(&ch));
				}

			}


		}

	}
	while(ch != '\n');

}

void runlength_decompress_flush_repeated(FILE *fp_in, FILE *fp_out)
{
	int i, value, times;

	fscanf(fp_in,"%d %d", &value, &times);

	for( i = 0; i < times; i++)
	{
		printf("%d ", value);
		fprintf(fp_out, "%d ", value);

	}


}


