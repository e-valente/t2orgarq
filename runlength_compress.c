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

/*
 * Processa o arquivo a ser comprimido
 * Parâmetros:
 *  *fp_in: ponteiro para o arquvo de entrada
 */
void runlength_compress(char *filename_in)
{
	int i, j;
	int rows, cols, range;
	char img_magic_number[2];
	int **img_matrix;


	fp_in = fopen(filename_in, "r");


	if(!fp_in){
		printf("Falha ao abrir arquivo %s\n ", filename_in);
		return;
	}



	//obtemmagic number, cols, and rows
	fscanf(fp_in, "%s", img_magic_number);
	fscanf(fp_in, "%d %d", &cols, &rows);
	fscanf(fp_in, "%d", &range);

	//escreve magic number cols and rows
	printf("%s\n", "P8");
	printf("%d %d\n", cols, rows);
	printf("%d\n", range);

	//alloc img matrix
	img_matrix = (int**) malloc(sizeof(int*) * rows);

	for(i = 0; i < rows; i++)
	{
		img_matrix[i] = (int*) malloc(sizeof(int) * cols);
	}



	//arquivo -> ram
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < cols; j++)
		{

			fscanf(fp_in, "%d",&img_matrix[i][j]);
		}
	}


	//processa cada linha

	for(i = 0; i < rows; i++) {
		runlength_row_process(img_matrix, i, cols);
		printf("\n");

	}


	//libera memoria
	for(i = 0; i < rows; i++)
	{
		free(img_matrix[i]);
	}


	fclose(fp_in);
	free(img_matrix);

}


/*
 * Processada cada linha a ser comprimida
 * Parâmetros:
 * **img_matrix: matriz contendo a imagem
 * row: linha atual
 * cols: total de colunas
 */
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

			if(count > 3)runlength_flush(img_matrix, row, cols,  i, count);

			if(count == 3) {
				i -= 2;
				runlength_flush(img_matrix, row, cols, i, 3);
				i+=2;
			}
			if(count == 2) {
				i -= 1;
				runlength_flush(img_matrix, row, cols, i, 2);
				i += 1;
			}


		} else runlength_flush(img_matrix, row, cols, i, count);


	}

	//se o ultimo caracter for diferente do penultimo
	count = 1;
	if(img_matrix[row][cols-2] != img_matrix[row][cols-1])
		runlength_flush(img_matrix, row, cols, cols -1, count);


}


/*
 * Imprime na stdout o resultado de cada linha processada
 * Parâmetros:
 * **img_matrix: matriz contendo a imagem comprimida
 * row: linha atual
 * total_cols: total de colunas
 * i: coluna processada
 * count: numero de repeticoes a partir de i
 */
void runlength_flush(int **img_matrix, int row, int total_cols,  int i, int count)
{
	//repete
	if(count > 3){
		//se nao for o ultimo caracter da linha colocamos
		//um espaco depois
		if(i < total_cols -1) {
			printf("ff %d %d ",img_matrix[row][i], count);
			/*pra dar flush num arquivo externo
			 * descomente a linha abaixo
			 */
			//fprintf(fp_out, "ff %d %d ",img_matrix[row][i], count);

		} else {
			//nao tem espaco depois do ultimo caracter
			printf("ff %d %d",img_matrix[row][i], count);
			/*pra dar flush num arquivo externo
			 * descomente a linha abaixo
			 */
			//fprintf(fp_out, "ff %d %d",img_matrix[row][i], count);

		}

		return;

	}

	if(count == 3)
	{
		if(i + 2 < total_cols -1)
			printf("%d %d %d ",img_matrix[row][i], img_matrix[row][i+1], img_matrix[row][i+2]);

		else
			printf("%d %d %d",img_matrix[row][i], img_matrix[row][i+1], img_matrix[row][i+2]);

	}

	if(count == 2)
	{
		if(i + 1 < total_cols -1)
			printf("%d %d ",img_matrix[row][i], img_matrix[row][i+1]);
		else
			printf("%d %d",img_matrix[row][i], img_matrix[row][i+1]);

	}


	if(count == 1)
	{
		if(i < total_cols -1)
			printf("%d ",img_matrix[row][i]);
		else
			printf("%d",img_matrix[row][i]);


	}

}
