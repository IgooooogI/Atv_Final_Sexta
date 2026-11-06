#include <stdio.h>
#include "categoria.h"
#include "produto.h"
#include "util.h"

static void mostrarMenu(void) {
    printf("\n============================\n");
    printf("     SISTEMA DE ESTOQUE\n");
    printf("============================\n");
    printf("1 - Cadastrar Produto\n");
    printf("2 - Listar Produtos\n");
    printf("3 - Pesquisar Produto\n");
    printf("4 - Alterar Estoque de um Produto\n");
    printf("5 - Remover Produto\n");
    printf("6 - Categorias\n");
    printf("7 - Sair\n");
    printf("============================\n");
}

static void menuPesquisa(Produto produtos[], int total,
                         Categoria categorias[], int totalCategorias) {
    int tipo;
    printf("\n===== PESQUISAR PRODUTO =====\n");
    printf("1 - Por codigo\n");
    printf("2 - Por nome\n");
    tipo = lerInteiro("Escolha como pesquisar: ",
                      "Opcao invalida! Digite 1 ou 2: ", 1);
    while (tipo != 1 && tipo != 2) {
        tipo = lerInteiro("Escolha como pesquisar: ",
                          "Opcao invalida! Digite 1 ou 2: ", 1);
    }
    if (tipo == 1) pesquisarPorCodigo(produtos, total, categorias, totalCategorias);
    else pesquisarPorNome(produtos, total, categorias, totalCategorias);
}

/* Submenu de categorias; devolve o novo total de categorias. */
static int menuCategorias(Categoria categorias[], int total) {
    int opcao;
    do {
        printf("\n===== CATEGORIAS =====\n");
        printf("1 - Cadastrar Categoria\n");
        printf("2 - Listar Categorias\n");
        printf("3 - Voltar\n");
        opcao = lerInteiro("Digite uma opcao: ",
                           "Opcao invalida! Digite um numero: ", 0);
        switch (opcao) {
            case 1:
                total = cadastrarCategoria(categorias, total);
                salvarCategorias(categorias, total);
                break;
            case 2: listarCategorias(categorias, total); break;
            case 3: break;
            default: printf("\nOpcao invalida!\n");
        }
    } while (opcao != 3);
    return total;
}

int main(void) {
    Produto produtos[MAX_PRODUTOS];
    Categoria categorias[MAX_CATEGORIAS];
    int total, totalCategorias, opcao;

    /* carrega os dados dos arquivos (listas vazias se nao existirem) */
    totalCategorias = carregarCategorias(categorias);
    total = carregarProdutos(produtos);

    do {
        mostrarMenu();
        opcao = lerInteiro("Digite uma opcao: ",
                           "Opcao invalida! Digite um numero: ", 0);
        switch (opcao) {
            case 1:
                total = cadastrarProduto(produtos, total,
                                         categorias, totalCategorias);
                salvarProdutos(produtos, total);   /* salva a cada cadastro */
                break;
            case 2: listarProdutos(produtos, total, categorias, totalCategorias); break;
            case 3: menuPesquisa(produtos, total, categorias, totalCategorias); break;
            case 4:
                alterarEstoque(produtos, total);
                salvarProdutos(produtos, total);
                break;
            case 5:
                removerProduto(produtos, total);
                salvarProdutos(produtos, total);
                break;
            case 6: totalCategorias = menuCategorias(categorias, totalCategorias); break;
            case 7:
                salvarCategorias(categorias, totalCategorias);
                salvarProdutos(produtos, total);
                printf("\nDados salvos. Programa encerrado!\n");
                break;
            default: printf("\nOpcao invalida!\n");
        }
    } while (opcao != 7);
    return 0;
}
