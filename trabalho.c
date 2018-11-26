#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "knn.h"

#define CONFIG "iris/config.txt"


void testeAbrirArquivo(FILE * conf){ // a função tenta abrir o arquivo config.txt
        if (conf == NULL)
        {
                printf("Erro na abertura de arquivo! \n O programa serah abortado...\n");
                exit(1);
        }
	return;
}

void recebeConfig(FILE *conf, char *treino, char *teste, char *predicao, int x, int *k, char *tipo, float *r){ // a função recebe todas as linhas do arquivo config.txt
        conf = fopen(CONFIG, "r");
        fscanf(conf, "%s\n%s\n%s", treino, teste, predicao);
/*printf("\n%s\n",treino);
printf("\n%s\n",teste);
printf("\n%s\n",predicao);*/
//printf("o valor de x eh igual a %d\n",x);
//printf("\n");
                int w=0;
		for(w=3;w<x;w++)
		{	
		fscanf(conf, "%d, %c, %f",&k[(w-3)], &tipo[(w-3)], &r[(w-3)]);
//printf("%d %c %.2f\n",k[(w-3)], tipo[(w-3)], r[(w-3)]);
		}
      fclose(conf);
	return;
}

int contaConfig(FILE *conf, int *tamTreino, int *tamTeste, int* tamPredicao){ 
        char letra; 
        int x=0, z =0;       
        while(!feof(conf)){
        fscanf(conf, "%c", &letra); 
                if (letra == '\n')
                {
                        x++; // conta quantas linhas config.txt possui
                }
        }
        x--;
//printf("o arquivo tem %d linhas\n",x);
        char le;
        rewind(conf);
                while(!feof(conf)){
        fscanf(conf, "%c", &le);
                if (le == '\n')
                {
                        z++;
                }
                if (z==0)
                {
                        *tamTreino = *tamTreino + 1;  // conta quantos caracteres tem o endereço do arquivo de treino
                }
                if (z==1)
                {
                        *tamTeste = *tamTeste + 1; // conta quantos caracteres tem o endereço do arquivo de teste
                }
                if (z==2)
                {
                        *tamPredicao = *tamPredicao + 1; // conta quantos caracteres tem o endereço do arquivo de predicao
                }
        }
        *tamTreino = *tamTreino + 1;
        *tamTeste = *tamTeste + 1;
        *tamPredicao = *tamPredicao + 1;
/*printf("\no arquivo tem %d linhas\n",x);
printf("\nteste tem %d caracteres\n",*tamTeste);
printf("\ntreino tem %d caracteres\n",*tamTreino);
printf("\npredicao tem %d caracteres\n",*tamPredicao);*/
        return x;
}

void contaCSV(char *local, FILE *csvConta, int *linConta, int *colConta){ // a função lê o número de linhas e colunas do teste e do treino
        csvConta = fopen (local,"r");
        char letra;  
        while(!feof(csvConta)){
                fscanf(csvConta, "%c", &letra); // faz leitura do número de linhas
                if (letra == '\n')
                {
                        *linConta = *linConta + 1;
                }  
        }
        *linConta = *linConta - 1; // ele conta uma linha a mais
        
        csvConta = fopen (local,"r");
        while(!feof(csvConta)){
                fscanf(csvConta, "%c", &letra);
                if (letra == ',')
                {
                        *colConta = *colConta + 1; // faz leitura do número de colunas
                }
                if (letra == '\n')
                {
                        break;
                }  
        }
        *colConta = *colConta + 1; //o numero de caracteristicas é o numero de virgulas +1 
// printf("\n\n\n %d eh o numero de 0 linhas\n\n\n",*linConta);
// printf("\n\n\n %d eh o numero de 0 colunas\n\n\n",*colConta);
        fclose(csvConta);
        return;
}

void recebeTabela(FILE *csvTabela, char *local, int linTabela, int colTabela, float **posiTabela){  // coloca os valores da tabela em uma matriz
        csvTabela = fopen (local,"r");
        float val=0; int i=0,u=0; char le;
        for(i=0;i<linTabela;i++){        
                for(u=0;u<colTabela;u++){                
                                fscanf(csvTabela, "%f", &val);  // recebe o valor da coluna para uma variável auxiliar
                                posiTabela[i][u] = val; // coloca na matriz o valor na variável auxiliar
                                fscanf(csvTabela, "%c", &le); // recebe a virgula que separa cada valor da tabela e também recebe o caracter que indica fim da linha (trocadilho não proposital)
//printf(" %.2f ",posiTabela[i][u]);
                }
//printf("\n\n");
        }
}


void libera(int *k, float *r, char *tipo, char *teste, char *treino, char *predicao, float **testeCSV, float **treinoCSV, int liNTeste, int liNTreino, float** resultadoCalculo, float **rotulo, int *rotulos){  // faz free em todos os ponteiros
   
        int i=0;
        for (i=0;i<(liNTeste);i++){     //faz o free na matriz
                free(testeCSV[i]);
        }
        free(testeCSV);                 //faz o free na matriz
        for (i=0;i<(liNTreino);i++){
                free(treinoCSV[i]);
        }
        free(treinoCSV);
        for (i=0;i<(liNTeste);i++){
                free(resultadoCalculo[i]);
        }
        free(resultadoCalculo);
        for (i=0;i<(liNTeste);i++){
                free(rotulo[i]);
        }
        free(rotulo);
	
	free(rotulos);
        free(treino);
        free(teste);
        free(predicao);
        free(k); 
        free(r);
        free(tipo);
}


int main (){
        Resultado resultadoCalculo;
        FILE *conf, *csvteste, *csvtreino; // *conf é um ponteiro do tipo arquivo para o arquivo config.txt
        int  linTeste = 0, colTeste = 0, colTreino = 0, linTreino = 0, tamTeste = 0, tamTreino = 0, tamPredicao = 0, i = 0, z = 0; // variáveis que não precisam de ponteiro
        int x=0, posi, pposi, *k, *rotulos, **confusao;// x é uma variável para contar quantas linhas config.txt possui; *k é um ponteiro para um vetor dinâmico que armazena os valores de k
	float *r, **testeCSV, **treinoCSV, acuracia = 0; // *r é um ponteiro para um vetor dinãmico que armazena os valores de r quando eles existem
        char *treino, *teste, *predicao, *tipo; // Strings que armazenam os endereços em que paramêtros estão e um vetor de caracteres para a configuração dos calculos
        conf = fopen(CONFIG, "r");
        
        testeAbrirArquivo(conf);
        
        x = contaConfig(conf, &tamTreino, &tamTeste, &tamPredicao);

   k = (int *)malloc((x-3) * sizeof(int));
   r = (float *)malloc((x-3) * sizeof(float)); // faz a alocação dos vetores que armazenarão os valores para configurar os calculos
   tipo = (char *)malloc((x-3) * sizeof(char));

   teste = (char *)malloc((tamTeste) * sizeof(char));
   treino = (char *)malloc((tamTreino) * sizeof(char)); // faz a alocação dos vetores que armazenarão os valores para configurar os calculos
   predicao = (char *)malloc((tamPredicao) * sizeof(char));
        
        recebeConfig(conf, treino, teste, predicao, x, k, tipo, r); // recebe as informações contidas no config.txt
         
        contaCSV(teste, csvteste, &linTeste, &colTeste);
        contaCSV(treino, csvtreino, &linTreino, &colTreino );
        
   testeCSV = (float**) malloc (linTeste*(sizeof(float *))); // aloca as linhas da matriz
   for (i=0; i<linTeste;i++){

           testeCSV[i] = (float*) malloc (colTeste*(sizeof(float))); // aloca as colunas da matriz

   }
   treinoCSV = (float**) malloc (linTreino*(sizeof(float *)));  // aloca as linhas da matriz
   for (i=0; i<linTreino;i++){

           treinoCSV[i] = (float*) malloc (colTreino*(sizeof(float))); // aloca as colunas da matriz

   }
   
   resultadoCalculo.calculo = (float**) malloc (linTeste*(sizeof(float *)));  // aloca as linhas da matriz
   for (i=0; i<linTeste;i++){

           resultadoCalculo.calculo[i] = (float*) malloc (linTreino*(sizeof(float))); // aloca as colunas da matriz

   }
   resultadoCalculo.rotulo = (float**) malloc (linTeste*(sizeof(float *)));  // aloca as linhas da matriz
   for (i=0; i<linTeste;i++){

           resultadoCalculo.rotulo[i] = (float*) malloc (linTreino*(sizeof(float))); // aloca as colunas da matriz

   }


   rotulos = (int*) malloc (linTeste*(sizeof(int)));  // aloca as linhas da matriz

        recebeTabela(csvteste, teste, linTeste, colTeste, testeCSV); // recebe os valores da tabela e armazenas na matriz correspondente
//printf("\n\n\n");
        recebeTabela(csvtreino, treino, linTreino, colTreino, treinoCSV); // recebe os valores da tabela e armazenas na matriz correspondente

/*printf("\n\n\n %d eh o numero de linhas do teste\n\n\n",linTeste);
printf("\n\n\n %d eh o numero de colunas do teste\n\n\n",colTeste);    
printf("\n\n\n %d eh o numero de 2 linhas do treino\n\n\n",linTreino);
printf("\n\n\n %d eh o numero de 2 colunas do treino\n\n\n",colTreino);*/


for(posi=0;posi<(x-3);posi++){
	resultadoCalculo = calculaKNN(testeCSV, treinoCSV, colTeste, r, x, linTeste, linTreino, tipo, posi, resultadoCalculo);// armazena na variável os resultados dos calculos e os rotulos correspondentes

	for(pposi=0;pposi<linTeste;pposi++){
	i=0;
	ordena(resultadoCalculo.calculo[pposi], i, (linTreino-1),resultadoCalculo.rotulo[pposi] );

	}
	rotulos = rotulador(resultadoCalculo, k, rotulos, linTeste, linTreino, posi);
	z = numeroDeRotulos(resultadoCalculo, linTeste, linTreino);
	confusao = (int**) malloc (z*(sizeof(int *)));  // aloca as linhas da matriz
   for (i=0; i<z;i++){

           confusao[i] = (int *) malloc (z*(sizeof(int))); // aloca as colunas da matriz

   }
	comparador (testeCSV, rotulos, linTeste, colTeste, &acuracia, confusao, z);
	
/*for(i=0;i<z;i++){	

	for(pposi=0;pposi<z;pposi++){
		printf("%d ",confusao[i][pposi]);
	}
	printf("\n");
}
printf("\n"); */
/*if(posi == 1){
for(pposi=0;pposi<linTreino;pposi++){
printf("\n\n%.2f  %.2f\n\n",resultadoCalculo.calculo[1][pposi],resultadoCalculo.rotulo[1][pposi]);
}
}*/
//printf("\n\n%f\n\n",resultadoCalculo.rotulo[posi][0]);
/*	for(pposi=0;pposi<linTeste;pposi++){
	printf("\nrotulo %d\n",rotulos[pposi]);
	}*/
	for (i=0;i<(z);i++){
                free(confusao[i]);
        }
        free(confusao);
}



libera(k, r, tipo, teste, treino, predicao, testeCSV, treinoCSV, linTeste, linTreino, resultadoCalculo.calculo, resultadoCalculo.rotulo, rotulos); // faz o free em todos os ponteiros
return 0;
}
