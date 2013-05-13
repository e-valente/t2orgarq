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
	char ch, *filename_out;
	char *pgmformat = ".pgm";


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
	printf("%s\n", "P1");
	printf("%d %d\n", cols, rows);
	printf("%d\n", range);



	//remove a quebra de linha da segunda linha
	//e volta um caracter (1 byte) caso nao for a quebra
	ch = fgetc(fp_in);
	if(ch != '\n')fseek(fp_in, -1, SEEK_CUR);

	/*caso queira que grave em arquivo externo
	 * descomente a linha abaixo

	filename_out = (char*)malloc(sizeof(char) * strlen(filename_in));
	strcpy(filename_out, "\0");
	strncat(filename_out, filename_in, strlen(filename_in) -4);
	strcat(filename_out, pgmformat);

	fp_out = fopen(filename_out, "w");

	fprintf(fp_out,"%s\n", "P1");
	fprintf(fp_out,"%d %d\n", cols, rows);
	fprintf(fp_out, "%d\n", range);

	*/

	for(i = 0; i < rows; i++)
	{
		runlength_decompress_process_row(fp_in, i);
		printf("\n");

		/*caso queira que grave em arquivo externo
		 * descomente a linha abaixo
		 */
		//fprintf(fp_out, "\n");

	}

	fclose(fp_in);


	/*caso queira que grave em arquivo externo
	 * descomente a linha abaixo
	 */
	//free(filename_out);
	//fclose(fp_out);

}


/*
 * Processa cada linha do arquivo compactado
 * Parâmetros:
 *  *fp_in: ponteiro para o arquvo de entrada
 *  i: linha atual
 */
void runlength_decompress_process_row(FILE *fp_in, int i)
{
	char ch;

	do{
		ch = fgetc(fp_in);
		if(ch != '\n'){
			if(ch == 'f') {
				ch = fgetc(fp_in);
				//printf("repetiu! ");
				runlength_decompress_flush_repeated(fp_in);
			}
			else {
				if(ch != ' '){
					printf("%d ", atoi(&ch));
				}

			}


		}

	}
	while(ch != '\n');

}


/*
 * Processa cada linha do arquivo compactado
 * Parâmetros:
 *  *fp_in: ponteiro para o arquvo de entrada
 *  *fp_ou: ponteiro para o arquivo de saida
 *  i: linha atual
 */
void runlength_decompress_process_row_with_fileout(FILE *fp_in, FILE *fp_out, int i)
{
	char ch;

	do{
		ch = fgetc(fp_in);
		if(ch != '\n'){
			if(ch == 'f') {
				ch = fgetc(fp_in);
				//printf("repetiu! ");
				runlength_decompress_flush_repeated_with_fileout(fp_in, fp_out);
			}
			else {
				if(ch != ' '){
					fprintf(fp_out, "%d ", atoi(&ch));
				}

			}


		}

	}
	while(ch != '\n');

}


/*
 * Imprime na saida padrao (stdout) quando houver repeticoes
 * (quando encontrar a string "ff"
 * Parâmetros:
 *  *fp_in: ponteiro para o arquvo de entrada
 */
void runlength_decompress_flush_repeated(FILE *fp_in)
{
	int i, value, times;

	fscanf(fp_in,"%d %d", &value, &times);

	for( i = 0; i < times; i++)
	{
		printf("%d ", value);

	}


}

/*
 * Imprime no arquivo fp_out quando houver repeticoes
 * (quando encontrar a string "ff"
 * Parâmetros:
 *  *fp_in: ponteiro para o arquvo de entrada
 *   *fp_ou: ponteiro para o arquivo de saida
 */
void runlength_decompress_flush_repeated_with_fileout(FILE *fp_in, FILE *fp_out)
{
	int i, value, times;

	fscanf(fp_in,"%d %d", &value, &times);

	for( i = 0; i < times; i++)
	{
		fprintf(fp_out, "%d ", value);

	}


}


