#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CAPACIDADE_MOCHILA 10

// Item agrupa os dados essenciais de cada recurso armazenado na mochila.
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

void limparEntrada(void) {
    int caractere;

    while ((caractere = getchar()) != '\n' && caractere != EOF) {
        /* Descarta o restante da entrada para a próxima leitura. */
    }
}

void lerTexto(const char *mensagem, char *texto, size_t tamanho) {
    printf("%s", mensagem);
    fgets(texto, tamanho, stdin);
    texto[strcspn(texto, "\n")] = '\0';
}

// Lista todos os itens cadastrados e seus dados atuais.
void listarItens(const Item mochila[], int numItens) {
    int indice;

    printf("\n===== ITENS DA MOCHILA =====\n");
    if (numItens == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }

    for (indice = 0; indice < numItens; indice++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               indice + 1, mochila[indice].nome, mochila[indice].tipo,
               mochila[indice].quantidade);
    }
}

// Cadastra um item no proximo espaco livre do vetor sequencial.
void inserirItem(Item mochila[], int *numItens) {
    Item novoItem;

    if (*numItens >= CAPACIDADE_MOCHILA) {
        printf("\nA mochila esta cheia. Remova um item antes de cadastrar outro.\n");
        return;
    }

    printf("\n===== CADASTRO DE ITEM =====\n");
    lerTexto("Nome: ", novoItem.nome, sizeof(novoItem.nome));
    lerTexto("Tipo (arma, municao, cura ou ferramenta): ",
             novoItem.tipo, sizeof(novoItem.tipo));
    printf("Quantidade: ");
    if (scanf("%d", &novoItem.quantidade) != 1 || novoItem.quantidade < 0) {
        limparEntrada();
        printf("Quantidade invalida. O item nao foi cadastrado.\n");
        return;
    }
    limparEntrada();

    mochila[*numItens] = novoItem;
    (*numItens)++;
    printf("Item cadastrado com sucesso!\n");
}

// Remove o item encontrado e desloca os itens seguintes para fechar a lacuna.
void removerItem(Item mochila[], int *numItens) {
    char nomeBusca[30];
    int indice;
    int deslocamento;

    if (*numItens == 0) {
        printf("\nNao ha itens para remover.\n");
        return;
    }

    lerTexto("\nNome do item a remover: ", nomeBusca, sizeof(nomeBusca));
    for (indice = 0; indice < *numItens; indice++) {
        if (strcmp(mochila[indice].nome, nomeBusca) == 0) {
            for (deslocamento = indice; deslocamento < *numItens - 1; deslocamento++) {
                mochila[deslocamento] = mochila[deslocamento + 1];
            }
            (*numItens)--;
            printf("Item removido com sucesso!\n");
            return;
        }
    }

    printf("Item nao encontrado na mochila.\n");
}

// Faz uma busca sequencial pelo nome e exibe o item quando ele existe.
void buscarItem(const Item mochila[], int numItens) {
    char nomeBusca[30];
    int indice;

    lerTexto("\nNome do item a buscar: ", nomeBusca, sizeof(nomeBusca));
    for (indice = 0; indice < numItens; indice++) {
        if (strcmp(mochila[indice].nome, nomeBusca) == 0) {
            printf("Item encontrado: Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[indice].nome, mochila[indice].tipo,
                   mochila[indice].quantidade);
            return;
        }
    }

    printf("Item nao encontrado na mochila.\n");
}

int main() {
    Item mochila[CAPACIDADE_MOCHILA];
    int numItens = 0;
    int opcao;

    // O menu repete as operacoes ate o jogador escolher sair.
    do {
        printf("\n===== MOCHILA DE LOOT INICIAL =====\n");
        printf("1. Cadastrar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item por nome\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            limparEntrada();
            printf("Opcao invalida. Digite um numero do menu.\n");
            continue;
        }
        limparEntrada();

        switch (opcao) {
            case 1:
                inserirItem(mochila, &numItens);
                listarItens(mochila, numItens);
                break;
            case 2:
                removerItem(mochila, &numItens);
                listarItens(mochila, numItens);
                break;
            case 3:
                listarItens(mochila, numItens);
                break;
            case 4:
                buscarItem(mochila, numItens);
                listarItens(mochila, numItens);
                break;
            case 0:
                printf("Encerrando a mochila. Ate a proxima partida!\n");
                break;
            default:
                printf("Opcao invalida. Escolha uma opcao do menu.\n");
        }
    } while (opcao != 0);

    return 0;
}
