#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"

int listaVazia(LISTA *lista){
	if ((lista->inicio == NULL)&&(lista->fim == NULL)) return 0;
	else return 1;
}

void exibir(LISTA *porNome, LISTA *porCodigo){
	printf("\n==============================================\n");
	NO *no = (NO*) malloc(sizeof(NO));
	if(no == NULL){
		printf("\nLista vazia\n");
	}
	
	printf("\tLISTAR POR NOME\n");
	printf("\t------\n");
	no = porNome->inicio;
	
	while(no!=NULL){
		printf("nome = %s\n", no->cidade->nome);
		printf("codigo = %d\n", no->cidade->codigo);
		//printf("area = %f\n", no->cidade->area);
		printf("-----------------------------\n");
		no = no->proximo;
	}
	printf("\t------\n");
	printf("\n\n\tLISTAR POR CODIGO\n");
	printf("\t------\n");
	no = porCodigo->inicio;
	while(no!=NULL){
		printf("nome = %s\n", no->cidade->nome);
		printf("codigo = %d\n", no->cidade->codigo);
		//printf("area = %f\n", no->cidade->area);
		printf("-----------------------------\n");
		no = no->proximo;
	}
	printf("\t------\n");
	printf("\n==============================================\n");
}

void inserir(LISTA *porNome, LISTA *porCodigo, char nome[50], int codigo, double area){
	NO *aux = (NO*) malloc(sizeof(NO));
	NO *noNome = (NO*) malloc(sizeof(NO));
	NO *noCodigo = (NO*) malloc(sizeof(NO));
	CIDADE *cidade = (CIDADE*) malloc(sizeof(CIDADE));
	
	//atributos de cidade
	strcpy(cidade->nome, nome);
	cidade->codigo = codigo;
	cidade->area = area;
	//printf("nome: %s cod: %d\n", cidade->nome, cidade->codigo);
	//atributos de no
	noNome->anterior = NULL;
	noNome->proximo = NULL;
	noNome->cidade = cidade;
	
	noCodigo->anterior = NULL;
	noCodigo->proximo = NULL;
	noCodigo->cidade = cidade;
	
	//======== add por codigo ========
	aux = porCodigo->inicio;
	if (aux==NULL){
		porCodigo->inicio = noCodigo;
		porCodigo->fim = noCodigo;
		
	}else{
		//(aux!=NULL)&&
		while((aux->cidade->codigo < noCodigo->cidade->codigo)){
			//encontrar o lugar
			if (aux->proximo==NULL) break;
			aux = aux->proximo;
		}
		if((aux->proximo==NULL)&&(aux->cidade->codigo < noCodigo->cidade->codigo)){
			//printf("\nadd no fim CODIGO\n");
			aux->proximo = noCodigo;
			noCodigo->anterior = aux;
			porCodigo->fim = noCodigo;			
		}else{
			//meio da lista ou inicio 
			if(aux == porCodigo->inicio){
				//inicio da lista
				noCodigo->proximo = aux;
				aux->anterior = noCodigo;
				porCodigo->inicio = noCodigo;
			}else{
				//meio
				noCodigo->proximo = aux;
				noCodigo->anterior = aux->anterior;
				aux->anterior->proximo = noCodigo;
				aux->anterior = noCodigo;
			}//else
		}//else
	}//else (aux==NULL)
	
	//========== add por nome =======
	aux = porNome->inicio;
	if (aux==NULL){
		porNome->inicio = noNome;
		porNome->fim = noNome;
		
	}
	else{
		//(aux!=NULL)&&
		while((strcmp(aux->cidade->nome, noNome->cidade->nome)!=1)){
			//printf("\n1");
			//encontrar o lugar
			if (aux->proximo==NULL) break;
			aux = aux->proximo;
		}
		 
		if((aux->proximo==NULL)&&((strcmp(aux->cidade->nome, noNome->cidade->nome)!=1))){
			//printf("\nfim da lista NOME\n");
			aux->proximo = noNome;
			noNome->anterior = aux;
			porNome->fim = noNome;			
		}
		else{
			//meio da lista ou inicio 
			if(aux == porNome->inicio){
				//inicio da lista
				noNome->proximo = aux;
				aux->anterior = noNome;
				porNome->inicio = noNome;
			}else{
				//meio
				noNome->proximo = aux;
				noNome->anterior = aux->anterior;
				aux->anterior->proximo = noNome;
				aux->anterior = noNome;
			}//else
		}//else
	}//else (aux==NULL)
	
}

void remover(NO* lixo, LISTA* lista){
	
	if (lista->inicio == lista->fim){
		//lista com somente 1 elemento
		lista->fim = NULL;
		lista->inicio = NULL;
		return;
	}
		
	if(lixo->cidade->codigo == lista->inicio->cidade->codigo){
		//inicio da lista
		lista->inicio = lixo->proximo;
		lixo->proximo->anterior = NULL;
		
		free(lixo);
		return;
	}/**/else if(lixo->cidade->codigo == lista->fim->cidade->codigo){
		//final da lista
		lista->fim = lixo->anterior;
		lixo->anterior->proximo = NULL;
		
		free(lixo);
		//return 1;
	}else{
		//meio da lista
		lixo->proximo->anterior = lixo->anterior;
		lixo->anterior->proximo = lixo->proximo;
		
		free(lixo);
		//return 1;
	}
	printf("\n\tREMOVIDO COM SUCESSO\n");
}

int excluir(LISTA *porNome, LISTA *porCodigo, int codigo, char nome[50]){
	// ponteiros para auxiliar a exclusao ...
	NO *lixoCod = (NO*) malloc(sizeof(NO));
	NO *lixoNome = (NO*) malloc(sizeof(NO));
	lixoCod = NULL;
	lixoNome = NULL;
		
	// lista com somente 1 elemento
	if((porNome->inicio==porNome->fim)&&(porCodigo->inicio==porCodigo->fim)){
		lixoNome=porNome->inicio;
		lixoCod=porCodigo->inicio;
		remover(lixoCod, porCodigo);
		remover(lixoNome, porNome);
		return 1;
	}
	
	if (codigo>0){
		// ---- por codigo ----		 
		//	encontrar o NO responsavel LCodigo
		lixoCod = porCodigo->inicio;
		while((lixoCod!=NULL)&&(lixoCod->cidade->codigo!=codigo)){ 
			lixoCod=lixoCod->proximo;
			
		}
		//nao encontrado
		if(lixoCod==NULL) {
			printf("\nA CIDADE %s NAO FOI ENCONTRADA!\n\n", nome);
			return 0; 
		}
		
		
		//	encontrar o NO responsavel LNome
		lixoNome = porNome->inicio;
		while((lixoNome!=NULL)&&(strcmp(lixoNome->cidade->nome, lixoNome->cidade->nome)!=0)){ //entrontar o NO responsavel LNome
			lixoNome=lixoNome->proximo;
			
		}
		//nao encontrado
		if(lixoNome==NULL) {
			printf("\nA CIDADE %s NAO FOI ENCONTRADA!\n\n", nome);
			return 0; 
		}
		
		//remover os NO's
		remover(lixoCod, porCodigo);
		remover(lixoNome, porNome);
		
	}
	else{
		// ---- por nome ---- 
		//	encontrar o NO responsavel LNome
		lixoNome = porNome->inicio;
		while((lixoNome!=NULL)&&(strcmp(lixoNome->cidade->nome, nome)!=0)){ //entrontar o NO responsavel LNome
			lixoNome=lixoNome->proximo;
		}
		//nao encontrado
		if(lixoNome==NULL) {
			printf("\nA CIDADE %s NAO FOI ENCONTRADA!\n\n", nome);
			return 0; 
		}
		
		//	encontrar o NO responsavel LCodigo
		lixoCod = porCodigo->inicio;
		while((lixoCod!=NULL)&&(lixoCod->cidade->codigo!= lixoNome->cidade->codigo)){ //entrontar o NO responsavel LCodigo
			lixoCod=lixoCod->proximo;
		}
		//nao encontrado
		if(lixoCod==NULL) {
			printf("\nA CIDADE %s NAO FOI ENCONTRADA!\n\n", nome);
			return 0; 
		}
		
		//remover os NO's
		remover(lixoCod, porCodigo);
		remover(lixoNome, porNome);
		
	}
	return 1;
	exibir(porNome, porCodigo);	
}

CIDADE *consultarPorNome (LISTA *lista, char nome[50]){
	// ponteiros para auxiliar a exclusao ...
	NO *noAtual = (NO*) malloc(sizeof(NO));	
	
	noAtual = NULL;
	noAtual = lista->inicio;
	
	while((noAtual!=NULL)&&(strcmp(noAtual->cidade->nome, nome)!=0)){ //entrontar o NO responsavel LNome
		noAtual=noAtual->proximo;
	}
	
	//nao encontrado
	if(noAtual == NULL) {
		printf("\nA CIDADE %s NAO FOI ENCONTRADA!\n\n", nome);
		return NULL;
	}else{
		return noAtual->cidade;
	}
}

CIDADE *consultarPorCodigo (LISTA *lista, int codigo){
	// ponteiros para auxiliar a exclusao ...
	NO *noAtual = (NO*) malloc(sizeof(NO));	
	
	noAtual = NULL;
	noAtual = lista->inicio;
	
	while((noAtual!=NULL)&&(noAtual->cidade->codigo != codigo)){ //entrontar o NO responsavel LNome
		noAtual=noAtual->proximo;
	}
	
	//nao encontrado
	if(noAtual == NULL) {
		printf("\nA CIDADE DE CODIGO %d NAO FOI ENCONTRADA! \n\n", codigo);
		return NULL;
	}else{
		return noAtual->cidade;
	}
}












