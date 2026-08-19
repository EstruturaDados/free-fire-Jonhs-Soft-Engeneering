# Torre de Resgate - Free Fire

Modulo final do desafio de Estruturas de Dados para organizar os componentes da torre de resgate.

## Funcionalidades

- Cadastro de ate 20 componentes.
- Campos `nome`, `tipo` e `prioridade` de 1 a 10.
- Bubble Sort por nome.
- Insertion Sort por tipo.
- Selection Sort por prioridade.
- Contagem de comparacoes e medicao com `clock()`.
- Busca binaria pelo nome, liberada somente depois do Bubble Sort.
- Exibicao formatada dos componentes e confirmacao do componente-chave.

## Compilacao e execucao

```bash
gcc -std=c11 -Wall -Wextra -pedantic FreeFire.c -o FreeFire
./FreeFire
```

O programa possui um menu interativo para cadastrar os componentes, escolher a estrategia de montagem, analisar as metricas e localizar o componente-chave.
