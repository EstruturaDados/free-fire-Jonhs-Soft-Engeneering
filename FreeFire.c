#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACIDADE_MOCHILA 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

/* Vetor: memoria contigua e capacidade fixa. */
typedef struct {
    Item itens[CAPACIDADE_MOCHILA];
    int quantidade;
    int ordenadoPorNome;
} MochilaVetor;

/* Lista: cada no e alocado dinamicamente e aponta para o proximo. */
typedef struct No {
    Item dados;
    struct No *proximo;
} No;

void limparEntrada(void) {
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
}

void lerTexto(const char *mensagem, char *texto, size_t tamanho) {
    printf("%s", mensagem);
    if (fgets(texto, (int)tamanho, stdin) == NULL) {
        texto[0] = '\0';
        return;
    }
    texto[strcspn(texto, "\n")] = '\0';
}

int lerQuantidade(void) {
    int quantidade;
    printf("Quantidade: ");
    if (scanf("%d", &quantidade) != 1 || quantidade < 0) {
        limparEntrada();
        return -1;
    }
    limparEntrada();
    return quantidade;
}

Item lerItem(void) {
    Item item;
    lerTexto("Nome: ", item.nome, sizeof(item.nome));
    lerTexto("Tipo (arma, municao, cura ou ferramenta): ", item.tipo,
             sizeof(item.tipo));
    item.quantidade = lerQuantidade();
    return item;
}

void exibirItem(const Item *item) {
    printf("Nome: %s | Tipo: %s | Quantidade: %d\n", item->nome,
           item->tipo, item->quantidade);
}

void listarItensVetor(const MochilaVetor *mochila) {
    int indice;
    printf("\n===== MOCHILA (VETOR) =====\n");
    if (mochila->quantidade == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }
    for (indice = 0; indice < mochila->quantidade; indice++) {
        printf("%d. ", indice + 1);
        exibirItem(&mochila->itens[indice]);
    }
}

void inserirItemVetor(MochilaVetor *mochila) {
    Item novoItem;
    if (mochila->quantidade >= CAPACIDADE_MOCHILA) {
        printf("Mochila cheia (limite: %d itens).\n", CAPACIDADE_MOCHILA);
        return;
    }
    novoItem = lerItem();
    if (novoItem.quantidade < 0) {
        printf("Quantidade invalida. Item nao cadastrado.\n");
        return;
    }
    mochila->itens[mochila->quantidade++] = novoItem;
    mochila->ordenadoPorNome = 0;
    printf("Item inserido no vetor.\n");
}

int removerItemVetor(MochilaVetor *mochila, const char *nome) {
    int indice;
    for (indice = 0; indice < mochila->quantidade; indice++) {
        if (strcmp(mochila->itens[indice].nome, nome) == 0) {
            for (; indice < mochila->quantidade - 1; indice++) {
                mochila->itens[indice] = mochila->itens[indice + 1];
            }
            mochila->quantidade--;
            mochila->ordenadoPorNome = 0;
            return 1;
        }
    }
    return 0;
}

void ordenarVetor(MochilaVetor *mochila) {
    int passou, indice;
    Item temporario;
    for (passou = 0; passou < mochila->quantidade - 1; passou++) {
        for (indice = 0; indice < mochila->quantidade - passou - 1; indice++) {
            if (strcmp(mochila->itens[indice].nome,
                       mochila->itens[indice + 1].nome) > 0) {
                temporario = mochila->itens[indice];
                mochila->itens[indice] = mochila->itens[indice + 1];
                mochila->itens[indice + 1] = temporario;
            }
        }
    }
    mochila->ordenadoPorNome = 1;
    printf("Vetor ordenado por nome com Bubble Sort.\n");
}

int buscarSequencialVetor(const MochilaVetor *mochila, const char *nome,
                          int *comparacoes) {
    int indice;
    *comparacoes = 0;
    for (indice = 0; indice < mochila->quantidade; indice++) {
        (*comparacoes)++;
        if (strcmp(mochila->itens[indice].nome, nome) == 0) {
            return indice;
        }
    }
    return -1;
}

int buscarBinariaVetor(const MochilaVetor *mochila, const char *nome,
                       int *comparacoes) {
    int inicio = 0, fim = mochila->quantidade - 1;
    *comparacoes = 0;
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        int resultado;
        (*comparacoes)++;
        resultado = strcmp(mochila->itens[meio].nome, nome);
        if (resultado == 0) {
            return meio;
        }
        if (resultado < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return -1;
}

void listarItensLista(const No *inicio) {
    int indice = 1;
    printf("\n===== MOCHILA (LISTA ENCADEADA) =====\n");
    if (inicio == NULL) {
        printf("A mochila esta vazia.\n");
        return;
    }
    while (inicio != NULL) {
        printf("%d. ", indice++);
        exibirItem(&inicio->dados);
        inicio = inicio->proximo;
    }
}

void inserirItemLista(No **inicio) {
    No *novoNo = malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Falha ao alocar memoria.\n");
        return;
    }
    novoNo->dados = lerItem();
    if (novoNo->dados.quantidade < 0) {
        free(novoNo);
        printf("Quantidade invalida. Item nao cadastrado.\n");
        return;
    }
    novoNo->proximo = *inicio;
    *inicio = novoNo;
    printf("Item inserido na lista encadeada.\n");
}

int removerItemLista(No **inicio, const char *nome) {
    No *atual = *inicio;
    No *anterior = NULL;
    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL) {
                *inicio = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            return 1;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    return 0;
}

int buscarSequencialLista(const No *inicio, const char *nome,
                          int *comparacoes) {
    *comparacoes = 0;
    while (inicio != NULL) {
        (*comparacoes)++;
        if (strcmp(inicio->dados.nome, nome) == 0) {
            return 1;
        }
        inicio = inicio->proximo;
    }
    return 0;
}

void liberarLista(No **inicio) {
    No *atual = *inicio;
    while (atual != NULL) {
        No *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    *inicio = NULL;
}

void operarVetor(MochilaVetor *mochila) {
    int opcao;
    char nome[30];
    do {
        printf("\n===== MENU DO VETOR =====\n");
        printf("1. Inserir\n2. Remover\n3. Listar\n4. Buscar sequencial\n");
        printf("5. Ordenar por nome\n6. Buscar binaria\n0. Voltar\nEscolha: ");
        if (scanf("%d", &opcao) != 1) {
            limparEntrada();
            printf("Opcao invalida.\n");
            continue;
        }
        limparEntrada();
        switch (opcao) {
            case 1:
                inserirItemVetor(mochila);
                break;
            case 2:
                lerTexto("Nome a remover: ", nome, sizeof(nome));
                printf(removerItemVetor(mochila, nome) ? "Item removido.\n"
                                                        : "Item nao encontrado.\n");
                break;
            case 3:
                listarItensVetor(mochila);
                break;
            case 4: {
                int comparacoes, indice;
                lerTexto("Nome a buscar: ", nome, sizeof(nome));
                indice = buscarSequencialVetor(mochila, nome, &comparacoes);
                if (indice >= 0) exibirItem(&mochila->itens[indice]);
                else printf("Item nao encontrado.\n");
                printf("Comparacoes (busca sequencial): %d\n", comparacoes);
                break;
            }
            case 5:
                ordenarVetor(mochila);
                break;
            case 6: {
                int comparacoes, indice;
                if (!mochila->ordenadoPorNome) {
                    printf("Ordene o vetor por nome antes da busca binaria.\n");
                    break;
                }
                lerTexto("Nome a buscar: ", nome, sizeof(nome));
                indice = buscarBinariaVetor(mochila, nome, &comparacoes);
                if (indice >= 0) exibirItem(&mochila->itens[indice]);
                else printf("Item nao encontrado.\n");
                printf("Comparacoes (busca binaria): %d\n", comparacoes);
                break;
            }
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

void operarLista(No **inicio) {
    int opcao;
    char nome[30];
    do {
        printf("\n===== MENU DA LISTA ENCADEADA =====\n");
        printf("1. Inserir\n2. Remover\n3. Listar\n4. Buscar sequencial\n0. Voltar\nEscolha: ");
        if (scanf("%d", &opcao) != 1) {
            limparEntrada();
            printf("Opcao invalida.\n");
            continue;
        }
        limparEntrada();
        switch (opcao) {
            case 1:
                inserirItemLista(inicio);
                break;
            case 2:
                lerTexto("Nome a remover: ", nome, sizeof(nome));
                printf(removerItemLista(inicio, nome) ? "Item removido.\n"
                                                       : "Item nao encontrado.\n");
                break;
            case 3:
                listarItensLista(*inicio);
                break;
            case 4: {
                int comparacoes;
                int encontrado;
                lerTexto("Nome a buscar: ", nome, sizeof(nome));
                encontrado = buscarSequencialLista(*inicio, nome, &comparacoes);
                printf(encontrado ? "Item encontrado.\n" : "Item nao encontrado.\n");
                printf("Comparacoes (busca sequencial): %d\n", comparacoes);
                break;
            }
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

int main(void) {
    MochilaVetor mochilaVetor = {0};
    No *inicioLista = NULL;
    int opcao;
    do {
        printf("\n===== SISTEMA DE MOCHILAS =====\n");
        printf("1. Usar vetor\n2. Usar lista encadeada\n3. Comparar estruturas\n0. Sair\nEscolha: ");
        if (scanf("%d", &opcao) != 1) {
            limparEntrada();
            printf("Opcao invalida.\n");
            continue;
        }
        limparEntrada();
        switch (opcao) {
            case 1:
                operarVetor(&mochilaVetor);
                break;
            case 2:
                operarLista(&inicioLista);
                break;
            case 3:
                printf("Vetor: insercao no fim O(1), remocao pode deslocar itens e busca binaria apos ordenacao.\n");
                printf("Lista: insercao no inicio O(1), remocao e busca sao sequenciais.\n");
                printf("Use os contadores exibidos para comparar as buscas na pratica.\n");
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
    liberarLista(&inicioLista);
    printf("Sistema encerrado.\n");
    return 0;
}
