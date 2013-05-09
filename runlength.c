/*
 * runlength.c
 *
 *  Created on: May 8, 2013
 *      Author: emanuel
 */

#include <stdlib.h>
#include <stdio.h>

#include "runlength.h"

void runlength_init(FILE *fp)
{
	int i, j;
	char ch;
	int rows, cols;
	char img_magic_number[2];

	int **img_matrix;


	fscanf(fp, "%s", img_magic_number);
	fscanf(fp, "%d %d", &cols, &rows);

	//alloc img matrix
	img_matrix = (int**) malloc(sizeof(int*) * rows);

	for(i = 0; i < rows; i++)
	{
		img_matrix[i] = (int*) malloc(sizeof(int) * cols);
	}


	//img_file -> to img_matrix (ram)
	printf("magic: %s cols: %d rows: %d\n\n", img_magic_number, cols, rows);

	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{


			ch = fgetc(fp);

			//qdo o primeiro caracter for espaco
			if(i == 0 && j == 0 && ch == '\n')
				ch = fgetc(fp);

			if(ch == ' ' || ch == '\n')
				j--;


			if(ch != ' ' && ch != '\n')
				img_matrix[i][j] = atoi(&ch);
		}

	}


	//imprime
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{

			//printf("%d", img_matrix[i][j]);
		}

		//printf("\n");

	}


	//processa cada linha

	for(i = 0; i < rows; i++)
	{
		//printf("linha %d\n", i + 1);

		runlength_row_process(img_matrix, i, cols);
		printf("\n");

	}


	//printf("\n\n");

	//libera memoria
	for(i = 0; i < rows; i++)
	{
		free(img_matrix[i]);
	}

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

			if(count > 3)runlength_compact(img_matrix, row, i, count);

			if(count == 3) {
				i -= 2;
				runlength_compact(img_matrix, row, i, 3);
			}
			if(count == 2) {
				i -= 1;
				runlength_compact(img_matrix, row, i, 2);
			}


		} else{
			runlength_compact(img_matrix, row, i, count);

		}

		//printf("linha atual é : %d elem: %d\n", row+1, img_matrix[row][i]);
	}



}


void runlength_compact(int **img_matrix, int row, int i, int count)
{
	//printf("linha: %d elemento repetido %d numero de repeticoes: %d\n",
		//	row+1, img_matrix[row][i], count );
	if(count > 3)printf("ff %d %d ",img_matrix[row][i], count);
	else printf("%d ",img_matrix[row][i]);

}
