#ifndef UTIL_H
#define UTIL_H

void limparEntrada(void);
int lerInteiro(const char *mensagem, const char *erro, int minimo);
float lerPreco(void);
void lerNome(const char *mensagem, char nome[], int tamanho);
char lerPrateleira(void);

#endif
