#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
// printf("\n%s\n",treino);
// printf("\n%s\n",teste);
//  printf("\n%s\n",predicao);
		int w=0;
//printf("o valor de x eh igual a %d\n",x);
//	printf("\n");
		for(w=3;w<x;w++)
		{	
		fscanf(conf, "%d, %c, %f",&k[(w-3)], &tipo[(w-3)], &r[(w-3)]);
//printf("%d %c %.2f\n",k[(w-3)], tipo[(w-3)], r[(w-3)]);
		}
      fclose(conf);
	return;
}

int contaConfig(FILE *conf){ // a funçao conta quantas linhas config.txt possui
        char tx1[30]=" "; 
        int x=0;       
        while(!feof(conf)){
        fgets(tx1, 30, conf);
	x++;
        }
        x--;
        //printf("o arquivo tem %d linhas\n",x);
        return x;
}

void contaCSV(char *treino, char *teste, FILE *csvteste, FILE *csvtreino, int *linTeste, int *colTeste, int *linTreino, int *colTreino){ // a função lê o número de linhas e colunas do teste e do treino
        csvteste = fopen (teste,"r");
        char tx1[30], letra;  
        while(!feof(csvteste)){
                fgets(tx1, 30, csvteste);   // faz leitura do número de linhas do teste.csv
                *linTeste = *linTeste + 1;
        }
        *linTeste = *linTeste - 1;
        
        csvteste = fopen (teste,"r");
        while(!feof(csvteste)){
                fscanf(csvteste, "%c", &letra);
                if (letra == ',')
                {
                        *colTeste = *colTeste + 1; // faz leitura do número de colunas do teste.csv
                }
                if (letra == '\n')
                {
                        break;
                }  
        }
        *colTeste = *colTeste + 1; //o numero de caracteristicas é o numero de virgulas +1 
        // printf("\n\n\n %d eh o numero de linhas\n\n\n",linTeste);
        // printf("\n\n\n %d eh o numero de colunas\n\n\n",colTeste);
  
        csvtreino = fopen (treino,"r");
        while(!feof(csvtreino)){
                fgets(tx1, 30, csvtreino);   // faz leitura do número de colunas do treino.csv
                *colTreino = *colTreino + 1;
        }
        *colTreino = *colTreino - 1;
        
        csvtreino = fopen (teste,"r");
        while(!feof(csvtreino)){
                fscanf(csvtreino, "%c", &letra);
                if (letra == ',')
                {
                        *linTreino = *linTreino + 1; // faz leitura do número de linhas do treino.csv
                }
                if (letra == '\n')
                {
                        break;
                }  
        }
        *linTreino = *linTreino + 1; //o numero de caracteristicas é o numero de virgulas +1

        fclose(csvtreino);
        fclose(csvteste);
        return;
}



int main (){
        FILE *conf, *csvteste, *csvtreino; // *conf é um ponteiro do tipo arquivo para o arquivo config.txt
        int x=0, *k, linTeste = 0, colTeste = 0, colTreino = 0, linTreino = 0; // x é uma variável para contar quantas linhas config.txt possui; *k é um ponteiro para um vetor dinâmico que armazena os valores de k
        int *liNTeste = &linTeste, *coLTeste = &colTeste, *coLTreino = &colTreino, *liNTreino = &linTreino;
	float *r; // *r é um ponteiro para um vetor dinãmico que armazena os valores de r quando eles existem
        char treino[30], teste[30], predicao[30], *tipo; // Strings que armazenam os endereços em que paramêtros estão e um vetor de caracteres para a configuração dos calculos
        conf = fopen(CONFIG, "r");
        
        testeAbrirArquivo(conf);
        
        x = contaConfig(conf);
            k = (int *)malloc((x-3) * sizeof(int));
            r = (float *)malloc((x-3) * sizeof(float)); // faz a alocação dos vetores que armazenarão os valores para configurar os calculos
            tipo = (char *)malloc((x-3) * sizeof(char));
         recebeConfig(conf, treino, teste, predicao, x, k, tipo, r);
         contaCSV(treino, teste, csvteste, csvtreino, liNTeste, coLTeste, coLTreino, liNTreino);
  /*       printf("\n\n\n %d eh o numero de linhas\n\n\n",linTeste);
         printf("\n\n\n %d eh o numero de colunas\n\n\n",colTeste);
         printf("\n\n\n %d eh o numero de linhas\n\n\n",linTreino);
         printf("\n\n\n %d eh o numero de colunas\n\n\n",colTreino);*/
   free(k); 
   free(r);
   free(tipo);
        //liberaMemoria(kk, rr, titipo);       
return 0;
}
