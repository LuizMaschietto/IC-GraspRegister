#include<stdio.h>
#include<stdlib.h>
#include "Grafo.h"
#include <string.h>

#define NUM_REGISTRADORES 4 // Número de registradores disponíveis
#define NUM_VARIAVEIS 100     // Máximo de variáveis

// Estrutura para registrar alocação
typedef struct {
    char variavel;
    int registrador; // Índice do registrador alocado
} Alocacao;

int encontrar_registrador_livre(Alocacao alocacoes[], int registradores[], int n) {
    for (int i = 0; i < n; i++) {
        if (registradores[i] == 0) { // Registrador livre
            return i;
        }
    }
    return -1; // Nenhum registrador livre
}

int encontrar_alocacao(Alocacao alocacoes[], int n, char variavel) {
    for (int i = 0; i < n; i++) {
        if (alocacoes[i].variavel == variavel) {
            return alocacoes[i].registrador;
        }
    }
    return -1; // Não alocado
}


void alocar_registrador(Alocacao alocacoes[], int registradores[], int *num_alocacoes, char variavel) {
    int reg_livre = encontrar_registrador_livre(alocacoes, registradores, NUM_REGISTRADORES);
    
    if (reg_livre == -1) {
        //Tirar o primeiro registrador ( Guloso )
        reg_livre = alocacoes[0].registrador;
        printf("Desalocando registrador %d da variável %c\n", reg_livre, alocacoes[0].variavel);
        for (int i = 1; i < *num_alocacoes; i++) {
            alocacoes[i - 1] = alocacoes[i];
        }
        (*num_alocacoes)--;
    }
    
    // Aloca o registrador livre
    alocacoes[*num_alocacoes].variavel = variavel;
    alocacoes[*num_alocacoes].registrador = reg_livre;
    registradores[reg_livre] = 1;
    (*num_alocacoes)++;
    printf("Alocando registrador %d para variável %c\n", reg_livre, variavel);
}

void desalocar_tudo(Alocacao alocacoes[], int registradores[], int *num_alocacoes) {
    for (int i = 0; i < *num_alocacoes; i++) {
        registradores[alocacoes[i].registrador] = 0;
    }
    *num_alocacoes = 0;
}

int main() {
    Alocacao alocacoes[NUM_VARIAVEIS];
    int registradores[NUM_REGISTRADORES] = {0}; // 0 = livre, 1 = ocupado
    int num_alocacoes = 0;

    // Sequência de variáveis para alocar
    char variaveis[] = {'A', 'B', 'C', 'A', 'D', 'E', 'F', 'D', 'G'};
    int num_variaveis = sizeof(variaveis) / sizeof(variaveis[0]);

    for (int i = 0; i < num_variaveis; i++) {
        char variavel = variaveis[i];
        
        if (encontrar_alocacao(alocacoes, num_alocacoes, variavel) == -1) {
            alocar_registrador(alocacoes, registradores, &num_alocacoes, variavel);
        } else {
            printf("Variável %c já está alocada em um registrador.\n", variavel);
        }
    }

    desalocar_tudo(alocacoes, registradores, &num_alocacoes);
    return 0;
}
