#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Lista.h"


 int main(int argc, char *argv[]) {	
	LISTA* listaPorNome = (LISTA*) malloc(sizeof(LISTA));
	listaPorNome->fim=NULL;
	listaPorNome->inicio=NULL;
	
	LISTA* listaPorCodigo = (LISTA*) malloc(sizeof(LISTA));
	listaPorCodigo->fim=NULL;
	listaPorCodigo->inicio=NULL;
	
	//lerArquivo(listaPorNome, listaPorCodigo);
	exibir(listaPorNome, listaPorCodigo);

	clock_t inicio;
	inicio = clock();
	//int maxcod = 0, mincod=1000000;
	lerArquivo(listaPorNome, listaPorCodigo, "entrada.txt");
	printf("\n tempo para ler 10 arquivos %f ", (double)(clock()-inicio)/CLOCKS_PER_SEC);
	
	//clock_t inicio;
	inicio = clock();
	//int maxcod = 0, mincod=1000000;
	lerArquivo(listaPorNome, listaPorCodigo, "entrada100k.txt");
	printf("\n tempo para ler 100k arquivos %f ", (double)(clock()-inicio)/CLOCKS_PER_SEC);	
	
	//exibir(listaPorNome, listaPorCodigo);
	return 0;
}


void lerArquivo(LISTA* listaPorNome, LISTA* listaPorCodigo, char url[]){
	char info[50];
	FILE *arq;
	arq = fopen(url, "r");
	if(arq == NULL) printf("Erro, nao foi possivel abrir o arquivo\n");
	else{
		while( (fgets(info, 50, arq))!=NULL ){
			char codAux[10];
			int cod;
			char nome[50];
			double area = 4.20;
			int tamanho = 50; 
			
		    char *token = strtok(info, ";");
		    
		    cod = atoi(token);
	        token = strtok(NULL, ";");
	        strcpy(nome, token);
	        
	        inserir(listaPorNome, listaPorCodigo, nome, cod, area);
		}
	}
	fclose(arq);
}
    














