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

float numeroDeRotulos(Resultado resultado, int linTeste, int linTreino){ // conta o número de rotulos a partir do maior rotulo encontrado
	int y=0, z=0;
	float x=0, v=0;
	for(z=0;z<linTeste;z++){

		for(y=0;y<linTreino;y++){

			x = resultado.rotulo[z][y];
			if(x>v){
	
				v = x;

			}
		}

	}

return v;
}

int* rotulador(Resultado resultado, int *k, int *rotulos, int linTeste,int linTreino, int posi) { // rotula os testes
	int i=0, g=0, *y, x=0, a=0, d=0;
	float z=0;
	z = numeroDeRotulos(resultado, linTeste, linTreino);// recebe o número de rotulos existentes
	for(i=0;i<linTeste;i++){
	y = (int *)malloc((z) * sizeof(int));
	for(x=0;x<z;x++){
			y[x]=0;  // este for serve apenas para o valgrind parar de mostrar erro de variável não inicializada

		}
		for(x=0;x<k[posi];x++){
			g =(int) resultado.rotulo[i][x]; // recebe o valor do rotulo k vezes
			y[(g-1)] = y[(g-1)] + 1; // no vetor do numero de rotulos, a posição correspondente ao rotulo ganha mais um para fins comparativos
		}
		d=0;
		for(x=0;x<z;x++){
			//printf("\n%d %d\n",y[x], x);
			if(y[x]>d){ // se a posição no vetor tiver valor maior então recebe aquela posição, os empates são resolvidos aqui, pois se for igual ele ignora, assim pegando o primeiro rotulo do empate

				d = y[x]; // recebe o valor correspondente a quantas amostras possui aquele rotulo
				a = x; // recebe o valor de qual rotulo deve rotular a amostra

			}

		}
		rotulos[i]=(a+1); //rotula na posição da amostra
		//printf("\nrotulo determinado %d \n",rotulos[i]);
	free(y);
	}

	return rotulos;
}
