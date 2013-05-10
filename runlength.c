/*
 * runlength.c
 *
 *  Created on: May 8, 2013
 *      Author: emanuel
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "runlength.h"

void runlength_compress(char *filename_in)
{
	int i, j;
	char ch;
	int rows, cols;
	char img_magic_number[2];
	char *token, *filename_out;
	int **img_matrix;


	fp_in = fopen(filename_in, "r");


	if(!fp_in){
		printf("Falha ao abrir arquivo %s\n ", filename_in);
		return;
	}

	//handling file out (compressed)
	token = strtok(filename_in, "pbm");
	filename_out = (char*)malloc(sizeof(char) * (strlen(token) + 3));
	strcat(filename_out, token);
	strcat(filename_out, "rl");

	//printf("arquivo de saida: %s\n", filename_out);

	fp_out = fopen(filename_out, "w");




	//get the magic number, cols, and rows
	fscanf(fp_in, "%s", img_magic_number);
	fscanf(fp_in, "%d %d", &cols, &rows);

	//write magic number cols and rows
	fprintf(fp_out,"%s\n", "P8");
	fprintf(fp_out,"%d %d\n", cols, rows);


	//alloc img matrix
	img_matrix = (int**) malloc(sizeof(int*) * rows);

	for(i = 0; i < rows; i++)
	{
		img_matrix[i] = (int*) malloc(sizeof(int) * cols);
	}



	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{


			ch = fgetc(fp_in);

			//qdo o primeiro caracter for espaco
			if(i == 0 && j == 0 && ch == '\n')
				ch = fgetc(fp_in);

			if(ch == ' ' || ch == '\n')
				j--;


			if(ch != ' ' && ch != '\n')
				img_matrix[i][j] = atoi(&ch);
		}

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


		} else{
			runlength_flush(img_matrix, row, i, count);

		}

		//printf("linha atual é : %d elem: %d\n", row+1, img_matrix[row][i]);
	}



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
