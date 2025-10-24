// =================================================================
// PRÁTICA: CRIAÇÃO DO JOGO WAR ESTRUTURADO - PARTE 3
//
// OBJETIVO:
// Adicionar a opção de missões utilizando conceitos de modularização e passagem
// de parâmetros em funções
//
// =================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Constantes Globais
#define MAX_TROPAS 5
#define SIZE_STRING 40
#define MAX_BATALHAS 80

// Definição das Structs
struct Territorio {
  char nome[SIZE_STRING];
  char cor[SIZE_STRING];
  int tropas;
};

struct Batalha {
  int territorio_atacante;
  int dado_atacante;
  int territorio_defensor;
  int dado_defensor;
};

struct Jogador {
  int indice;
  int missao;
  int missao_concluida;
};

// Definição de Vetores
char missoes[2][40] = { "Conquistar um exercito inimigo.", "Conquistar cinco tropas consecutivas." };

// Função para limpar o buffer de entrada
void limparBufferEntrada() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
};

void mensagemInicialDoSistema() {
  printf("================================================\n");
  printf("Vamos cadastrar os 5 territorios iniciais do nosso mundo.\n");
};

void cadastroDeTerritorios(struct Territorio territorios[MAX_TROPAS]) {
  for (int totalTropas = 0; totalTropas < MAX_TROPAS; totalTropas++) {
    printf("--- Cadastrando territorio %d ---\n", totalTropas + 1);
    printf("Nome do territorio: ");
    scanf("%s", territorios[totalTropas].nome);

    printf("Cor do exercito (ex: Azul, Verde): ");
    scanf("%s", territorios[totalTropas].cor);

    printf("Numero de tropas: ");
    scanf("%d", &territorios[totalTropas].tropas);
    limparBufferEntrada();
    printf("\n");
  };

  printf("Cadastro inicial concluido com sucesso!\n");
};

void listagemDosTerritorios(struct Territorio territorios[MAX_TROPAS]) {
  printf("============================================\n");
  printf("               MAPA DO MUNDO\n");
  printf("============================================\n");

  for (int totalTropas = 0; totalTropas < MAX_TROPAS; totalTropas++) {
    printf("%d. %s ", totalTropas + 1, territorios[totalTropas].nome);
    printf("(Exercito %s, Tropas: %d)\n", territorios[totalTropas].cor, territorios[totalTropas].tropas);
  };
};

void ataque(struct Batalha *batalha, struct Territorio territorios[MAX_TROPAS], struct Jogador *jogador, int *contador_conquista_tropas) {
    printf("\n\n--- FASE DE ATAQUE ---\n");
    printf("Escolha o territorio atacante (de 1 a 5): ");
    scanf("%d", &batalha->territorio_atacante);
    limparBufferEntrada();
    
    printf("Escolha o territorio defensor (de 1 a 5): ");
    scanf("%d", &batalha->territorio_defensor);
    limparBufferEntrada();
      
    if (territorios[batalha->territorio_atacante - 1].cor == territorios[batalha->territorio_defensor - 1].cor) {
      printf("\nOs territorios escolhidos estao dominados pelo mesmo exercito!\n");
    } else {
        srand(time(0));
    
        batalha->dado_atacante = (rand() % 6) + 1;
        batalha->dado_defensor = (rand() % 6) + 1;
          
        printf("\n--- RESULTADO DA BATALHA ---\n");
        printf("O atacante %s jogou um dado e tirou: %d\n", territorios[batalha->territorio_atacante - 1].nome, batalha->dado_atacante);
        printf("O defensor %s jogou um dado e tirou: %d\n", territorios[batalha->territorio_defensor - 1].nome, batalha->dado_defensor);
          
        // Resultado da batalha
        if (batalha->dado_atacante > batalha->dado_defensor) {
          printf("VITORIA DO ATACANTE! O defensor perdeu 1 tropa.\n");
            
          if (territorios[batalha->territorio_defensor - 1].tropas == 1) {
            strcpy(territorios[batalha->territorio_defensor - 1].cor, territorios[batalha->territorio_atacante - 1].cor);
            printf("CONQUISTA! O territorio %s foi dominado pelo exercito %s!\n", territorios[batalha->territorio_defensor - 1].nome, territorios[batalha->territorio_atacante - 1].cor);
          } else {
            territorios[batalha->territorio_atacante - 1].tropas += 1;
            territorios[batalha->territorio_defensor - 1].tropas -= 1;
            }
        } else if (batalha->dado_atacante == batalha->dado_defensor) {
          printf("A BATALHA DEU EMPATE! Nenhum territorio perdeu tropa.\n");
        } else {
          printf("VITORIA DO DEFENSOR! O atacante perdeu 1 tropa.\n");
            
          if (territorios[batalha->territorio_atacante - 1].tropas == 1) {
            strcpy(territorios[batalha->territorio_atacante - 1].cor, territorios[batalha->territorio_defensor - 1].cor);
            printf("CONQUISTA! O territorio %s foi dominado pelo exercito %s!\n", territorios[batalha->territorio_atacante - 1].nome, territorios[batalha->territorio_defensor - 1].cor);
          } else {
            territorios[batalha->territorio_atacante - 1].tropas -= 1;
            territorios[batalha->territorio_defensor - 1].tropas += 1;
          };
        };
    };
    
    // Avaliar conclusão da missão
    if (jogador->missao == 1) {
      int contador_territorios = 0;
    
      for (int i = 0; i <= 4; i++) {
        if (territorios[i].cor == territorios[jogador->indice - 1].cor) {
          contador_territorios++;
        };
      };
    
      if (contador_territorios > 1) {
        jogador->missao_concluida = 1;
      };
    } else {
      if (batalha->dado_atacante > batalha->dado_defensor && batalha->territorio_atacante == jogador->indice || batalha->dado_atacante < batalha->dado_defensor && batalha->territorio_defensor == jogador->indice) {
        *contador_conquista_tropas++;
      } else {
        *contador_conquista_tropas = 0;
      };
      
      if (*contador_conquista_tropas == 5) {
        jogador->missao_concluida = 1;
      };
    };
};

void atribuirMissao(struct Jogador *jogador) {
  srand(time(0));
  
  jogador->indice = (rand() % 5) + 1;
  jogador->missao = (rand() % 2) + 1;
};

void informarMissao(struct Jogador *jogador, struct Territorio territorios[MAX_TROPAS]) {
  printf("\n--- SUA MISSAO (Exercito %s) ---\n", territorios[jogador->indice - 1].cor);
  printf("%s\n", missoes[jogador->missao - 1]);
};

void verificarMissao(struct Jogador *jogador) {
  if (jogador->missao_concluida == 1) {
    printf("\n\nParabéns! Você concluiu a missão.\n\n");
  } else {
    printf("\n\nVocê ainda não concluiu a missão. Continue tentando.\n\n");
  }
};

void menu(int *opcao_menu, struct Batalha *batalha, struct Territorio territorios[MAX_TROPAS], struct Jogador *jogador) {
  int numero_escolhido;
  int contador_conquista_tropas = 0;
    
  printf("\n--- MENU DE ACOES ---\n");
  printf("1 - Atacar\n");
  printf("2 - Verificar missao\n");
  printf("0 - Sair\n\n");
  printf("Escolha sua acao: ");
  scanf("%d", &numero_escolhido);
  limparBufferEntrada();
  
  *opcao_menu = numero_escolhido;
    
  switch (*opcao_menu) {
    case 1:
        ataque(batalha, territorios, jogador, &contador_conquista_tropas);
        break;
    case 2:
        verificarMissao(jogador);
        break;
    case 0:
        printf("\n\nJogo encerrado...");
        break;
    default:
        printf("\n\nOpcao invalida!\n\n");
  }
};

void liberarMemoriaDinamica(struct Batalha *batalha, struct Territorio territorios[MAX_TROPAS], struct Jogador *jogador) {
  free(batalha);
  free(territorios);
  free(jogador);
};

// Função principal
int main() {
  // Criação de variáveis
  int opcao_menu;
    
  // Criação de ponteiros
  struct Territorio *territorios;
  
  // Alocação dinâmica de memória
  territorios = calloc(MAX_TROPAS, sizeof(struct Territorio));
  
  struct Batalha* batalha = (struct Batalha*) malloc(MAX_BATALHAS * sizeof(struct Batalha));
  
  struct Jogador* jogador = (struct Jogador*) malloc(MAX_TROPAS * sizeof(struct Jogador));
  
  // Verificação de alocação de memória
  if (territorios == NULL || batalha == NULL || jogador == NULL) {
    printf("Falha ao alocar memória!\n");
  };
  
  // Mensagem inicial do sistema
  mensagemInicialDoSistema();
  
  // Cadastro dos territórios
  cadastroDeTerritorios(territorios);
  
  // Criar missão
    atribuirMissao(jogador);
    
  do {
    // Listagem dos territórios
    listagemDosTerritorios(territorios);
    
    // Criar missão
    informarMissao(jogador, territorios);
    
    // Menu de opções
    menu(&opcao_menu, batalha, territorios, jogador);
    
  } while (opcao_menu != 0);
  
  // Liberação de memória dinâmica
  liberarMemoriaDinamica(batalha, territorios, jogador);
};