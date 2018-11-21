#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void testeAbrirArquivo(FILE * conf){
        if (conf == NULL)
        {
                printf("Erro na abertura de arquivo! \n O programa serah abortado...\n");
                exit(1);
        }
	return;
}

void recebeConfig(FILE *conf, char *treino, char *teste, char *predicao, int x, int *k, char *tipo, float *r){
        conf = fopen("bateria_validacao/iris/config.txt", "r");
        fscanf(conf, "%s\n%s\n%s", treino, teste, predicao);
        printf("%s\n",treino);
        printf("%s\n",teste);
        printf("%s\n",predicao);
		int w=0;
		printf("o valor de x eh igual a %d\n",x);
		k = (int *)malloc((x-3) * sizeof(int));
		r = (float *)malloc((x-3) * sizeof(float));
		tipo = (char *)malloc((x-3) * sizeof(char));
		printf("\n");
		for(w=3;w<x;w++)
		{	
		fscanf(conf, "%d, %c, %f",&k[(w-3)], &tipo[(w-3)], &r[(w-3)]);
		printf("%d %c %.2f\n",k[(w-3)], tipo[(w-3)], r[(w-3)]);
		}
	return;
}

int contaLinhas(FILE *conf){
        char tx1[30]; 
        int x=0;       
        while(!feof(conf)){
        fgets(tx1, 30, conf);
	x++;
        }
	x--;
	printf("o arquivo tem %d linhas\n",x);
        return x;
}

void liberarMemoria(FILE *conf, int *k, float *r, char *tipo){

	fclose(conf);
	//free(k);
	//free(r);
	//free(tipo);
	return;
}
int contaCaracteristica(FILE *arquivo)
{
        int nVirgulas=0;
        char letra;
        rewind(arquivo);
        while(!feof(arquivo)){
                fscanf(letra, 1, arquivo);
                if(letra ==',')
                {
                        nVirgulas++
                }
                if(letra =='\n')
                {
                        break;
                }
	nVirgulas++ //o numero de caracteristicas é o numero de virgulas +1   
        }
        return nVirgulas;

}
void lePlanilha(FILE *file, int nvirgulas);
{
        int l=0,c=0;
        float *VFeatures;
        VFeatures = ((float**))malloc(nvirgulas*(sizeof(float*))// aloca as colunas
        //botar o feof aqui pra o arquivo ler até o fim 
        for(c=0;c<=nvirgulas;c++)//preenche as colunas
        {
                fscanf(file,"%s, ",VFeatures[l][c]);
        }
        
        l++
        
        for (c = 0; c <= nvirgulas; i++)// aloca mais uma linha
        {
	        VFeatures[l] = (float *) realloc (VFeatures[l], sizeof (float) * (l + 1)); 
        }
        
        
        
}

int main (){
        FILE *conf,*teste; // *conf é um ponteiro do tipo arquivo para o arquivo config.txt
        int x=0, *k, nvirguas=0; // x é uma variável para contar quantas linhas config.txt possui; *k é um ponteiro para um vetor dinâmico que armazena os valores de k
	float *r; // *r é um ponteiro para um vetor dinãmico que armazena os valores de r quando eles existem
        char treino[30], teste[30], predicao[30], *tipo; //
        
        conf = fopen("bateria_validacao/iris/config.txt", "r");
        teste= fopen("dataset/iris_teste.csv", "r")
        nvirgulas = contaCaracteristica(teste);
        lePlanilha(*teste, nvirgulas);

        testeAbrirArquivo(conf);
        
        x = contaLinhas(conf);

        recebeConfig(conf, treino, teste, predicao, x, k, tipo, r);

	contaCaracteristica()
        liberarMemoria(conf, k, r, tipo);
        
return 0;
}