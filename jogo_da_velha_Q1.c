#include <stdio.h>
#include <stdlib.h> // Para malloc, free, rand e srand
#include <time.h>   // Para time

// Função para criar a matriz dinamicamente
int** cria_matriz() {
    int** m = (int**)malloc(3 * sizeof(int*)); // Aloca as linhas
    if (m == NULL) {
        printf("Erro: falha na alocação de memória para a matriz.\n");
        exit(1);
    }
    for (int i = 0; i < 3; i++) {
        m[i] = (int*)malloc(3 * sizeof(int)); // Aloca as colunas
        if (m[i] == NULL) {
            printf("Erro: falha na alocação de memória para as colunas.\n");
            exit(1);
        }
        // Inicializa a matriz com zeros
        for (int j = 0; j < 3; j++) {
            m[i][j] = 0;
        }
    }
    return m;
}

// Função para liberar a memória da matriz
void libera_matriz(int** m) {
    for (int i = 0; i < 3; i++) {
        free(m[i]); // Libera cada linha
    }
    free(m); // Libera o array de ponteiros
}

// Função para exibir a matriz
void exibir_matriz(int** m) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (m[i][j] == 0) {
                printf("%d ", i * 3 + j + 1); // Exibe os índices de 1 a 9
            } else if (m[i][j] == 1) {
                printf("X ");
            } else if (m[i][j] == 2) {
                printf("O ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Função que verifica se alguém venceu
int verifica_vencedor(int** m) {
    // Verifica linhas e colunas
    for (int i = 0; i < 3; i++) {
        if (m[i][0] == m[i][1] && m[i][1] == m[i][2] && m[i][0] != 0) {
            return m[i][0]; // Vencedor da linha (1 para X, 2 para O)
        }
        if (m[0][i] == m[1][i] && m[1][i] == m[2][i] && m[0][i] != 0) {
            return m[0][i]; // Vencedor da coluna (1 para X, 2 para O)
        }
    }
    // Verifica diagonais
    if (m[0][0] == m[1][1] && m[1][1] == m[2][2] && m[0][0] != 0) {
        return m[0][0]; // Diagonal principal
    }
    if (m[0][2] == m[1][1] && m[1][1] == m[2][0] && m[0][2] != 0) {
        return m[0][2]; // Diagonal secundária
    }
    return 0; // Sem vencedor
}

// Função que verifica se a jogada é válida
int jogada_valida(int** m, int jogada) {
    if (jogada < 1 || jogada > 9) {
        return 0; // Jogada fora do intervalo
    }
    int i = (jogada - 1) / 3; // Calcula a linha
    int j = (jogada - 1) % 3; // Calcula a coluna
    return (m[i][j] == 0); // Retorna verdadeiro se a célula está vazia
}

// Função que verifica se há uma jogada estratégica (ganhar ou bloquear)
int estrategia_pc(int** m, int jogada) {
    for (int i = 0; i < 3; i++) {
        // Verifica linhas
        if (m[i][0] == m[i][1] && m[i][2] == 0 && m[i][0] == jogada) 
            return i * 3 + 3;
        if (m[i][1] == m[i][2] && m[i][0] == 0 && m[i][1] == jogada) 
            return i * 3 + 1;
        if (m[i][0] == m[i][2] && m[i][1] == 0 && m[i][0] == jogada) 
            return i * 3 + 2;
        
        // Verifica colunas
        if (m[0][i] == m[1][i] && m[2][i] == 0 && m[0][i] == jogada) 
            return i + 7;
        if (m[1][i] == m[2][i] && m[0][i] == 0 && m[1][i] == jogada) 
            return i + 1;
        if (m[0][i] == m[2][i] && m[1][i] == 0 && m[0][i] == jogada) 
            return i + 4;
        
        // Verifica diagonais
        if (m[0][0] == m[1][1] && m[2][2] == 0 && m[0][0] == jogada)
            return 9;
        if (m[0][0] == m[2][2] && m[1][1] == 0 && m[0][0] == jogada)
            return 5;
        if (m[2][0] == m[0][2] && m[1][1] == 0 && m[2][0] == jogada)
            return 5;
        if (m[1][1] == m[2][2] && m[0][0] == 0 && m[1][1] == jogada)
            return 1;
        if (m[2][0] == m[1][1] && m[0][2] == 0 && m[2][0] == jogada)
            return 3;
        if (m[0][2] == m[1][1] && m[2][0] == 0 && m[0][2] == jogada)
            return 7;
    }
    return 0; // Nenhuma jogada estratégica encontrada
}

// Função que implementa a escolha do PC (tenta ganhar ou bloquear)
int escolha_do_pc(int** m) {
    // Verifica se o PC pode ganhar
    int jogada = estrategia_pc(m, 2);
    if (jogada != 0) {
        int i = (jogada - 1) / 3;
        int j = (jogada - 1) % 3;
        m[i][j] = 2; // Marca a jogada do PC
        return jogada;
    }
    // Bloqueia o jogador X se ele estiver prestes a ganhar
    jogada = estrategia_pc(m, 1);
    if (jogada != 0) {
        int i = (jogada - 1) / 3;
        int j = (jogada - 1) % 3;
        m[i][j] = 2; // Marca a jogada do PC
        return jogada;
    }
    // Se não houver jogadas estratégicas, escolhe uma jogada aleatória
    do {
        jogada = rand() % 9 + 1; // Gera uma jogada aleatória entre 1 e 9
    } while (!jogada_valida(m, jogada)); // Repete até encontrar uma jogada válida
    int i = (jogada - 1) / 3;
    int j = (jogada - 1) % 3;
    m[i][j] = 2; // Marca a jogada do PC
    return jogada;
}

// Função principal
int main() {
    srand(time(NULL)); // Inicializa a semente para números aleatórios
    int** m = cria_matriz(); // Inicializa a matriz
    int rodada = 1;
    while (rodada <= 9) {
        exibir_matriz(m);
        if (rodada % 2 != 0) { // Vez do jogador (X)
            printf("Escolha sua posição, jogador X: ");
            int jogada;
            scanf("%d", &jogada);
            while (!jogada_valida(m, jogada)) {
                printf("Jogada inválida! Escolha novamente: ");
                scanf("%d", &jogada);
            }
            int i = (jogada - 1) / 3;
            int j = (jogada - 1) % 3;
            m[i][j] = 1; // Marca a jogada do jogador X
        } else { // Vez do PC (O)
            int jogada_pc = escolha_do_pc(m);
            printf("Escolha da máquina, jogador O: %d\n", jogada_pc);
        }
        // Verifica se há um vencedor ou empate a partir da 5ª rodada
        if (rodada >= 5) {
            int vencedor = verifica_vencedor(m);
            if (vencedor != 0) {
                exibir_matriz(m);
                printf("O vencedor é: %c\n", vencedor == 1 ? 'X' : 'O');
                break; // Termina o jogo se houver um vencedor
            }
            if (rodada == 9) {
                exibir_matriz(m);
                printf("Empate!\n");
                break; // Termina o jogo em caso de empate
            }
        }
        rodada++;
    }
    libera_matriz(m); // Libera a memória da matriz
    return 0;
}
