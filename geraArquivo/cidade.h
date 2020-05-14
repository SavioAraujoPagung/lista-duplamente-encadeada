#define MAX_NOME 15

typedef struct cidade{
	char *nome;
	int codigo;
}TCidade;

TCidade * criaCidade(int codigo, char *nome);
