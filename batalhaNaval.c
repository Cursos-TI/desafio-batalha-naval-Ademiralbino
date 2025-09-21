#include <stdio.h>
#include <stdlib.h> // Incluído para a função abs()

// Definições de constantes para o tabuleiro e navios.
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// Definições de constantes para o tamanho das habilidades.
// O tamanho deve ser ímpar para ter um centro.
#define TAMANHO_HABILIDADE 5 
#define CENTRO_HABILIDADE (TAMANHO_HABILIDADE / 2)

// Representação numérica para os elementos do tabuleiro.
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

// --- Protótipos das funções de habilidade ---
// A função abs() está na biblioteca stdlib.h.
// O ponto de origem (linha, coluna) será o ponto de referência para cada forma.
void aplicarHabilidadeCone(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna);
void aplicarHabilidadeCruz(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna);
void aplicarHabilidadeOctaedro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna);

// --- Função principal do programa ---
int main() {
    // 1. Declaração e inicialização do tabuleiro com água (0s).
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Looping para preencher o tabuleiro com 0s.
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // --- 2. Posicionamento dos Navios ---
    // Posiciona os navios primeiro para que as habilidades possam se sobrepor a eles.
    
    // Navio 1: Horizontal (linha 2, coluna 4)
    int navio1_linha = 2;
    int navio1_coluna = 4;
    // Validação de limite
    if (navio1_coluna + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[navio1_linha][navio1_coluna + i] == AGUA) {
                tabuleiro[navio1_linha][navio1_coluna + i] = NAVIO;
            }
        }
    }

    // Navio 2: Vertical (linha 6, coluna 1)
    int navio2_linha = 6;
    int navio2_coluna = 1;
    // Validação de limite
    if (navio2_linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[navio2_linha + i][navio2_coluna] == AGUA) {
                tabuleiro[navio2_linha + i][navio2_coluna] = NAVIO;
            }
        }
    }

    // Navio 3: Diagonal crescente (linha 1, coluna 1)
    int navio3_linha = 1;
    int navio3_coluna = 1;
    // Validação de limite
    if (navio3_linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO && navio3_coluna + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[navio3_linha + i][navio3_coluna + i] == AGUA) {
                tabuleiro[navio3_linha + i][navio3_coluna + i] = NAVIO;
            }
        }
    }
    
    // Navio 4: Diagonal decrescente (linha 2, coluna 7)
    int navio4_linha = 2;
    int navio4_coluna = 7;
    // Validação de limite
    if (navio4_linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO && navio4_coluna - (TAMANHO_NAVIO - 1) >= 0) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[navio4_linha + i][navio4_coluna - i] == AGUA) {
                tabuleiro[navio4_linha + i][navio4_coluna - i] = NAVIO;
            }
        }
    }
    
    // --- 3. Aplicação das Habilidades Especiais ---
    // A validação de limites é feita dentro de cada função de habilidade.
    
    // Ponto de origem para a Habilidade Cone (linha 3, coluna 4)
    aplicarHabilidadeCone(tabuleiro, 3, 4);

    // Ponto de origem para a Habilidade Cruz (linha 5, coluna 5)
    aplicarHabilidadeCruz(tabuleiro, 5, 5);

    // Ponto de origem para a Habilidade Octaedro (linha 3, coluna 3)
    aplicarHabilidadeOctaedro(tabuleiro, 3, 3);

    // --- 4. Exibição do Tabuleiro Final ---
    printf("\n--- Tabuleiro de Batalha Naval (com Navios e Habilidades) ---\n");
    
    // Looping para exibir o tabuleiro.
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    printf("--- Legenda: 0=Agua, 3=Navio, 5=Area da Habilidade ---\n");
    
    return 0;
}

// --- Funções de Aplicação de Habilidade ---

// Função para aplicar a habilidade do tipo Cone.
// O ponto de origem (linha, coluna) será o topo do cone.
void aplicarHabilidadeCone(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    // Looping para percorrer a área de efeito do cone.
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = -i; j <= i; j++) {
            int novaLinha = linha + i;
            int novaColuna = coluna + j;
            
            // Verifica se a posição está dentro dos limites do tabuleiro.
            if (novaLinha >= 0 && novaLinha < TAMANHO_TABULEIRO &&
                novaColuna >= 0 && novaColuna < TAMANHO_TABULEIRO) {
                // Marca a posição como "área de habilidade" se não houver um navio.
                if (tabuleiro[novaLinha][novaColuna] != NAVIO) {
                     tabuleiro[novaLinha][novaColuna] = HABILIDADE;
                }
            }
        }
    }
}

// Função para aplicar a habilidade do tipo Cruz.
// O ponto de origem (linha, coluna) será o centro da cruz.
void aplicarHabilidadeCruz(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    // Looping para preencher a área de efeito da cruz.
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        // Posição horizontal (mantém a linha fixa, varia a coluna)
        int novaLinhaH = linha;
        int novaColunaH = (coluna - CENTRO_HABILIDADE) + i;

        // Posição vertical (mantém a coluna fixa, varia a linha)
        int novaLinhaV = (linha - CENTRO_HABILIDADE) + i;
        int novaColunaV = coluna;

        // Verifica e marca a parte horizontal
        if (novaLinhaH >= 0 && novaLinhaH < TAMANHO_TABULEIRO &&
            novaColunaH >= 0 && novaColunaH < TAMANHO_TABULEIRO) {
            if (tabuleiro[novaLinhaH][novaColunaH] != NAVIO) {
                tabuleiro[novaLinhaH][novaColunaH] = HABILIDADE;
            }
        }

        // Verifica e marca a parte vertical
        if (novaLinhaV >= 0 && novaLinhaV < TAMANHO_TABULEIRO &&
            novaColunaV >= 0 && novaColunaV < TAMANHO_TABULEIRO) {
            if (tabuleiro[novaLinhaV][novaColunaV] != NAVIO) {
                tabuleiro[novaLinhaV][novaColunaV] = HABILIDADE;
            }
        }
    }
}

// Função para aplicar a habilidade do tipo Octaedro.
// O ponto de origem (linha, coluna) será o centro do octaedro.
void aplicarHabilidadeOctaedro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    // Percorre a área de efeito do octaedro em um quadrado de tamanho (HABILIDADE x HABILIDADE).
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Calcula as coordenadas relativas ao centro da matriz de habilidade.
            int dist_i = i - CENTRO_HABILIDADE;
            int dist_j = j - CENTRO_HABILIDADE;
            
            // A condição para a forma de losango (vista de um octaedro) é baseada na distância de Manhattan.
            if (abs(dist_i) + abs(dist_j) <= CENTRO_HABILIDADE) {
                int novaLinha = linha + dist_i;
                int novaColuna = coluna + dist_j;
                
                // Verifica se a posição calculada está dentro dos limites do tabuleiro.
                if (novaLinha >= 0 && novaLinha < TAMANHO_TABULEIRO &&
                    novaColuna >= 0 && novaColuna < TAMANHO_TABULEIRO) {
                    if (tabuleiro[novaLinha][novaColuna] != NAVIO) {
                        tabuleiro[novaLinha][novaColuna] = HABILIDADE;
                    }
                }
            }
        }
    }
}