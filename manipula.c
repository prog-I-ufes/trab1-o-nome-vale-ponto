#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "knn.h"

void ordena(float *vetor, int posicaoInicio, int posicaoFim, float *rotulo) {
	int i, j, k, metadeTamanho;
	float *vetorTemp, *rotuloTemp;
	if(posicaoInicio == posicaoFim){

	return;

	}
	metadeTamanho = (posicaoInicio + posicaoFim ) / 2;

	ordena(vetor, posicaoInicio, metadeTamanho, rotulo);
	ordena(vetor, metadeTamanho + 1, posicaoFim, rotulo);

	i = posicaoInicio;
	j = metadeTamanho + 1;
	k = 0;
	vetorTemp = (float *) malloc(sizeof(float) * (posicaoFim - posicaoInicio + 1));
	rotuloTemp = (float *) malloc(sizeof(float) * (posicaoFim - posicaoInicio + 1));

	while(i < metadeTamanho + 1 || j  < posicaoFim + 1) {
		if (i == metadeTamanho + 1 ) { 
			vetorTemp[k] = vetor[j];
			rotuloTemp[k] = rotulo[j];
			j++;
			k++;
		}
		else {
			if (j == posicaoFim + 1) {
				vetorTemp[k] = vetor[i];
				rotuloTemp[k] = rotulo[i];
				i++;
				k++;
				}
			else {
					if (vetor[i] < vetor[j]) {
						vetorTemp[k] = vetor[i];
						rotuloTemp[k] = rotulo[i];
						i++;
						k++;
						}
				else {
					vetorTemp[k] = vetor[j];
					rotuloTemp[k] = rotulo[j];
					j++;
					k++;
				}
			}
		}

	}
	for(i = posicaoInicio; i <= posicaoFim; i++) {
		vetor[i] = vetorTemp[i - posicaoInicio];
		rotulo[i] = rotuloTemp[i - posicaoInicio];
		}
	free(vetorTemp);
	free(rotuloTemp);
}
