#ifndef MEUGRAFO_HPP
#define MEUGRAFO_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "No.hpp"

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
    void inserirVertice(int v);

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
};

#endif