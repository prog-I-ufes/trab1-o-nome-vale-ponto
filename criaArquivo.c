#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "knn.h"

void criaArquivo(char *predicao, float *acuracia, int **confusao, int *rotulos, int posi, int z, int linTeste){
	FILE *pred; char nome[30] = ""; char va[5]; posi++; int i=0, ii=0, iii=0;
	sprintf(va, "%d", posi);	
	strcpy(nome, predicao);
	strcat(nome, "predicao_");
	strcat(nome, va);
	strcat(nome, ".txt");

	pred = fopen (nome,"w");
	
	pred = fopen (nome,"a");

	fprintf(pred, "%.2f\n", *acuracia);
	fprintf(pred, "\n");

	for(i=0;i<z;i++){

		for(ii=0;ii<z;ii++){

			fprintf(pred, "%d ", confusao[i][ii]);

		}
	fprintf(pred, "\n");

	}
	fprintf(pred, "\n");
	for(iii=0;iii<linTeste;iii++){
		fprintf(pred, "%d\n", (rotulos[iii]-1));
	}

	fclose(pred);
}
