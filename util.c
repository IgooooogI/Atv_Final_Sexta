#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "util.h"

void limparEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int lerInteiro(const char *mensagem, const char *erro, int minimo) {
    int valor, resultado;
    printf("%s", mensagem);
    while ((resultado = scanf("%d", &valor)) != 1 || valor < minimo) {
        printf("%s", erro);
        limparEntrada();
    }
    limparEntrada();
    return valor;
}

float lerPreco(void) {
    float valor;
    int resultado;
    printf("Digite o preco unitario: ");
    while ((resultado = scanf("%f", &valor)) != 1 || valor <= 0) {
        printf("Preco invalido! Digite um numero maior que zero: ");
        limparEntrada();
    }
    limparEntrada();
    return valor;
}

/* Devolve 1 se a string so tem espacos (ou esta vazia). */
static int emBranco(const char s[]) {
    int i;
    for (i = 0; s[i] != '\0'; i++)
        if (!isspace((unsigned char)s[i])) return 0;
    return 1;
}

/* Le uma linha de ate (tamanho - 1) caracteres. Nao aceita nome em branco. */
void lerNome(const char *mensagem, char nome[], int tamanho) {
    printf("%s", mensagem);
    while (1) {
        if (fgets(nome, tamanho, stdin) == NULL) nome[0] = '\0';
        if (strchr(nome, '\n') == NULL && !feof(stdin))
            limparEntrada();               /* descarta o que passou do limite */
        nome[strcspn(nome, "\n")] = '\0';
        if (!emBranco(nome)) break;
        printf("Nome nao pode ser vazio! Digite novamente: ");
    }
}

/* Aceita somente A, B, C ou D (maiuscula ou minuscula), um unico caractere. */
char lerPrateleira(void) {
    char linha[50], c, resto;
    printf("Digite a prateleira (A, B, C ou D): ");
    while (1) {
        if (fgets(linha, sizeof(linha), stdin) != NULL &&
            sscanf(linha, " %c %c", &c, &resto) == 1) {
            c = (char)toupper((unsigned char)c);
            if (c >= 'A' && c <= 'D') return c;
        }
        printf("Prateleira invalida! Digite A, B, C ou D: ");
    }
}
