#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void testeAbrirArquivo(FILE * conf){ // a função tenta abrir o arquivo config.txt
        if (conf == NULL)
        {
                printf("Erro na abertura de arquivo! \n O programa serah abortado...\n");
                exit(1);
        }
	return;
}

void recebeConfig(FILE *conf, char *treino, char *teste, char *predicao, int x, int *k, char *tipo, float *r){ // a função recebe todas as linhas do arquivo config.txt
        conf = fopen("bateria_validacao/iris/config.txt", "r");
        fscanf(conf, "%s\n%s\n%s", treino, teste, predicao);
//   printf("%s\n",treino);
//   printf("%s\n",teste);
//   printf("%s\n",predicao);
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

int contaLinhas(FILE *conf){ // a funçao conta quantas linhas config.txt possui
        char tx1[30]; 
        int x=0;       
        while(!feof(conf)){
        fgets(tx1, 30, conf);
	x++;
        }
	x--;
//	printf("o arquivo tem %d linhas\n",x);
        return x;
}

int main (){
        FILE *conf; // *conf é um ponteiro do tipo arquivo para o arquivo config.txt
        int x=0, *k; // x é uma variável para contar quantas linhas config.txt possui; *k é um ponteiro para um vetor dinâmico que armazena os valores de k
	     float *r; // *r é um ponteiro para um vetor dinãmico que armazena os valores de r quando eles existem
        char treino[30], teste[30], predicao[30], *tipo; // Strings que armazenam os endereços em que paramêtros estão e um vetor de caracteres para a configuração dos calculos
        conf = fopen("bateria_validacao/iris/config.txt", "r");
        
        testeAbrirArquivo(conf);
        
        x = contaLinhas(conf);
         k = (int *)malloc((x-3) * sizeof(int));
		   r = (float *)malloc((x-3) * sizeof(float)); // faz a alocação dos vetores que armazenarão os valores para configurar os calculos
		   tipo = (char *)malloc((x-3) * sizeof(char));
        recebeConfig(conf, treino, teste, predicao, x, k, tipo, r);

free(k); // os free estão funcionando, pois os frees tem que estar na mesma função que fez a malloc
free(r);
free(tipo);       
return 0;
}
