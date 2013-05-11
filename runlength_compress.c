/*
 * runlength_compress.c
 *
 *  Created on: May 9, 2013
 *      Author: emanuel
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "runlength_compress.h"

void runlength_compress(char *filename_in)
{
	int i, j;
	int rows, cols, range;
	char img_magic_number[2];
	char *filename_out;
	int **img_matrix;
	char *rlformat = ".rl";


	fp_in = fopen(filename_in, "r");


	if(!fp_in){
		printf("Falha ao abrir arquivo %s\n ", filename_in);
		return;
	}

	//handling file out (compressed)
	filename_out = (char*)malloc(sizeof(char) * strlen(filename_in));
	strcpy(filename_out, "\0");
	strncat(filename_out, filename_in, strlen(filename_in) -4);
	strcat(filename_out, rlformat);

	//printf("arquivo de saida: %s\n", filename_out);

	fp_out = fopen(filename_out, "w");




	//get the magic number, cols, and rows
	fscanf(fp_in, "%s", img_magic_number);
	fscanf(fp_in, "%d %d", &cols, &rows);
	fscanf(fp_in, "%d", &range);

	//write magic number cols and rows
	fprintf(fp_out,"%s\n", "P8");
	fprintf(fp_out,"%d %d\n", cols, rows);
	fprintf(fp_out, "%d\n", range);


	//alloc img matrix
	img_matrix = (int**) malloc(sizeof(int*) * rows);

	for(i = 0; i < rows; i++)
	{
		img_matrix[i] = (int*) malloc(sizeof(int) * cols);
	}



	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)

			fscanf(fp_in, "%d",&img_matrix[i][j]);
	}


	//processa cada linha

	for(i = 0; i < rows; i++) {
		runlength_row_process(img_matrix, i, cols);
		printf("\n");
		fprintf(fp_out, "\n");
	}


	//libera memoria
	for(i = 0; i < rows; i++)
	{
		free(img_matrix[i]);
	}

	free(filename_out);
	fclose(fp_in);
	fclose(fp_out);
	free(img_matrix);

}

void runlength_row_process(int **img_matrix, int row, int cols)
{
	int i, count;

	//imprime
	for(i = 0; i < cols -1; i++)
	{
		count = 1;
		//printf("linha %d colina %d comparando %d com %d\n", row, i, img_matrix[row][i],img_matrix[row][i+1] );
		if(img_matrix[row][i] == img_matrix[row][i+1]) {
			while(img_matrix[row][i] == img_matrix[row][i+1] && cols > i +1)
			{
				count++;
				i++;
			}

			if(count > 3)runlength_flush(img_matrix, row, i, count);

			if(count == 3) {
				i -= 2;
				runlength_flush(img_matrix, row, i, 3);
			}
			if(count == 2) {
				i -= 1;
				runlength_flush(img_matrix, row, i, 2);
			}


		} else runlength_flush(img_matrix, row, i, count);


	}

	//se o ultimo caracter for diferente do penultimo
	count = 1;
	if(img_matrix[row][cols-2] != img_matrix[row][cols-1])
		runlength_flush(img_matrix, row, cols -1, count);


}


void runlength_flush(int **img_matrix, int row, int i, int count)
{
	//printf("linha: %d elemento repetido %d numero de repeticoes: %d\n",
	//	row+1, img_matrix[row][i], count );
	if(count > 3){
		printf("ff %d %d ",img_matrix[row][i], count);
		fprintf(fp_out, "ff %d %d ",img_matrix[row][i], count);

	}
	else {
		printf("%d ",img_matrix[row][i]);
		fprintf(fp_out, "%d ",img_matrix[row][i]);
	}

}
