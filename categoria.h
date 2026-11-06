#ifndef CATEGORIA_H
#define CATEGORIA_H

#define MAX_CATEGORIAS 20

typedef struct {
    int codigo;
    char nome[30];
} Categoria;

int buscarCategoriaPorCodigo(Categoria categorias[], int total, int codigo);
void exibirCategoria(Categoria c);
int cadastrarCategoria(Categoria categorias[], int total);
void listarCategorias(Categoria categorias[], int total);

/* Persistencia: arquivo de texto "categorias.txt" */
int carregarCategorias(Categoria categorias[]);
void salvarCategorias(Categoria categorias[], int total);

#endif
