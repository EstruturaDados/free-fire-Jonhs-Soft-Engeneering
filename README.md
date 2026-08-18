# 🔫🎒 Desafio Código da Ilha – Edição Free Fire

Bem-vindo ao **Desafio Código da Ilha – Edição Free Fire!**  
Neste desafio, você irá simular o gerenciamento de um **inventário de sobrevivência** em uma ilha misteriosa, utilizando a linguagem **C**.

A empresa **MateCheck** encarregou você de desenvolver o sistema de **mochila virtual** que ajudará os sobreviventes a se prepararem para escapar da ilha.  
O desafio é dividido em três níveis: **Novato**, **Aventureiro** e **Mestre**, cada um com mais complexidade e poder.


## 🎮 Nível Novato: Inventário Básico

### 🚩 Objetivo

Criar um programa em C com as seguintes funcionalidades:

- Adicionar itens à mochila (**nome**, **tipo** e **quantidade**)
- Remover itens pelo nome
- Listar os itens cadastrados

### ⚙️ Funcionalidades

- Utilização de `struct` para representar cada item
- Vetor estático com capacidade para até **10 itens**
- Leitura e escrita via terminal (`scanf`, `printf`)
- Menu interativo com `switch` e `do-while`

### 🧠 Simplicidade

- Sem ordenações, buscas especializadas ou uso de ponteiros
- Ideal para praticar manipulação básica de estruturas e arrays

### 📥 Entrada

O usuário escolhe ações no menu e preenche os dados dos itens conforme solicitado.

### 📤 Saída

O programa exibe os dados organizados em formato de tabela, com nome, tipo e quantidade.



## 🛡️ Nível Aventureiro: Mochila com Busca

### 🆕 Diferenças em relação ao Nível Novato

- Implementação de **busca sequencial** por nome
- Novidade no menu: opção de **"Buscar item por nome"**
- Exibição detalhada do item encontrado

### ⚙️ Funcionalidades

- O usuário pode procurar qualquer item já inserido
- Se encontrado, o programa exibe seus atributos
- Caso contrário, exibe mensagem de erro amigável

### 💡 Conceitos Adicionados

- **Busca sequencial**
- **Comparação de strings** (`strcmp`)
- **Controle com flag** para indicar se item foi encontrado

### 📥 Entrada

O usuário digita o nome do item que deseja buscar.

### 📤 Saída

- Detalhes completos do item (nome, tipo, quantidade)
- Ou uma mensagem de erro, se não for encontrado

---

## 🧠 Nível Mestre: Ordenação e Busca Binária

### 🆕 Diferenças em relação ao Nível Aventureiro

- Adição do campo **prioridade** aos itens (valores de 1 a 5)
- Possibilidade de **ordenar** a mochila por **nome**, **tipo** ou **prioridade**
- Implementação da **busca binária** por nome com verificação de ordenação

### ⚙️ Funcionalidades

- **Menu de ordenação**: o jogador escolhe o critério desejado
- Contador de **comparações na ordenação** para análise de desempenho
- **Busca binária** com validação de pré-requisito (lista deve estar ordenada por nome)

### 💡 Conceitos Adicionados

- **Enumeração** (`enum`) para critérios de ordenação
- **Ordenação com Insertion Sort**
- **Busca binária** (`binary search`)
- Uso de **bool** para controle de estado
- **Análise de desempenho** com contador de comparações

### 📥 Entrada

O usuário:

1. Adiciona itens com prioridade
2. Ordena os itens
3. Realiza busca binária pelo nome do item

### 📤 Saída

- Mochila **ordenada** com base no critério escolhido
- Exibição dos **dados do item buscado** ou mensagem de erro
- **Quantidade de comparações** realizadas durante a ordenação



## 🏁 Conclusão

## Comparação entre vetor e lista encadeada

O arquivo `FreeFire.c` contém duas mochilas independentes para comparação:

- **Vetor:** armazena até 10 itens em posições contíguas. A remoção desloca os itens seguintes, e a busca binária fica disponível depois do Bubble Sort por nome.
- **Lista encadeada:** cria nós dinamicamente com `malloc`. A inserção ocorre no início e a remoção ajusta ponteiros, mas a busca permanece sequencial.

No menu principal, escolha a estrutura desejada. Em cada busca, o programa informa quantas comparações foram realizadas. Assim, é possível inserir dados equivalentes nas duas mochilas e observar o comportamento durante uma busca crítica.

Ao completar qualquer nível do **Desafio Código da Ilha – Edição Free Fire**, você terá avançado significativamente na programação em **C**, desenvolvendo habilidades práticas de:

- Manipulação de **estruturas e arrays**
- Criação de **menus interativos**
- Implementação de **buscas e ordenações**
- **Pensamento modular** e boas práticas de software

Cada nível representa uma missão rumo à **sobrevivência total**.  
Escolha seu nível, prepare sua mochila... e **boa sorte na ilha!** 🏝️💼🔍

> Equipe de Ensino – MateCheck
