all: trab

trab: trab1.o distancia.o manipula.o confusao.o criaArquivo.o
	gcc trab1.o distancia.o manipula.o confusao.o criaArquivo.o -o trabalho -lm

trab1.o: trab1.c
	gcc -c trab1.c -lm -g

distancia.o: distancia.c knn.h
	gcc -c distancia.c -lm -g

manipula.o: manipula.c knn.h
	gcc -c manipula.c -g

confusao.o: confusao.c knn.h
	gcc -c confusao.c -g

criaArquivo.o: criaArquivo.c knn.h
	gcc -c criaArquivo.c -g

val:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./trabalho

clean:
	rm *.o

exe:
	./trabalho
