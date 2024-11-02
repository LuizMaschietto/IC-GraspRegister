#include <stdio.h>
#include <stdbool.h>

#define TAMANHO 30
#define NUM_REGISTRADORES 4  // Ajuste conforme a quantidade de registradores disponíveis
int matriz[TAMANHO][TAMANHO];  // Matriz de interferência

void ler_matriz() {
    // Exemplo de leitura direta de um arquivo ou valores fixos para teste
    FILE *file = fopen("caso_teste.txt", "r");
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            fscanf(file, "%d", &matriz[i][j]);
        }
    }
    fclose(file);
}

void alocar_registradores(int registradores[]) {
    for (int i = 0; i < TAMANHO; i++) {
        bool usado[NUM_REGISTRADORES] = {false};  // Registra registradores usados pelos vizinhos

        // Marca os registradores dos vizinhos como usados
        for (int j = 0; j < TAMANHO; j++) {
            if (matriz[i][j] == 1 && registradores[j] != -1) {
                usado[registradores[j]] = true;
            }
        }

        // Encontra o primeiro registrador disponível
        for (int k = 0; k < NUM_REGISTRADORES; k++) {
            if (!usado[k]) {
                registradores[i] = k;  // Atribui registrador à variável
                break;
            }
        }
    }
}

int main() {
    int registradores[TAMANHO];
    for (int i = 0; i < TAMANHO; i++) {
        registradores[i] = -1;  // Inicialmente, nenhum registrador é atribuído
    }

    ler_matriz();  // Lê a matriz de interferência
    alocar_registradores(registradores);  // Aloca registradores

    // Exibe o resultado da alocação
    for (int i = 0; i < TAMANHO; i++) {
        printf("Variável %d -> Registrador %d\n", i, registradores[i]);
    }

    return 0;
}
