/*
 * main.c
 *
 *  Created on: May 8, 2013
 *      Author: emanuel
 */
#include <stdlib.h>
#include <stdio.h>

#include "runlength.h"


int main(int argc, char * argv[])
{
	FILE *fp;

	if(argc != 2)
	{
		printf("usage %s <filename>\n", argv[0]);
		exit(1);
	}

	fp = fopen(argv[1], "r");

	runlength_init(fp);

	//myprint();

	fclose(fp);
	return 0;
}
