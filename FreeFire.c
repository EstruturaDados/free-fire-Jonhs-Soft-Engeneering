#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

/* Estas variaveis permitem informar metricas sem alterar as assinaturas exigidas. */
static long long comparacoesOrdenacao;
static int comparacoesBusca;

/* Remove o restante da linha quando a entrada ultrapassa o tamanho do campo. */
void limparEntrada(void) {
    int caractere;
    while ((caractere = getchar()) != '\n' && caractere != EOF) {
    }
}

/* Le uma string com limite de tamanho e remove a quebra de linha. */
void lerTexto(const char *mensagem, char *texto, size_t tamanho) {
    printf("%s", mensagem);
    if (fgets(texto, (int)tamanho, stdin) == NULL) {
        texto[0] = '\0';
        return;
    }
    if (strchr(texto, '\n') == NULL) {
        limparEntrada();
    }
    texto[strcspn(texto, "\n")] = '\0';
}

/* Le um inteiro dentro do intervalo solicitado usando fgets e strtol. */
int lerInteiro(const char *mensagem, int minimo, int maximo) {
    char entrada[64];
    char *fim;
    long valor;

    for (;;) {
        lerTexto(mensagem, entrada, sizeof(entrada));
        valor = strtol(entrada, &fim, 10);
        while (*fim == ' ' || *fim == '\t') {
            fim++;
        }
        if (entrada[0] != '\0' && *fim == '\0' && valor >= minimo &&
            valor <= maximo) {
            return (int)valor;
        }
        printf("Digite um valor entre %d e %d.\n", minimo, maximo);
    }
}

/* Exibe todos os componentes em formato de tabela. */
void mostrarComponentes(Componente vetor[], int tamanho) {
    int indice;
    printf("\n%-4s %-29s %-19s %s\n", "No.", "Nome", "Tipo", "Prioridade");
    printf("---------------------------------------------------------------\n");
    if (tamanho == 0) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }
    for (indice = 0; indice < tamanho; indice++) {
        printf("%-4d %-29s %-19s %d\n", indice + 1, vetor[indice].nome,
               vetor[indice].tipo, vetor[indice].prioridade);
    }
}

/* Ordena os componentes por prioridade crescente com Selection Sort. */
void selectionSortPrioridade(Componente vetor[], int tamanho) {
    int indice, menor, proximo;
    Componente temporario;
    comparacoesOrdenacao = 0;
    for (indice = 0; indice < tamanho - 1; indice++) {
        menor = indice;
        for (proximo = indice + 1; proximo < tamanho; proximo++) {
            comparacoesOrdenacao++;
            if (vetor[proximo].prioridade < vetor[menor].prioridade) {
                menor = proximo;
            }
        }
        if (menor != indice) {
            temporario = vetor[indice];
            vetor[indice] = vetor[menor];
            vetor[menor] = temporario;
        }
    }
}

/* Ordena os componentes por tipo em ordem alfabetica com Insertion Sort. */
void insertionSortTipo(Componente vetor[], int tamanho) {
    int indice, posicao, resultado;
    Componente chave;
    comparacoesOrdenacao = 0;
    for (indice = 1; indice < tamanho; indice++) {
        chave = vetor[indice];
        posicao = indice - 1;
        while (posicao >= 0) {
            resultado = strcmp(vetor[posicao].tipo, chave.tipo);
            comparacoesOrdenacao++;
            if (resultado <= 0) {
                break;
            }
            vetor[posicao + 1] = vetor[posicao];
            posicao--;
        }
        vetor[posicao + 1] = chave;
    }
}

/* Ordena os componentes por nome em ordem alfabetica com Bubble Sort. */
void bubbleSortNome(Componente vetor[], int tamanho) {
    int passou, indice;
    Componente temporario;
    comparacoesOrdenacao = 0;
    for (passou = 0; passou < tamanho - 1; passou++) {
        for (indice = 0; indice < tamanho - passou - 1; indice++) {
            comparacoesOrdenacao++;
            if (strcmp(vetor[indice].nome, vetor[indice + 1].nome) > 0) {
                temporario = vetor[indice];
                vetor[indice] = vetor[indice + 1];
                vetor[indice + 1] = temporario;
            }
        }
    }
}

/* Mede o tempo de CPU e mostra as comparacoes feitas pelo algoritmo. */
void medirTempo(void (*algoritmo)(Componente[], int), Componente vetor[],
                int tamanho) {
    clock_t inicio = clock();
    algoritmo(vetor, tamanho);
    clock_t fim = clock();
    double segundos = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Comparacoes: %lld | Tempo: %.6f segundos\n", comparacoesOrdenacao,
           segundos);
}

/* Busca um nome em vetor previamente ordenado por nome. */
int buscaBinariaPorNome(Componente vetor[], int tamanho, char nome[]) {
    int inicio = 0;
    int fim = tamanho - 1;
    comparacoesBusca = 0;
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        int resultado = strcmp(vetor[meio].nome, nome);
        comparacoesBusca++;
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

/* Cadastra um componente e invalida a ordenacao anterior. */
void cadastrarComponente(Componente vetor[], int *tamanho, int *ordenadoPorNome) {
    if (*tamanho >= MAX_COMPONENTES) {
        printf("Limite de %d componentes atingido.\n", MAX_COMPONENTES);
        return;
    }
    lerTexto("Nome do componente: ", vetor[*tamanho].nome,
             sizeof(vetor[*tamanho].nome));
    lerTexto("Tipo do componente: ", vetor[*tamanho].tipo,
             sizeof(vetor[*tamanho].tipo));
    vetor[*tamanho].prioridade = lerInteiro("Prioridade (1 a 10): ", 1, 10);
    (*tamanho)++;
    *ordenadoPorNome = 0;
    printf("Componente cadastrado.\n");
}

/* Executa a montagem final: ordenacao escolhida, exibicao e busca da chave. */
void executarMontagem(Componente vetor[], int tamanho, int *ordenadoPorNome) {
    int opcao;
    if (tamanho == 0) {
        printf("Cadastre componentes antes de montar a torre.\n");
        return;
    }
    printf("\n1. Bubble Sort por nome\n2. Insertion Sort por tipo\n");
    printf("3. Selection Sort por prioridade\n");
    opcao = lerInteiro("Estrategia: ", 1, 3);
    if (opcao == 1) {
        medirTempo(bubbleSortNome, vetor, tamanho);
        *ordenadoPorNome = 1;
    } else if (opcao == 2) {
        medirTempo(insertionSortTipo, vetor, tamanho);
        *ordenadoPorNome = 0;
    } else {
        medirTempo(selectionSortPrioridade, vetor, tamanho);
        *ordenadoPorNome = 0;
    }
    mostrarComponentes(vetor, tamanho);
}

/* Menu principal do modulo de componentes da torre de resgate. */
int main(void) {
    Componente componentes[MAX_COMPONENTES];
    int tamanho = 0;
    int ordenadoPorNome = 0;
    int opcao;

    do {
        printf("\n===== TORRE DE RESGATE =====\n");
        printf("1. Cadastrar componente\n2. Mostrar componentes\n");
        printf("3. Montar torre com estrategia de ordenacao\n");
        printf("4. Buscar componente-chave\n0. Sair\n");
        opcao = lerInteiro("Escolha: ", 0, 4);
        switch (opcao) {
            case 1:
                cadastrarComponente(componentes, &tamanho, &ordenadoPorNome);
                mostrarComponentes(componentes, tamanho);
                break;
            case 2:
                mostrarComponentes(componentes, tamanho);
                break;
            case 3:
                executarMontagem(componentes, tamanho, &ordenadoPorNome);
                break;
            case 4: {
                char nome[30];
                int indice;
                if (!ordenadoPorNome) {
                    printf("Ordene por nome com Bubble Sort antes da busca binaria.\n");
                    break;
                }
                lerTexto("Nome do componente-chave: ", nome, sizeof(nome));
                indice = buscaBinariaPorNome(componentes, tamanho, nome);
                printf("Comparacoes na busca binaria: %d\n", comparacoesBusca);
                if (indice >= 0) {
                    printf("Componente-chave confirmado para ativar a torre:\n");
                    mostrarComponentes(&componentes[indice], 1);
                } else {
                    printf("Componente-chave nao encontrado.\n");
                }
                break;
            }
            case 0:
                printf("Montagem encerrada.\n");
                break;
        }
    } while (opcao != 0);
    return 0;
}
