#ifndef SOLUCAO_HPP
#define SOLUCAO_HPP

#include <iostream>
#include <vector>

using namespace std;

struct Solucao
{
    vector<int> verticesSelecionados;
    vector<pair<int, int>> arestasSelecionadas;

    float custoArestas;
    float premioTotal;
    float penalidadeNaoColetada;
    float valorObjetivo;
};

#endif