#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void testeAbrirArquivo(FILE * arq){
        if (arq == NULL)
        {
                printf("Erro na abertura de arquivo! \n O programa serah abortado...\n");
                exit(1);
        }
}

void recebePatch(FILE *conf, char *tx1, char *tx2, char *tx3){
        conf = fopen("bateria_validacao/iris/config.txt", "r");
        fscanf(conf, "%s\n%s\n%s", &tx1, &tx2, &tx3);
        printf("%s\n",tx1);
        printf("%s\n",tx2);
        printf("%s\n",tx3);
        printf("o arquivo tem %d linhas\n",x);
}

int contaLinhas(FILE *conf){
        char tx1[30]; 
        int x=0;       
        while(!feof(conf)){
        fgets(tx1, 30, conf);
	x++;
        }
	x--;
	printf("%d\n",x);
        return x;
}

int main (){
        FILE *conf;
        int x=0;
        char *tx1[30], *tx2[30], *tx3[30];
        conf = fopen("bateria_validacao/iris/config.txt", "r");
        
        testeAbrirArquivo(conf);
        
        x = contaLinhas(conf);       

        recebePatch(conf, tx1, tx2, tx3);        

        fclose(conf);
return 0;
}
