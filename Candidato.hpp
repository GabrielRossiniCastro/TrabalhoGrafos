#ifndef CANDIDATO_HPP
#define CANDIDATO_HPP

#include <iostream>
#include <vector>

using namespace std;

struct Candidato
{
    int verticeDestino = -1;
    vector<int> caminho;
    float custo = 0.0;
    float premio = 0.0;
    float ganho = 0.0;
};

#endif