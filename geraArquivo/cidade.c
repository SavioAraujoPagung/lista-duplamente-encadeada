#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidade.h"



TCidade * criaCidade(int codigo, char *nome){
	TCidade *n = (TCidade *) malloc (sizeof(TCidade));
	n->codigo = codigo;
	n->nome = (char *) malloc (MAX_NOME * sizeof(char));
	strcpy(n->nome,nome);
	return n;
}
