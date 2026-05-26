#include <iostream>
#include "No.hpp"
#include "Aresta.hpp"

using namespace std;

class Grafo
{
    private:
        No* no;          // Ponteiro para o nó do grafo
        Aresta* aresta;  // Ponteiro para a aresta do grafo
        
    public:
        Grafo();
        ~Grafo();
        void adicionarNo(int id, int valor);    // Método para adicionar um nó ao grafo, recebendo o identificador e valor do nó como parâmetros
        void adicionarAresta(Aresta* aresta, int idNo1, int idNo2);   // Método para adicionar uma aresta ao grafo, recebendo um ponteiro para a aresta e os identificadores dos nós de origem e destino como parâmetros, se o grafo for direcionado, ou os identificadores dos dois nós, se o grafo for não direcionado
        No* getNo();    // Método para obter o ponteiro para o nó do grafo
        Aresta* getAresta();    // Método para obter o ponteiro para a aresta do grafo
        No* buscaNo(int idNo);    // Método para buscar um nó no grafo pelo seu identificador
        Aresta* buscaAresta(int idAresta);    // Método para buscar uma aresta no grafo pelo seu identificador
};