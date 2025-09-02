// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios e tamanho máximo de strings, facilitando a manutenção.
#define MAX_TROPAS 5 // Mantido como 5 para seguir o exemplo, mas poderia ser alterado.
#define TAM_STRING_NOME 30
#define TAM_STRING_COR 10

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
struct Territorio
{
    char nome[TAM_STRING_NOME];
    char cor[TAM_STRING_COR];
    int tropas;
};

// --- Protótipos das Funções ---
void limparBufferEntrada();
void lancamentodedados(int *ataque, int *defesa);
// Não há outros protótipos, pois as funções adicionais foram incluídas diretamente no main para simplicidade.

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

// --- Função Principal (main) ---
// Orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    // Inicializa o gerador de números aleatórios.
    srand((unsigned int)time(NULL));

    struct Territorio *combat; // Ponteiro para o array dinâmico de territórios.

    // Aloca memória para 5 territórios usando calloc, que também inicializa a memória com zeros.
    combat = (struct Territorio*)calloc(MAX_TROPAS, sizeof(struct Territorio));

    // Verifica se a alocação de memória foi bem-sucedida.
    if (combat == NULL) {
        printf("Erro: Falha ao alocar memoria.\n");
        return 1; // Retorna um código de erro.
    }

    int resultAtaque = 0; // Armazena o resultado do dado de ataque.
    int resultDefesa = 0; // Armazena o resultado do dado de defesa.
    int opcaoAtaque;
    int opcaoDefesa;

    printf("Vamos cadastrar 5 territorios iniciais do nosso mundo.\n\n");

    // Loop para cadastrar os 5 territórios.
    for (int i = 0; i < MAX_TROPAS; i++) {
        printf("--- Cadastrando Territorio %d ---\n", i + 1);

        printf("Nome do Territorio: ");
        fgets(combat[i].nome, TAM_STRING_NOME, stdin);

        printf("Cor do Territorio (Ex: Azul, Verde...): ");
        fgets(combat[i].cor, TAM_STRING_COR, stdin);

        // Remove o caractere de nova linha ('\n') que o fgets captura.
        combat[i].nome[strcspn(combat[i].nome, "\n")] = 0;
        combat[i].cor[strcspn(combat[i].cor, "\n")] = 0;

        // *** SUGESTÃO 1: Validação da quantidade de tropas ***
        // Garante que o número de tropas esteja dentro do intervalo permitido.
        do {
            printf("Numero de tropas (1 a 5): ");
            scanf("%d", &combat[i].tropas);
            limparBufferEntrada();
            if (combat[i].tropas < 1 || combat[i].tropas > 5) {
                printf("Numero invalido! Por favor, insira um valor entre 1 e 5.\n");
            }
        } while (combat[i].tropas < 1 || combat[i].tropas > 5);

        printf("\n");
    }

    // Loop principal do jogo (Fase de Ataque).
    do {
        printf("====================================\n");
        printf("      Mapa do Mundo - Estado Atual  \n");
        printf("====================================\n");

        // Exibe o status de todos os territórios.
        for (int i = 0; i < MAX_TROPAS; i++) {
            // Se um território não tiver mais tropas, indica que está neutro ou derrotado.
            if (combat[i].tropas > 0) {
                 printf("%d- %s (Exercito: %s, Tropas: %d)\n", i + 1, combat[i].nome, combat[i].cor, combat[i].tropas);
            } else {
                 printf("%d- %s (Territorio SEM TROPAS)\n", i + 1, combat[i].nome);
            }
        }

        printf("\n              Fase de Ataque          \n");
        printf("----------------------------------------\n");
        printf("Escolha o Territorio do Atacante (1 a %d ou 0 para sair): ", MAX_TROPAS);
        scanf("%d", &opcaoAtaque);
        limparBufferEntrada();

        if (opcaoAtaque == 0) {
            break; // Sai do loop do jogo.
        }

        // Valida a opção de ataque.
        if (opcaoAtaque >= 1 && opcaoAtaque <= MAX_TROPAS) {
            int indexAtaque = opcaoAtaque - 1;

            // *** SUGESTÃO 2: Verificar se o atacante tem tropas para atacar ***
            if (combat[indexAtaque].tropas <= 1) {
                printf("\nATAQUE INVALIDO! O territorio %s precisa de mais de 1 tropa para atacar.\n\n", combat[indexAtaque].nome);
                continue; // Volta para o início do loop.
            }

            printf("Escolha o Territorio para defender (1 a %d): ", MAX_TROPAS);
            scanf("%d", &opcaoDefesa);
            limparBufferEntrada();

            int indexDefesa = opcaoDefesa - 1;

            // Valida a opção de defesa.
            if (opcaoDefesa < 1 || opcaoDefesa > MAX_TROPAS || opcaoDefesa == opcaoAtaque) {
                printf("\nOpcao de defesa invalida!\n\n");
                continue;
            }
            
            // *** SUGESTÃO 3: Impedir ataque a territórios do mesmo exército (mesma cor) ***
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
                combat[indexDefesa].tropas--; // O defensor perde uma tropa.

                // *** SUGESTÃO 4: Lógica de conquista de território ***
                if (combat[indexDefesa].tropas == 0) {
                    printf("CONQUISTA! O territorio %s foi dominado por %s!\n", combat[indexDefesa].nome, combat[indexAtaque].nome);
                    
                    // O território conquistado agora pertence ao atacante.
                    strcpy(combat[indexDefesa].cor, combat[indexAtaque].cor); 
                    
                    // O atacante move uma tropa para o novo território.
                    combat[indexDefesa].tropas = 1;
                    combat[indexAtaque].tropas--;

                } else {
                    printf("%s agora tem %d tropas.\n\n", combat[indexDefesa].nome, combat[indexDefesa].tropas);
                }

            } else { // Empate ou vitória da defesa
                printf("DEFESA BEM-SUCEDIDA! O territorio %s repeliu o ataque!\n", combat[indexDefesa].nome);
                // O atacante perde uma tropa na derrota.
                combat[indexAtaque].tropas--;
                printf("%s (atacante) agora tem %d tropas.\n\n", combat[indexAtaque].nome, combat[indexAtaque].tropas);
            }
        } else {
            printf("\nOpcao de ataque invalida! Escolha um numero entre 1 e %d.\n", MAX_TROPAS);
        }

    } while (opcaoAtaque != 0);

    printf("\nFinalizando jogo...\n");

    // Libera a memória alocada para os territórios.
    free(combat);
    return 0;
}