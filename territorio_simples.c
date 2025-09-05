// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios e tamanho máximo de strings, facilitando a manutenção.
#define NUM_TERRITORIOS 5
#define NUM_MAX_TROPAS_POR_TERRITORIO 5
#define TAM_STRING_NOME 30
#define TAM_STRING_COR 10
#define TAM_STRING_MISSOES 100
#define NUM_MISSOES 5

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
struct Territorio
{
    char nome[TAM_STRING_NOME];
    char cor[TAM_STRING_COR];
    int tropas;
};

// Array global com as missões disponíveis no jogo.
char *missoes[NUM_MISSOES] = {
    "Conquistar 5 Territorios seguidos",
    "Elinar todas as Tropas de um adversario",
    "Vença 2 Adversarios",
    "Destrua todo o exercito",
    "Vença 1 Adversario"
};


// --- Protótipos das Funções ---
void limparBufferEntrada();
void lancamentodedados(int *ataque, int *defesa);
void atribuirMissao(char *destino, char* missoes[], int totalMissoes);
void verificaMissao(const char *missao, struct Territorio *mapa, int tamanho);

// --- Definições das Funções ---

// Limpa o buffer de entrada para evitar que caracteres residuais (como o '\n') interfiram nas próximas leituras.
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Simula o lançamento de dois dados de 6 faces, um para o ataque e outro para a defesa.
void lancamentodedados(int *ataque, int *defesa) {
    *ataque = (rand() % 6) + 1;
    *defesa = (rand() % 6) + 1;
}

// Atribui uma missão aleatória ao jogador.
void atribuirMissao(char *destino, char* missoes[], int totalMissoes) {
    int indiceAleatorio = rand() % totalMissoes;
    strcpy(destino, missoes[indiceAleatorio]);
}

// Verifica se a missão do jogador foi concluída.
void verificaMissao(const char *missao, struct Territorio *mapa, int tamanho) {
    printf("\n--- Verificando Missao: \"%s\" ---\n", missao);

    // Exemplo de implementação para uma das missões.
    // strcmp compara duas strings. Retorna 0 se forem iguais.
    if (strcmp(missao, "Conquistar 5 Territorios seguidos") == 0 || strcmp(missao, "Destrua todo o exercito") == 0) {
        char primeiraCor[TAM_STRING_COR];
        strcpy(primeiraCor, mapa[0].cor); // Pega a cor do primeiro território como referência.
        int todosIguais = 1; // Começa assumindo que todos são da mesma cor.

        for (int i = 1; i < tamanho; i++) {
            if (strcmp(primeiraCor, mapa[i].cor) != 0) {
                todosIguais = 0; // Encontrou uma cor diferente, então a condição é falsa.
                break;
            }
        }

        if (todosIguais) {
            printf("Resultado: MISSAO CUMPRIDA! Voce conquistou todos os territorios!\n\n");
        } else {
            printf("Resultado: Missao ainda nao cumprida. Continue lutando!\n\n");
        }
    } else {
        // As outras missões exigem uma lógica mais complexa, como rastrear jogadores eliminados.
        printf("Resultado: A logica para esta missao ainda nao foi implementada.\n\n");
    }
}


// --- Função Principal (main) ---
int main() {
    srand((unsigned int)time(NULL));

    struct Territorio *combat;
    combat = (struct Territorio*)calloc(NUM_TERRITORIOS, sizeof(struct Territorio));

    if (combat == NULL) {
        printf("Erro: Falha ao alocar memoria.\n");
        return 1;
    }

    int resultAtaque = 0;
    int resultDefesa = 0;
    int opcaoMenu;

    printf("Vamos cadastrar %d territorios iniciais do nosso mundo.\n\n", NUM_TERRITORIOS);

    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("--- Cadastrando Territorio %d ---\n", i + 1);

        printf("Nome do Territorio: ");
        fgets(combat[i].nome, TAM_STRING_NOME, stdin);
        combat[i].nome[strcspn(combat[i].nome, "\n")] = 0;

        printf("Cor do Territorio (Ex: Azul, Verde...): ");
        fgets(combat[i].cor, TAM_STRING_COR, stdin);
        combat[i].cor[strcspn(combat[i].cor, "\n")] = 0;

        do {
            printf("Numero de tropas (1 a %d): ", NUM_MAX_TROPAS_POR_TERRITORIO);
            scanf("%d", &combat[i].tropas);
            limparBufferEntrada();
            if (combat[i].tropas < 1 || combat[i].tropas > NUM_MAX_TROPAS_POR_TERRITORIO) {
                printf("Numero invalido! Por favor, insira um valor entre 1 e %d.\n", NUM_MAX_TROPAS_POR_TERRITORIO);
            }
        } while (combat[i].tropas < 1 || combat[i].tropas > NUM_MAX_TROPAS_POR_TERRITORIO);

        printf("\n");
    }

    // Atribui uma missão ao jogador antes do jogo começar.
    char missaoAtual[TAM_STRING_MISSOES];
    atribuirMissao(missaoAtual, missoes, NUM_MISSOES);
    printf("====================================\n");
    printf("Sua missao e: %s\n", missaoAtual);
    printf("====================================\n\n");

    // loop principal 
    do {
        printf("====================================\n");
        printf("      Mapa do Mundo - Estado Atual   \n");
        printf("====================================\n");

        for (int i = 0; i < NUM_TERRITORIOS; i++) {
            if (combat[i].tropas > 0) {
                 printf("%d- %s (Exercito: %s, Tropas: %d)\n", i + 1, combat[i].nome, combat[i].cor, combat[i].tropas);
            } else {
                 printf("%d- %s (Territorio SEM TROPAS)\n", i + 1, combat[i].nome);
            }
        }
        printf("====================================\n\n");

        printf("--- Menu de Acoes ---\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missao\n");
        printf("0 - Sair do jogo\n");
        printf("Escolha sua acao: ");
        scanf("%d", &opcaoMenu);
        limparBufferEntrada();

        // opção para chamar a funcao de opcoes de missoes
        switch (opcaoMenu) {
            case 1: {
                int opcaoAtaque, opcaoDefesa;

                printf("\n               Fase de Ataque              \n");
                printf("----------------------------------------\n");
                printf("Escolha o Territorio do Atacante (1 a %d ou 0 para cancelar): ", NUM_TERRITORIOS);
                scanf("%d", &opcaoAtaque);
                limparBufferEntrada();

                if (opcaoAtaque == 0) {
                    printf("Ataque cancelado.\n\n");
                    continue; // Volta para o início do loop do menu.
                }

                if (opcaoAtaque < 1 || opcaoAtaque > NUM_TERRITORIOS) {
                    printf("\nOpcao de ataque invalida! Escolha um numero entre 1 e %d.\n\n", NUM_TERRITORIOS);
                    continue;
                }

                int indexAtaque = opcaoAtaque - 1;

                //nessa logica deixa um exercito para defender o posto conquistado
                if (combat[indexAtaque].tropas <= 1) {
                    printf("\nATAQUE INVALIDO! O territorio %s precisa de mais de 1 tropa para atacar.\n\n", combat[indexAtaque].nome);
                    continue;
                }

                printf("Escolha o Territorio para defender (1 a %d): ", NUM_TERRITORIOS);
                scanf("%d", &opcaoDefesa);
                limparBufferEntrada();

                int indexDefesa = opcaoDefesa - 1;

                if (opcaoDefesa < 1 || opcaoDefesa > NUM_TERRITORIOS || opcaoDefesa == opcaoAtaque) {
                    printf("\nOpcao de defesa invalida!\n\n");
                    continue;
                }
                
                if (strcmp(combat[indexAtaque].cor, combat[indexDefesa].cor) == 0) {
                    printf("\nATAQUE INVALIDO! Nao e possivel atacar um territorio aliado (mesma cor).\n\n");
                    continue;
                }

                printf("\n--- Batalha entre %s e %s ---\n", combat[indexAtaque].nome, combat[indexDefesa].nome);

                lancamentodedados(&resultAtaque, &resultDefesa);

                printf("Dados do Ataque: %d\n", resultAtaque);
                printf("Dados da Defesa: %d\n\n", resultDefesa);

                if (resultAtaque > resultDefesa) {
                    printf("VITORIA! O territorio %s venceu o ataque!\n", combat[indexAtaque].nome);
                    combat[indexDefesa].tropas--;

                    if (combat[indexDefesa].tropas == 0) {
                        printf("CONQUISTA! O territorio %s foi dominado por %s!\n", combat[indexDefesa].nome, combat[indexAtaque].nome);
                        strcpy(combat[indexDefesa].cor, combat[indexAtaque].cor); 
                        combat[indexDefesa].tropas = 1;
                        combat[indexAtaque].tropas--;
                    } else {
                        printf("%s agora tem %d tropas.\n", combat[indexDefesa].nome, combat[indexDefesa].tropas);
                    }
                } else {
                    printf("DEFESA BEM-SUCEDIDA! O territorio %s repeliu o ataque!\n", combat[indexDefesa].nome);
                    combat[indexAtaque].tropas--;
                    printf("%s (atacante) agora tem %d tropas.\n", combat[indexAtaque].nome, combat[indexAtaque].tropas);
                }
                printf("\n");
                break;
            }
            case 2:
                // opção para verificar a missao .
                verificaMissao(missaoAtual, combat, NUM_TERRITORIOS);
                break;
            case 0:
                printf("\nFinalizando jogo...\n");
                break;
            default:
                printf("\nOpcao invalida! Por favor, escolha uma das acoes do menu.\n\n");
                break;
        }

    } while (opcaoMenu != 0);

    // Libera a memória alocada para os territórios.
    free(combat);
    return 0;
}