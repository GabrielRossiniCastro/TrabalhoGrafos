#ifndef NO_HPP
#define NO_HPP

#include <vector>

using namespace std;

/*
    Classe que representa um vértice do grafo.

    Cada nó possui:
    - um identificador
    - uma lista de adjacência

    A lista de adjacência armazena:
    first  -> vértice vizinho
    second -> peso da aresta
*/

class No
{
public:
    int id;

    vector<pair<int, double>> adjacentes;

    No(int id);
};

#endif