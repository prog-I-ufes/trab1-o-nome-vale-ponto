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
/*printf("\n%s\n",treino);
printf("\n%s\n",teste);
printf("\n%s\n",predicao);*/
		int w=0;
//printf("o valor de x eh igual a %d\n",x);
//printf("\n");
		for(w=3;w<x;w++)
		{	
		fscanf(conf, "%d, %c, %f",&k[(w-3)], &tipo[(w-3)], &r[(w-3)]);
//printf("%d %c %.2f\n",k[(w-3)], tipo[(w-3)], r[(w-3)]);
		}
      fclose(conf);
	return;
}

int contaConfig(FILE *conf, int *tamTreino, int *tamTeste, int* tamPredicao){ // a funçao conta quantas linhas config.txt possui
        char letra; 
        int x=0, z =0;       
        while(!feof(conf)){
        fscanf(conf, "%c", &letra);
                if (letra == '\n')
                {
                        x++;
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
                        *tamTreino = *tamTreino + 1;
                }
                if (z==1)
                {
                        *tamTeste = *tamTeste + 1;
                }
                if (z==2)
                {
                        *tamPredicao = *tamPredicao + 1;
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

void contaCSV(char *local, FILE *csvConta, long int *linConta, long int *colConta){ // a função lê o número de linhas e colunas do teste e do treino
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




int main (){
        FILE *conf, *csvteste, *csvtreino; // *conf é um ponteiro do tipo arquivo para o arquivo config.txt
      long int  linTeste = 0, colTeste = 0, colTreino = 0, linTreino = 0;
        int tamTeste = 0, tamTreino = 0, tamPredicao = 0; 
      long  int *liNTeste = &linTeste, *coLTeste = &colTeste, *coLTreino = &colTreino, *liNTreino = &linTreino; // declara ponteiros do tipo int
        int x=0, *k;// x é uma variável para contar quantas linhas config.txt possui; *k é um ponteiro para um vetor dinâmico que armazena os valores de k
	float *r; // *r é um ponteiro para um vetor dinãmico que armazena os valores de r quando eles existem
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
        
         recebeConfig(conf, treino, teste, predicao, x, k, tipo, r);
         contaCSV(teste, csvteste, liNTeste, coLTeste);

         contaCSV(treino, csvtreino, liNTreino,coLTreino );
/*printf("\n\n\n %ld eh o numero de linhas do teste\n\n\n",linTeste);
printf("\n\n\n %ld eh o numero de colunas do teste\n\n\n",colTeste);    
printf("\n\n\n %ld eh o numero de 2 linhas do treino\n\n\n",linTreino);
printf("\n\n\n %ld eh o numero de 2 colunas do treino\n\n\n",colTreino);*/
   
   free(treino);
   free(teste);
   free(predicao);
   free(k); 
   free(r);
   free(tipo);
      
return 0;
}
