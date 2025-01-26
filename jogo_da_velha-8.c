#include <stdio.h>
#include <stdlib.h> // gerar valores aleatórios rand() e srand()
#include <time.h> // obter resultados diferentes time()

// Função para criar a matriz dinamicamente
int** cria_matriz() {
    int** m = (int**)malloc(3 * sizeof(int*)); // Aloca as linhas
    if (m == NULL) {
        printf("Erro: falha na alocação de memória para o tabuleiro.\n");
        exit(1);
    }
    for (int i = 0; i < 3; i++) {
        m[i] = (int*)malloc(3 * sizeof(int)); // Aloca as colunas
        if (m[i] == NULL) {
            printf("Erro: falha na alocação de memória para as colunas.\n");
            exit(1);
        }
        // Inicializa o tabuleiro com zeros
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

// Função para exibir o tabuleiro
void exibir_matriz(int** m) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (m[i][j] == 0) {
                printf("%d ", i * 3 + j + 1); // Exibe os indices de 1 a 9
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

// Função que verifica se alguem venceu
int verifica_vencedor(int** m) {
    // Verificador de linhas e colunas
    for (int i = 0; i < 3; i++) {
        if (m[i][0] == m[i][1] && m[i][1] == m[i][2] && m[i][0] != 0) {
            return m[i][0]; // Vencedor da linha (1 para X, 2 para O)
        }
        if (m[0][i] == m[1][i] && m[1][i] == m[2][i] && m[0][i] != 0) {
            return m[0][i]; // Vencedor da coluna (1 para X, 2 para O)
        }
    }
    // Verificador das diagonais
    if (m[0][0] == m[1][1] && m[1][1] == m[2][2] && m[0][0] != 0) {
        return m[0][0]; // principal
    }
    if (m[0][2] == m[1][1] && m[1][1] == m[2][0] && m[0][2] != 0) {
        return m[0][2]; // secundária
    }
    return 0; // Sem vencedor
}

// Função que verifica se a jogada é válida
int jogada_valida(int** m, int jogada) {
    if (jogada < 1 || jogada > 9) {
        return 0; // Jogada fora do intervalo
    }
    int i = (jogada - 1) / 3; // linha <<<
    int j = (jogada - 1) % 3; // coluna <<<
    return (m[i][j] == 0); // Retorna verdadeiro se a célula está vazia
}

// Função que faz a escolha do PC
int escolha_do_pc(int** m) {
    int gerador;
    do {
        gerador = rand() % 9 + 1; // <<<
    } while (!jogada_valida(m, gerador));
    int i = (gerador - 1) / 3; // linha  // <<
    int j = (gerador - 1) % 3; // coluna // <<
    m[i][j] = 2; // Marca a jogada do PC
    return gerador; // posição escolhida pelo PC
}

// Função principal
int main() {
    srand(time(NULL));
    int** jogo_da_velha = cria_matriz(); // Inicializa a matriz com zeros
    //int *jogo_da_velha = matriz;
    int vencedor = 0;

    for (int rodada = 1; rodada <= 9; rodada++) {
        exibir_matriz(jogo_da_velha);

        if (rodada % 2 != 0) { // jogador X
            printf("Escolha sua posição, jogador X: ");
            int jogadaX;
            scanf("%d", &jogadaX);

            while (!jogada_valida(jogo_da_velha, jogadaX)) {
                printf("Jogada inválida! Escolha novamente: ");
                scanf("%d", &jogadaX);
            }

            int i = (jogadaX - 1) / 3; // <<
            int j = (jogadaX - 1) % 3; // <<
            jogo_da_velha[i][j] = 1; // Marca a jogada do jogador X
        } else { // jogador O (PC)
            int jogadaO = escolha_do_pc(jogo_da_velha);
            printf("Escolha da máquina, jogador O: %d\n", jogadaO);
        }
        // Verifica o vencedor apenas a partir da quinta rodada
        if (rodada >= 5) {
            vencedor = verifica_vencedor(jogo_da_velha);
            if (vencedor != 0) break;
        }
        // Checar empates
        if (rodada == 9 && vencedor == 0) {
            exibir_matriz(jogo_da_velha);
            printf("Empate!\n");
        }
    }
    if (vencedor != 0) {
        exibir_matriz(jogo_da_velha);
        printf("O vencedor é: %c\n", vencedor == 1 ? 'X' : 'O'); // <<<<
    }

    libera_matriz(jogo_da_velha);
    return 0;
}
