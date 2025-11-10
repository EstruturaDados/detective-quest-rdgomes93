#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
};

struct Sala* criarSala(const char* nome) {
    struct Sala* novaSala = (struct Sala*)malloc(sizeof(struct Sala));

    if (novaSala == NULL) {
        printf("Erro critico: Falha ao alocar memoria para o mapa!\n");
        exit(1);
    }

    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;

    return novaSala;
}

void explorarSalas(struct Sala* salaAtual) {
    char escolha;

    printf("--- Bem-vindo ao Detective Quest ---\n");
    printf("Voce esta na frente da mansao. A porta se abre...\n");

    while (salaAtual != NULL) {
        
        printf("\n==========================================\n");
        printf("Voce esta em: %s\n", salaAtual->nome);
        printf("==========================================\n");

        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("Nao ha mais caminhos. Voce chegou a um fim!\n");
            printf("Fim da exploracao.\n");
            break;
        }

        printf("Para onde voce quer ir?\n");

        if (salaAtual->esquerda != NULL) {
            printf(" (e) Esquerda -> (%s)\n", salaAtual->esquerda->nome);
        }
        
        if (salaAtual->direita != NULL) {
            printf(" (d) Direita  -> (%s)\n", salaAtual->direita->nome);
        }

        printf(" (s) Sair do jogo\n");
        printf("Escolha seu caminho: ");

        scanf(" %c", &escolha);

        switch (escolha) {
            case 'e':
            case 'E':
                if (salaAtual->esquerda != NULL) {
                    salaAtual = salaAtual->esquerda;
                } else {
                    printf("-> Voce tentou ir pela esquerda, mas nao ha porta.\n");
                }
                break;

            case 'd':
            case 'D':
                if (salaAtual->direita != NULL) {
                    salaAtual = salaAtual->direita;
                } else {
                    printf("-> Voce tentou ir pela direita, mas a porta esta trancada.\n");
                }
                break;

            case 's':
            case 'S':
                printf("\nVoce decidiu sair da mansao. Ate a proxima, detetive!\n");
                return;

            default:
                printf("\n[ERRO] Comando invalido. Tente 'e', 'd' ou 's'.\n");
                break;
        }
    }
}

void liberarMapa(struct Sala* sala) {
    if (sala == NULL) {
        return;
    }
    liberarMapa(sala->esquerda);
    liberarMapa(sala->direita);
    free(sala);
}

int main() {
    struct Sala* raiz = criarSala("Hall de Entrada");

    raiz->esquerda = criarSala("Sala de Estar");
    raiz->direita = criarSala("Cozinha");

    raiz->esquerda->esquerda = criarSala("Biblioteca");
    raiz->esquerda->direita = criarSala("Escritorio");
    raiz->direita->esquerda = criarSala("Jardim");
    raiz->direita->direita = criarSala("Sala de Jantar");

    raiz->esquerda->esquerda->esquerda = criarSala("Passagem Secreta");
    raiz->direita->esquerda->direita = criarSala("Cabana");

    explorarSalas(raiz);

    liberarMapa(raiz);

    return 0;
}