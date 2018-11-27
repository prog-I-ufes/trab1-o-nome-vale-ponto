#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "knn.h"

void criaArquivo(char *predicao, float *acuracia, int **confusao, int *rotulos, int posi, int z, int linTeste){
	FILE *pred; char nome[30] = ""; char va[5]; posi++; int i=0, ii=0, iii=0;
	sprintf(va, "%d", posi);    // converte para char o valor correspondente ao número de vezes que o algoritimo foi rodado
	strcpy(nome, predicao);
	strcat(nome, "predicao_");  // cria o nome do arquivo
	strcat(nome, va);
	strcat(nome, ".txt");

	pred = fopen (nome,"w"); // cria o arquivo
	
	pred = fopen (nome,"a"); // habilita a escrita a partir da ultima linha do arquivo

	fprintf(pred, "%.2f\n", *acuracia); //imprime no arquivo a acurácia
	fprintf(pred, "\n");	// pula uma linha no arquivo

	for(i=0;i<z;i++){

		for(ii=0;ii<z;ii++){

			fprintf(pred, "%d ", confusao[i][ii]); // imprime a matriz confusão no arquivo

		}
	fprintf(pred, "\n"); // pula uma linha no arquivo quando deve imprimir a próxima linha da matriz

	}
	fprintf(pred, "\n"); // pula uma linha no arquivo
	for(iii=0;iii<linTeste;iii++){
		fprintf(pred, "%d\n", (rotulos[iii]-1)); // imprime os rotulos um de baixo do outro
	}

	fclose(pred);
}
