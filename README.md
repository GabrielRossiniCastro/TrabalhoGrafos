# Trabalho 2 - Teoria dos Grafos

**Tema A:** Problema da Árvore de Steiner com Coleta de Prêmios  
**Disciplina:** DCC059 - Teoria dos Grafos - UFJF

## Integrantes

- Gabriel Rossini Castro - 202165043A
- Luís Otávio Maia Barrientos - 202276009
- Yan Vieira Guimarães - 202235015

## Descrição

O projeto implementa heurísticas para o *Prize-Collecting Steiner Tree Problem in Graphs* (PCSTP), ou Problema da Árvore de Steiner com Coleta de Prêmios.

O problema considera um grafo não direcionado com custos nas arestas e prêmios nos vértices. A função objetivo minimizada é:

```text
valor da solução = custo das arestas selecionadas
                    + penalidade dos vértices não selecionados
```

Foram implementadas três abordagens:

1. algoritmo guloso;
2. algoritmo guloso randomizado;
3. algoritmo guloso randomizado reativo.

## Requisitos

- compilador C++ com suporte a C++11 ou superior;
- GCC/G++ no Linux ou MinGW/MSYS2 no Windows;
- terminal aberto na pasta raiz do projeto.

Os experimentos finais foram compilados com `g++ 16.1.0`, utilizando a opção de otimização `-O2`.

## Arquivos principais

- `main.cpp`: execução demonstrativa dos algoritmos;
- `main_experimentos.cpp`: execução completa dos experimentos;
- `MeuGrafo.cpp` e `MeuGrafo.hpp`: representação do grafo e algoritmos;
- `No.cpp` e `No.hpp`: representação dos vértices;
- `Candidato.hpp`: estrutura auxiliar para candidatos;
- `Solucao.hpp`: estrutura que armazena uma solução;
- `B/`: instâncias utilizadas nos experimentos;
- `DCC059___Relatório/`: fontes LaTeX do relatório.

## Compilação

### Programa demonstrativo

Linux:

```bash
g++ -std=c++11 -O2 main.cpp MeuGrafo.cpp No.cpp -o programa
```

Windows:

```powershell
g++ -std=c++11 -O2 main.cpp MeuGrafo.cpp No.cpp -o programa.exe
```

### Executor dos experimentos

Linux:

```bash
g++ -std=c++11 -O2 main_experimentos.cpp MeuGrafo.cpp No.cpp -o programa_experimentos
```

Windows:

```powershell
g++ -std=c++11 -O2 main_experimentos.cpp MeuGrafo.cpp No.cpp -o programa_experimentos.exe
```

## Execução

### Demonstração

Linux:

```bash
./programa
```

Windows:

```powershell
.\programa.exe
```

### Experimento completo com 20 instâncias

Linux:

```bash
./programa_experimentos
```

Windows:

```powershell
.\programa_experimentos.exe
```

Também é possível executar somente uma instância ou um conjunto filtrado por prefixo:

```powershell
.\programa_experimentos.exe b01
.\programa_experimentos.exe b01,b02,b03
.\programa_experimentos.exe oddcycle3
```

**Atenção:** cada nova execução de `programa_experimentos` recria os arquivos CSV de resultados. Para preservar o experimento completo, faça uma cópia dos CSVs antes de executar apenas um filtro.

## Instâncias

O experimento final utiliza 20 instâncias da SteinLib:

- `b01` a `b18`, pertencentes ao conjunto B, com 50 a 100 vértices;
- `oddcycle3` e `oddwheel3`, pertencentes ao conjunto SP.

Os arquivos necessários estão em:

```text
B/steinb1.txt
...
B/steinb18.txt
B/SP/oddcycle3.stp
B/SP/oddwheel3.stp
```

Os arquivos do conjunto B estão no formato compacto da OR-Library. O executor converte esse formato internamente para STP antes de carregar cada instância. Os arquivos do conjunto SP já utilizam o formato STP.

Para usar as instâncias clássicas de Steiner na implementação do PCSTP, cada terminal recebe prêmio `1000000`, enquanto os demais vértices recebem prêmio zero. Dessa forma, excluir um terminal é sempre desvantajoso e o valor objetivo corresponde ao custo da árvore que conecta os terminais.

## Parâmetros dos experimentos

Cada configuração é executada dez vezes para cada instância, usando uma semente diferente em cada execução.

### Guloso

- uma construção determinística por execução;
- raiz escolhida pelo maior prêmio;
- inclusão do caminho de maior ganho positivo.

### Guloso randomizado

- valores de `alpha`: `0.2`, `0.3` e `0.4`;
- 30 construções por execução;
- retorno da melhor solução encontrada.

O parâmetro `alpha` não define diretamente o tamanho da Lista Restrita de Candidatos (LRC). Ele determina um limiar de qualidade:

```text
limiar = valorMaximo - alpha * (valorMaximo - valorMinimo)
```

Para a escolha da raiz, são utilizados os prêmios mínimo e máximo. Para a escolha dos caminhos, são utilizados os ganhos mínimo e máximo. Entram na LRC todos os candidatos cujo valor seja maior ou igual ao limiar.

### Guloso randomizado reativo

- valores de `alpha`: `0.2`, `0.3` e `0.4`;
- 300 construções por execução;
- blocos de 30 iterações;
- probabilidades inicialmente uniformes;
- atualização das probabilidades ao final de cada bloco.

Como o problema é de minimização, valores de `alpha` associados a menores médias recebem maior probabilidade nas iterações seguintes.

## Sementes

O executor utiliza sementes determinísticas para permitir a reprodução dos resultados. A semente é calculada a partir de uma base igual a `100000`, do índice da instância e do número da execução.

Todas as sementes utilizadas ficam registradas em `resultados_execucoes.csv`. A melhor semente de cada configuração também aparece em `resultados_resumo.csv`.

## Arquivos gerados

O executor dos experimentos produz:

- `resultados_execucoes.csv`: todas as 1.000 execuções;
- `resultados_resumo.csv`: melhor valor, média, tempo e desvios por configuração;
- `tabela_desvio_melhor.csv`: desvio percentual do melhor resultado das dez execuções;
- `tabela_desvio_media.csv`: desvio percentual da média das dez execuções;
- `tabela_tempo_medio.csv`: tempo médio das dez execuções;
- `linhas_latex_relatorio.txt`: linhas formatadas para as tabelas do relatório.

O desvio percentual é calculado por:

```text
desvio = 100 * (valorObtido - melhorConhecido) / melhorConhecido
```

Um desvio igual a zero indica que o algoritmo alcançou o melhor valor conhecido da instância.

## Relatório

O relatório final está disponível em:

```text
DCC059___Relatório/main.tex
DCC059___Relatório/bibliografia.bib
DCC059___Relatório.pdf
```

Para compilar no Overleaf, envie a pasta `DCC059___Relatório` completa. Para compilar localmente, execute PDFLaTeX e BibTeX na seguinte ordem:

```text
PDFLaTeX
BibTeX
PDFLaTeX
PDFLaTeX
```

## Resultados finais resumidos

No experimento com 20 instâncias:

- foram registradas 1.000 execuções;
- o menor desvio médio do melhor resultado foi `0,63%`, com `alpha = 0.4`;
- o menor desvio médio considerando as dez execuções foi `1,30%`, com `alpha = 0.2`;
- o desvio médio do guloso foi `3,14%`.

Os resultados completos e sua análise estão apresentados no relatório.
