#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "knn.h"

void comparador (float **testeCSV, int *rotulos, int linTeste, int colTeste, float *acuracia, int **confusao, int z){
	int i=0, j=0;
	*acuracia = 0;
	for (i=0;i<linTeste;i++){
	
		if(rotulos[i]==testeCSV[i][(colTeste-1)]){ // verifica se acertou na predição, ou seja, verifica se o rotulo dado é igual ao rotulo real			
			
			*acuracia = *acuracia + 1; // acrescenta mais um aos acertos
			confusao[(((int)testeCSV[i][(colTeste-1)])-1)][(rotulos[i]-1)] = confusao[(((int)testeCSV[i][(colTeste-1)])-1)][(rotulos[i]-1)] + 1; //adiciona mais um na posião da matriz confusão, usando os valores dos rotulos como coordenadas, representando acerto na predição
	
		}
		else{

			confusao[(((int)testeCSV[i][(colTeste-1)])-1)][(rotulos[i]-1)] = confusao[(((int)testeCSV[i][(colTeste-1)])-1)][(rotulos[i]-1)] + 1; // adiciona mais um na posião da matriz confusão, usando os valores dos rotulos como coordenadas, porém representa predição errada
	
		}
	
	}
	
	*acuracia = ((*acuracia/linTeste)*100); //calcula a acurácia
return;
}
