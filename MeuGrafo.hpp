#ifndef MEUGRAFO_HPP
#define MEUGRAFO_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <set>

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
    - executar algoritmo de componentes conexas
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

    /*
        DFS auxiliar utilizada
        em componentes conexas.
    */
    void dfs(int vertice,
             unordered_set<int> &visitados,
             vector<int> &componente);

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

    // Algoritmo do grupo
    vector<vector<int>> componentesConexas();

    //------------------------------------------------------------------------------------------------------

    float getPesoAresta(int u, int v);

    float getPremio(int v);
    void setPremio(int v, float premio);

    float calcularCustoArestas(const vector<pair<int,int>>& arestas);
    float calcularPenalidadeFora(const vector<int>& verticesSelecionados);
    Solucao avaliarSolucao(const vector<int>& verticesSelecionados,
                           const vector<pair<int,int>>& arestasSelecionadas);

    Solucao arvoreSteinerColetaPremios(int raiz);
    Solucao arvoreSteinerColetaPremiosHeuristica(int raiz);

    vector<int> dijkstraCaminho(int origem, int destino);
    float dijkstraCusto(int origem, int destino);
    vector<pair<int,int>> caminhoParaArestas(const vector<int>& caminho);
};

#endif