#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "knn.h"


float euclidiana(float *dadoTeste, float *dadoTreino, int colTeste){
        float dis =0;
        int i =0;
        for(i=0; i<(colTeste-1); i++){

                dis = dis + pow((dadoTeste[i]-dadoTreino[i]),2);

        }
        dis = sqrt(dis);
   return dis;
}

float minkowsky(float *dadoTeste, float *dadoTreino, int colTeste, float *r, int posi){
        float dis =0;
        int i=0;
        for(i=0; i<(colTeste-1); i++){
        
                if((dadoTeste[i] - dadoTreino[i]) < 0){
    
                        dis = dis + pow(((dadoTeste[i] - dadoTreino[i])*(-1)),r[posi]);

                }
                else{
                
                        dis = dis + pow((dadoTeste[i] - dadoTreino[i]),r[posi]);

                }        

        }
        dis = pow(dis,1/r[posi]);
   return dis;
}

float chebyshev(float *dadoTeste, float *dadoTreino, int colTeste){
        float dis =0, aux = 0;
        int i=0;
        for(i=0; i<(colTeste -1); i++){

                if((dadoTeste[i] - dadoTreino[i]) < 0){
                
                        aux = (dadoTeste[i] - dadoTreino[i])*(-1);

                }
                else{
                
                        aux = (dadoTeste[i] - dadoTreino[i]);

                }
                if(aux > dis){
                
                        dis = aux;

                }   
        
        }   
   return dis;    
}

Resultado calculaKNN(float **dadoTeste, float **dadoTreino, int colTeste, float *r, int x, int linTeste, int linTreino, char *tipo, int posi, Resultado resultadoCalculo){    
        int i=0,ii = 0, iii = 0;
        for(ii=0;ii<linTeste;ii++){

                for(iii=0;iii<linTreino;iii++){
			
                        switch(tipo[posi]){

                                case 'E':
                                        resultadoCalculo.calculo[ii][iii] = euclidiana(dadoTeste[ii], dadoTreino[iii], colTeste);
                                        resultadoCalculo.rotulo[ii][iii] = dadoTreino[iii][(colTeste-1)];
                                      
                                break;
                                        
                                case 'M':
                                        resultadoCalculo.calculo[ii][iii] = minkowsky(dadoTeste[ii], dadoTreino[iii], colTeste, r, posi);
                                        resultadoCalculo.rotulo[ii][iii] = dadoTreino[iii][(colTeste-1)];
                                break;

                                case 'C':
                                        resultadoCalculo.calculo[ii][iii] = chebyshev(dadoTeste[ii], dadoTreino[iii], colTeste);
                                        resultadoCalculo.rotulo[ii][iii] = dadoTreino[iii][(colTeste-1)];
                                break;

                        }

               }

        }
   return resultadoCalculo;
}























