#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <time.h>

#define TAMANHO 450//tamanho da matriz
#define NUM_REGISTRADORES 25// Número de registradores disponíveis
#define ITERACOES_GRASP 10000// Número de iterações GRASP

int matriz[TAMANHO][TAMANHO];  // Matriz de interferência



void ler_matriz() {
    FILE *file = fopen("/home/forest/Documents/IC-GraspRegister/IC-Grasp/TestCases/le450_25d.txt", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            fscanf(file, "%d", &matriz[i][j]);
        }
    }
    fclose(file);
}


void alocar_registradores_gulosa(int registradores[]) {
    int count=0;
    for (int i = 0; i < TAMANHO; i++) {
        bool usado[NUM_REGISTRADORES] = {false};

        for (int j = 0; j < TAMANHO; j++) {
            if (matriz[i][j] == 1 && registradores[j] != -1) {
                usado[registradores[j]] = true;
            }
        }

        // Tenta alocar um registrador que não cause conflito
        int registrador_alocado = -1;
        for (int k = 0; k < NUM_REGISTRADORES; k++) {
            if (!usado[k]) {
                registradores[i]=k;
                registrador_alocado=k;
                break;
            }
        }

        // Controle de erro: caso nenhuma opção válida tenha sido encontrada
        
        if (registrador_alocado == -1) {
            count++;
           // printf("Aviso: Variável %d não conseguiu alocar um registrador GULOSO.\n", i);
        }
        
    }
    printf("Numero de Variaveis nao Alocadas GULOSO: %d \n",count);
    printf("\n");

}

void alocar_registradores_grasp(int registradores[]) {


    int melhor_custo = TAMANHO;  // Valor alto para representar o pior custo
    

    for (int iteracao = 0; iteracao < ITERACOES_GRASP; iteracao++) {
        int solucao[TAMANHO];
        for (int i = 0; i < TAMANHO; i++) {
            solucao[i] = -1; // Nenhuma variável tem registrador atribuído inicialmente
        }

        for (int i = 0; i < TAMANHO; i++) {
            bool usado[NUM_REGISTRADORES] = {false};
            for (int j = 0; j < TAMANHO; j++) {
                if (matriz[i][j] == 1 && solucao[j] != -1) {
                    usado[solucao[j]] = true; //garantir q a solução seja marcada como usada
                }
            }
            //ado me salva

            int opcoes[NUM_REGISTRADORES];
            int num_opcoes = 0;
            for (int k = 0; k < NUM_REGISTRADORES; k++) {
                if (!usado[k]) {
                    opcoes[num_opcoes] = k;
                    num_opcoes++; //Guardar indice de um registrador vazio e adicionar na quantidade de opçoes livres
                }
            }

            if (num_opcoes > 0) {
                int escolha = opcoes[rand() % num_opcoes];
                solucao[i] = escolha;// guardar o registrador escolhido dentro do processo aleatorio
            }
        }

        // Refinamento local - minimizando conflitos
        int custo = 0;
        for (int i = 0; i < TAMANHO; i++) {
            for (int j = i + 1; j < TAMANHO; j++) {
                if (matriz[i][j] == 1 && solucao[i] == solucao[j]) {
                    custo++;
                }
            }
        }

        // Verifica se é a melhor solução encontrada até agora
        if (custo < melhor_custo) {
            melhor_custo = custo;
            for (int i = 0; i < TAMANHO; i++) {
                registradores[i]=solucao[i];
            }
        }/*else{
            for (int i = 0; i < TAMANHO; i++) {
                registradores[i] = solucao[i];
            }
           
        }*/


    }
    int count=0;
    for (int i = 0; i < TAMANHO; i++) { // atribuir a melhor solução, e ver se nao conseguiu alocar um registrador 
        
        if (registradores[i] == -1) {
            count++;
           // printf("Aviso: Variável %d não conseguiu alocar um registrador GRASP.\n", i);
        }
    }
    printf("Numero de Variaveis nao Alocadas GRASP: %d \n",count);
    printf("\n");
  
}

/*void alocar_registradores_grasp(int registradores[]) {
    int melhor_solucao[TAMANHO];
    int melhor_custo = TAMANHO;  // Valor alto para representar o pior custo

    for (int iteracao = 0; iteracao < ITERACOES_GRASP; iteracao++) {
        int solucao[TAMANHO];
        for (int i = 0; i < TAMANHO; i++) {
            solucao[i] = -1;  // Nenhuma variável tem registrador atribuído inicialmente
        }

        for (int i = 0; i < TAMANHO; i++) {
            bool usado[NUM_REGISTRADORES] = {false};
            for (int j = 0; j < TAMANHO; j++) {
                if (matriz[i][j] == 1 && solucao[j] != -1) {
                    usado[solucao[j]] = true;
                }
            }

            int opcoes[NUM_REGISTRADORES];
            int num_opcoes = 0;
            for (int k = 0; k < NUM_REGISTRADORES; k++) {
                if (!usado[k]) {
                    opcoes[num_opcoes++] = k;
                }
            }

            if (num_opcoes > 0) {
                int escolha = opcoes[rand() % num_opcoes];
                solucao[i] = escolha;
            } else {
                // Caso não haja opção disponível, força uma escolha aleatória para continuidade
                solucao[i] = rand() % NUM_REGISTRADORES;
            }
        }

        // Refinamento local - minimizando conflitos
        int custo = 0;
        for (int i = 0; i < TAMANHO; i++) {
            for (int j = i + 1; j < TAMANHO; j++) {
                if (matriz[i][j] == 1 && solucao[i] == solucao[j]) {
                    custo++;
                }
            }
        }

        // Verifica se é a melhor solução encontrada até agora
        if (custo < melhor_custo) {
            melhor_custo = custo;
            for (int i = 0; i < TAMANHO; i++) {
                melhor_solucao[i] = solucao[i];
            }
        }
    }

    for (int i = 0; i < TAMANHO; i++) {
        registradores[i] = melhor_solucao[i];
    }
}*/

int main() {
    srand(time(NULL));
    clock_t start, end;
    double cpu_time_used;

    int registradores_gulosa[TAMANHO];
    int registradores_grasp[TAMANHO];

    // Inicializa com valores neutros
    for (int i = 0; i < TAMANHO; i++) {
        registradores_gulosa[i] = -1;
        registradores_grasp[i] = -1;
    }

    ler_matriz();  // Lê a matriz de interferência

    // Executa a solução gulosa
    alocar_registradores_gulosa(registradores_gulosa);

    // Executa a solução GRASP
    alocar_registradores_grasp(registradores_grasp);

    // Exibe e compara as soluções
    start=clock();
    printf("Solução Gulosa:\n");
    for (int i = 0; i < TAMANHO; i++) {
        printf("Variável %d -> Registrador %d\n", i, registradores_gulosa[i]);
    }
    end=clock();
    cpu_time_used= ((double)end-start)/CLOCKS_PER_SEC;
    printf("Tempo Levado GULOSO: %f\n",cpu_time_used );

    start=clock();
    printf("\nSolução GRASP:\n");
    for (int i = 0; i < TAMANHO; i++) {
        printf("Variável %d -> Registrador %d\n", i, registradores_grasp[i]);
    }
    end=clock();
    cpu_time_used= ((double)end-start)/CLOCKS_PER_SEC;
    printf("Tempo Levado GRASP: %f \n",cpu_time_used );

    return 0;
}
