#ifndef MEUGRAFO_HPP
#define MEUGRAFO_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <set>
#include <fstream>

#include "No.hpp"
#include "Solucao.hpp"
#include "Candidato.hpp"

using namespace std;

/*
    Classe principal do TAD Grafo.

    Responsável por:
    - armazenar vértices
    - armazenar adjacências
    - realizar operações obrigatórias
*/

class MeuGrafo
{
private:
    // Define se o grafo é orientado
    bool orientado;

    /*
        Estrutura principal do grafo.

        chave -> id do vértice
        valor -> ponteiro para o nó
    */
    unordered_map<int, No *> nos;


public:
    MeuGrafo(bool orientado);

    ~MeuGrafo();

    // Operações obrigatórias
    void inserirVertice(int v, float premio);

    void inserirAresta(int u,
                       int v,
                       double peso = 1.0);

    bool verificarAresta(int u, int v);

    void alterarPesoAresta(int u,
                           int v,
                           double peso);

    int grauVertice(int v);

    vector<int> listarVizinhos(int v);

    bool saoAdjacentes(int u, int v);

    void removerAresta(int u, int v);

    void removerVertice(int v);

    void exibirGrafo();

    float getPesoAresta(int u, int v);

    float getPremio(int v);
    void setPremio(int v, float premio);

    float calcularCustoArestas(const vector<pair<int,int>>& arestas);
    float calcularPenalidadeFora(const vector<int>& verticesSelecionados);
    Solucao avaliarSolucao(const vector<int>& verticesSelecionados,
                           const vector<pair<int,int>>& arestasSelecionadas);

    Solucao algoritmoGuloso(int raiz);
    Solucao gerarArvoreGulosa(int raiz);

    vector<int> dijkstraCaminho(int origem, int destino);
    float dijkstraCusto(int origem, int destino);
    vector<pair<int,int>> caminhoParaArestas(const vector<int>& caminho);

    // Algoritmo do grupo - Tema A
            
    //------------------------------------------------------------------------------------------------------
    // Algoritmo guloso para o PCSTP
    Solucao algoritmoGulosoPCSTP();

    // Exibe a solução encontrada no terminal
    void imprimirSolucao(const Solucao &solucao);

    // Salva a solução em arquivo texto para visualização
    void salvarSolucao(const Solucao &solucao, string nomeArquivo);

    // Salva os resultados da execução do algoritmo em um arquivo CSV.
    void salvarResultadoCSV(string instancia, string algoritmo, double alpha, int iteracoes, int tamanhoBloco, 
        unsigned int semente, double tempo, float valorSolucao);
};

#endif