#include <stdio.h>
#include <stdlib.h>
/*
	LISTA 
	= inserir (2lista, nome, populacao, area)
	= excluir (2lista, nome ou populacao)
	= exibir (2lista)
	= lista vazia
	= consultar
*/
typedef struct Cidade{
	char nome[50];
	int codigo;
	double area;
}CIDADE;

typedef struct No{
	struct No *proximo;
	struct No *anterior;
	CIDADE *cidade;
}NO;

typedef struct lista{
	NO *inicio;
	NO *fim;
}LISTA;

int listaVazia(LISTA *lista);

void exibir(LISTA *porNome, LISTA *porCodigo);

void inserir(LISTA *porNome, LISTA *porCodigo, char nome[50], int codigo, double area);

int excluir(LISTA *porNome, LISTA *porCodigo, int codigo, char nome[50]);

CIDADE *consultarPorNome (LISTA *lista, char nome[50]);

CIDADE *consultarPorCodigo (LISTA *lista, int codigo);













