#include <stdio.h>
#include <string.h>
#include "categoria.h"
#include "util.h"

#define ARQUIVO_CATEGORIAS "categorias.txt"

int buscarCategoriaPorCodigo(Categoria categorias[], int total, int codigo) {
    int i;
    for (i = 0; i < total; i++)
        if (categorias[i].codigo == codigo) return i;
    return -1;
}

void exibirCategoria(Categoria c) {
    printf("Codigo: %d\n", c.codigo);
    printf("Nome: %s\n", c.nome);
}

int cadastrarCategoria(Categoria categorias[], int total) {
    Categoria nova;
    if (total >= MAX_CATEGORIAS) {
        printf("\nLista cheia! Nao e possivel cadastrar mais categorias.\n");
        return total;
    }
    printf("\n===== CADASTRO DE CATEGORIA =====\n");
    while (1) {
        nova.codigo = lerInteiro("Digite o codigo da categoria: ",
            "Codigo invalido! Digite um numero inteiro maior que zero: ", 1);
        if (buscarCategoriaPorCodigo(categorias, total, nova.codigo) != -1)
            printf("Ja existe uma categoria com esse codigo! Tente outro.\n");
        else break;
    }
    lerNome("Digite o nome da categoria: ", nova.nome, sizeof(nova.nome));
    categorias[total] = nova;
    printf("\nCategoria cadastrada com sucesso!\n\n");
    exibirCategoria(categorias[total]);
    return total + 1;
}

void listarCategorias(Categoria categorias[], int total) {
    int i;
    printf("\n===== CATEGORIAS CADASTRADAS =====\n");
    if (total == 0) {
        printf("Nenhuma categoria cadastrada.\n");
        return;
    }
    for (i = 0; i < total; i++) {
        printf("\n--- Categoria %d ---\n", i + 1);
        exibirCategoria(categorias[i]);
    }
}

/* Formato do arquivo: uma categoria por linha -> codigo;nome
   Devolve quantas categorias foram lidas (0 se o arquivo nao existe). */
int carregarCategorias(Categoria categorias[]) {
    FILE *f = fopen(ARQUIVO_CATEGORIAS, "r");
    int total = 0;
    Categoria c;
    if (f == NULL) return 0;               /* primeira execucao: lista vazia */
    while (total < MAX_CATEGORIAS &&
           fscanf(f, "%d;%29[^\n]\n", &c.codigo, c.nome) == 2) {
        categorias[total++] = c;
    }
    fclose(f);
    return total;
}

void salvarCategorias(Categoria categorias[], int total) {
    int i;
    FILE *f = fopen(ARQUIVO_CATEGORIAS, "w");
    if (f == NULL) {
        printf("\nErro: nao foi possivel salvar %s!\n", ARQUIVO_CATEGORIAS);
        return;
    }
    for (i = 0; i < total; i++)
        fprintf(f, "%d;%s\n", categorias[i].codigo, categorias[i].nome);
    fclose(f);
}
