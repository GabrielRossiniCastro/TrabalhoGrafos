TRABALHO 2 - TEORIA DOS GRAFOS
TEMA A - Problema da Arvore de Steiner com Coleta de Premios

INSTRUCOES DE COMPILACAO E EXECUCAO

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

COMPILACAO

Linux:

g++ main.cpp MeuGrafo.cpp No.cpp -o programa

Windows:

g++ main.cpp MeuGrafo.cpp No.cpp -o programa.exe

==================================================

EXECUCAO

Linux:

./programa

Windows:

.\programa.exe

==================================================

DESCRICAO DO PROJETO

Este projeto implementa heuristicas para o problema
Prize-Collecting Steiner Tree Problem in Graphs (PCSTP), tambem conhecido
como Problema da Arvore de Steiner com Coleta de Premios.

O problema consiste em encontrar uma arvore em um grafo nao direcionado,
considerando:

- peso nas arestas;
- premio nos vertices;
- penalidade para vertices que nao entram na solucao.

A funcao objetivo utilizada e:

valor da solucao = custo das arestas escolhidas + penalidade dos vertices fora da solucao

Quanto menor o valor da solucao, melhor e o resultado encontrado.

==================================================

LEITURA DE ARQUIVOS

O programa possui leitura de instancias por arquivo.

Atualmente, a funcao de leitura aceita dois tipos de entrada:

1) Formato simples utilizado nos testes

Exemplo:

5 5
1 10
2 8
3 5
4 15
5 3
1 2 2
2 3 3
3 4 1
1 4 7
4 5 10

Onde:

- a primeira linha contem a quantidade de vertices e arestas;
- em seguida, cada linha contem: id_do_vertice premio;
- depois, cada linha contem: origem destino peso.

2) Formato baseado em .stp

A leitura tambem reconhece palavras comuns de instancias .stp, como:

- Nodes
- E
- A
- TP
- T
- NW
- NodeWeight
- Prize

Exemplo:

SECTION Graph
Nodes 5
Edges 5
E 1 2 2
E 2 3 3
E 3 4 1
E 1 4 7
E 4 5 10
END

SECTION Terminals
TP 1 10
TP 2 8
TP 3 5
TP 4 15
TP 5 3
END

EOF

Observacao:
Como existem variacoes no formato .stp, a leitura foi feita de forma
flexivel para reconhecer os principais padroes encontrados em instancias
de problemas de Steiner e PCSTP.

==================================================

ALGORITMO GULOSO

O algoritmo guloso implementado escolhe inicialmente o vertice de maior
premio como raiz da solucao.

A partir dessa raiz, a arvore e construida de forma incremental. A cada
passo, o algoritmo avalia vertices fora da arvore e calcula o menor
caminho ate a solucao parcial. Em seguida, calcula o ganho:

ganho = premio dos novos vertices - custo do caminho

O caminho com maior ganho positivo e adicionado a solucao. O processo
termina quando nao existe mais nenhum candidato com ganho positivo.

Ao final, o programa calcula:

- vertices selecionados;
- arestas selecionadas;
- custo total das arestas;
- premio total coletado;
- penalidade dos vertices fora;
- valor objetivo da solucao.

==================================================

ALGORITMO GULOSO RANDOMIZADO

O algoritmo guloso randomizado utiliza a mesma ideia do algoritmo guloso,
mas nao escolhe necessariamente sempre o melhor candidato.

Ele utiliza o parametro alpha para montar uma Lista Restrita de Candidatos
(RCL). Essa lista contem candidatos considerados bons de acordo com o
ganho calculado.

Depois, um candidato e sorteado dentro da RCL.

Parametros utilizados:

- alpha: controla o tamanho/criterio da lista restrita de candidatos;
- numero de iteracoes: quantidade de solucoes construidas;
- semente: permite repetir os mesmos sorteios.

Ao final das iteracoes, o algoritmo retorna a melhor solucao encontrada.

==================================================

ALGORITMO GULOSO RANDOMIZADO REATIVO

O algoritmo guloso randomizado reativo tambem utiliza uma lista de valores
possiveis para alpha.

Inicialmente, todos os valores de alpha possuem a mesma probabilidade de
serem escolhidos. Durante a execucao, o algoritmo observa quais valores
de alpha estao gerando melhores solucoes.

A cada bloco de iteracoes, as probabilidades sao atualizadas:

- alphas que geraram solucoes melhores passam a ter maior chance de escolha;
- alphas que geraram solucoes piores passam a ter menor chance de escolha.

Parametros utilizados:

- lista de valores de alpha;
- numero de iteracoes;
- tamanho do bloco;
- semente de randomizacao.

Esse metodo torna o algoritmo adaptativo, pois ele ajusta automaticamente
a escolha dos valores de alpha durante a execucao.

==================================================

SEMENTE DE RANDOMIZACAO

A semente de randomizacao e gerada uma unica vez no inicio da execucao,
com base na data/hora atual.

Ela e impressa no terminal e tambem salva no arquivo resultados.csv.

Isso permite repetir um teste especifico, caso seja necessario.

==================================================

SAIDAS GERADAS

Ao executar o programa, sao gerados arquivos de solucao e um arquivo CSV
com os resultados dos testes.

1) Arquivos de solucao

Exemplos:

- solucao_guloso.txt
- solucao_randomizado.txt
- solucao_reativo.txt

Cada arquivo contem as arestas da solucao encontrada, uma por linha, no
formato:

origem destino

Exemplo:

1 2
2 3
3 4

Esse formato facilita copiar e colar a solucao em ferramentas de
visualizacao de grafos, como o Graph Editor do CS Academy.

2) resultados.csv

Contem os dados da execucao dos algoritmos, com informacoes como:

- data e hora do teste;
- instancia;
- algoritmo executado;
- valor de alpha;
- numero de iteracoes;
- tamanho do bloco;
- semente de randomizacao;
- tempo de execucao;
- valor objetivo da solucao.

No algoritmo guloso simples, os campos alpha, iteracoes e bloco sao
preenchidos com "-", pois esses parametros sao utilizados apenas nos
algoritmos randomizados.

==================================================

EXEMPLO DE SAIDA NO TERMINAL

Semente utilizada: 1783259625

Instancia carregada com sucesso.

===== TESTE DO ALGORITMO GULOSO =====

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

Arquivo gerado: solucao_guloso.txt

===== TESTE DO ALGORITMO GULOSO RANDOMIZADO =====

Arquivo gerado: solucao_randomizado.txt

===== TESTE DO GULOSO RANDOMIZADO REATIVO =====

Arquivo gerado: solucao_reativo.txt

Resultado salvo em resultados.csv

==================================================

OBSERVACOES

O main.cpp atual cria uma instancia de teste em arquivo para validar:

- leitura de arquivo;
- algoritmo guloso;
- algoritmo guloso randomizado;
- algoritmo guloso randomizado reativo;
- impressao da solucao;
- geracao dos arquivos de solucao;
- registro dos resultados em CSV.

Para testar outras instancias, basta alterar o arquivo de entrada carregado
pela funcao lerArquivo.