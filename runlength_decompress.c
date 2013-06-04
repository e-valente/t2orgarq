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


/*
 * Processa o arquivo a ser descomprimido
 * Parâmetros:
 *  *fp_in: ponteiro para o arquvo de entrada
 */
void runlength_decompress(char *filename_in)
{
	int i, rows, cols, range;
	char img_magic_number[2];
	char ch;


	fp_in = fopen(filename_in, "r");

	if(!fp_in){
		printf("Falha ao abrir arquivo %s\n ", filename_in);
		return;
	}


	//obtem magic number, cols, and rows
	fscanf(fp_in, "%s", img_magic_number);
	fscanf(fp_in, "%d %d", &cols, &rows);
	fscanf(fp_in, "%d", &range);

	//escreve magic number cols and rows
	printf("%s\n", "P2");
	printf("%d %d\n", cols, rows);
	printf("%d\n", range);



	//remove a quebra de linha da segunda linha
	//e volta um caracter (1 byte) caso nao for a quebra
	ch = fgetc(fp_in);
	if(ch != '\n')fseek(fp_in, -1, SEEK_CUR);

	for(i = 0; i < rows; i++)
	{
		runlength_decompress_process_row(fp_in, i);
		printf("\n");


	}

	fclose(fp_in);

}


/*
 * Processa cada linha do arquivo compactado
 * Parâmetros:
 *  *fp_in: ponteiro para o arquvo de entrada
 *  i: linha atual
 */
void runlength_decompress_process_row(FILE *fp_in, int i)
{
	char buffline[1000];
	char *token;
	int times, value;


	//obtem a linha atual
	fgets(buffline, 1000, fp_in);
	//printf("linha %d: %s\n", i, buffline);

	//processa o conteudo da linha


	token = strtok(buffline, " ");
	while(token != NULL)
	{
		//repetiu
		if(strcmp(token, "ff") == 0)
		{
			token = strtok(NULL, " ");
			value = atoi(token);
			token = strtok(NULL, " ");
			times = atoi(token);

			for(i = 0; i < times; i++)
			{
				printf("%d ", value);
			}

		} else {

			//imprime inteiro qdo nao repete
			//lixo que vem no fim da linha
			if(strcmp(token, "  ") > 0){
			printf("%d ", atoi(token));

			}
		}

		token = strtok(NULL, " ");
	}

}


