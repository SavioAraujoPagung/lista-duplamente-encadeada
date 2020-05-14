#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cidade.h"
//#define QTD 10000
#define TAM_NOME 11
#define MAX_POP 1000000


char vogais[5]={'a','e','i','o','u'};


void iniciaCodigos(int *usado, int QTD){
	int i;
	for (i=0;i<QTD;i++)
		usado[i]=0;
}


int geraCodigo(int *usado, int QTD){
	int r1 = rand();
	int r2 = rand();
	int codigo;
//Como RAND_MAX é 32657 e a quantidade de elementos que quero gerar pode ser maior que isso, gero um numero entre 0 e 1 e multiplico QTD

	if (r1<r2)
	    codigo = ((double)r1)/((double)r2) * QTD;
	else
		codigo = ((double)r2)/((double)r1) * QTD;
	if (codigo == QTD) codigo--;
	while(usado[codigo]){
		codigo = (codigo+1)%QTD;
	}
	usado[codigo]=1;
	return codigo+1;
}
int ehVogal(char letra){
	if (letra=='a' ||letra=='e' ||letra=='i' ||letra=='o' ||letra=='u' ||letra=='A' ||letra=='E' ||letra=='I' ||letra=='O' ||letra=='U')
		return 1;
	else
		return 0;
}

char geraLetraMaiuscula(){
	return rand()%26+65;
}

char geraLetraMinuscula(){
	return rand()%26+97;
}

char geraVogal(){
	return vogais[rand()%5];
}

char* geraPalavra(){
	int i;
	char *palavra = (char *) malloc (TAM_NOME * sizeof(char));
	palavra[0]= geraLetraMaiuscula();
	for(i=1;i<TAM_NOME;i++){
		if (ehVogal(palavra[i-1]))
			palavra[i]=geraLetraMinuscula();
		else
			palavra[i]=geraVogal();
	}
	palavra[i]='\0';
	return palavra;
}

void main(int argc, char *argv[]){
	int QTD = 1000;//atoi (argv[1]);
	TCidade *v = (TCidade *) malloc (QTD * sizeof(TCidade));
	int *usado = (int *) malloc(QTD * sizeof(int));
	int i,j;
	char letra, letra_ant;
	FILE *arq;
	arq = fopen("entrada.txt", "w");
	iniciaCodigos(usado, QTD);
	clock_t inicio;
	inicio = clock();
	int maxcod = 0, mincod=1000000;
	for (i=0;i<QTD;i++){
		v[i].nome =geraPalavra();
		v[i].codigo = geraCodigo(usado, QTD);
		fprintf(arq,"%d;%s\n",v[i].codigo,v[i].nome);
		if (v[i].codigo < mincod)
			mincod = v[i].codigo;
		if (v[i].codigo > maxcod)
			maxcod = v[i].codigo;
	 	if (i%1000==0)
			printf("\n %d gerados em %f - %d - %d",i, (double)(clock()-inicio)/CLOCKS_PER_SEC, mincod, maxcod);
	}
	printf("\n %d gerados em %f - %d - %d, %d, %d",i, (double)(clock()-inicio)/CLOCKS_PER_SEC, mincod, maxcod,clock(), inicio);
	fclose(arq);	
}
