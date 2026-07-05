TRABALHO 2 - TEORIA DOS GRAFOS
TEMA A - Problema da Árvore de Steiner com Coleta de Prêmios

INSTRUÇÕES DE COMPILAÇÃO E EXECUÇÃO

==================================================

REQUISITOS:

- Compilador C++ com suporte a C++11 ou superior
- g++ instalado
- No Windows: MinGW/MSYS2
- No Linux: GCC/G++

==================================================

ARQUIVOS PRINCIPAIS DO PROJETO:

- main.cpp
- MeuGrafo.cpp
- MeuGrafo.hpp
- No.cpp
- No.hpp
- Solucao.hpp
- Candidato.hpp

==================================================

COMPILAÇÃO

Linux:

g++ main.cpp MeuGrafo.cpp No.cpp -o programa

Windows:

g++ main.cpp MeuGrafo.cpp No.cpp -o programa.exe

==================================================

EXECUÇÃO

Linux:

./programa

Windows:

.\programa.exe

==================================================

DESCRIÇÃO DO PROJETO

Este projeto implementa uma solução heurística para o problema
Problema da Árvore de Steiner com Coleta de Prêmios (PCSTP).

O problema consiste em encontrar uma árvore em um grafo não direcionado,
considerando:

- peso nas arestas;
- prêmio nos vértices;
- penalidade para vértices que não entram na solução.

A função objetivo utilizada é:

valor da solução = custo das arestas escolhidas + penalidade dos vértices fora da solução

Quanto menor o valor da solução, melhor é o resultado encontrado.

==================================================

ALGORITMO GULOSO

O algoritmo guloso implementado escolhe inicialmente o vértice de maior
prêmio como raiz da solução.

A partir desse vértice, a solução é construída de forma incremental,
adicionando caminhos e vértices considerados vantajosos de acordo com
a heurística implementada.

Ao final, o programa calcula:

- vértices selecionados;
- arestas selecionadas;
- custo total das arestas;
- prêmio total coletado;
- penalidade dos vértices fora;
- valor objetivo da solução.

==================================================

SAÍDAS GERADAS

Ao executar o programa, são gerados dois arquivos:

1) solucao.txt

Contém as arestas da solução encontrada, uma por linha, no formato:

origem destino

Exemplo:

1 2
2 3
3 4

Esse formato facilita copiar e colar a solução em ferramentas de
visualização de grafos, como o Graph Editor do CS Academy.

2) resultados.csv

Contém os dados da execução do algoritmo, com informações como:

- data e hora do teste;
- instância;
- algoritmo executado;
- valor de alpha;
- número de iterações;
- tamanho do bloco;
- semente de randomização;
- tempo de execução;
- valor objetivo da solução.

No algoritmo guloso simples, os campos alpha, iterações e bloco são
preenchidos com "-", pois esses parâmetros são utilizados apenas nos
algoritmos guloso randomizado e guloso randomizado reativo.

==================================================

EXEMPLO DE SAÍDA NO TERMINAL

========== SOLUCAO ENCONTRADA ==========

Vertices selecionados:
4 3 2 1

Arestas selecionadas:
3 4
2 3
1 2

Custo das arestas: 6
Premio total coletado: 38
Penalidade dos vertices fora: 3
Valor objetivo: 9

Arquivo gerado: solucao.txt
Resultado salvo em resultados.csv

==================================================