#include <iostream>
#include "No.hpp"

using namespace std;

class Aresta
{
    private:
        int idAresta;     // Identificador da aresta
        No* no1;          // Ponteiro para o nó de origem da aresta, se o grafo for direcionado, ou para um dos nós, se o grafo for não direcionado
        No* no2;          // Ponteiro para o nó de destino da aresta, se o grafo for direcionado, ou para o outro nó, se o grafo for não direcionado
        vector<Aresta*> listaDeArestas;    // Lista de arestas do grafo
        
    public:
        Aresta(int idNo1, int idNo2, int idAresta);
        ~Aresta();
        void adicionaArestaLista(Aresta* aresta); // Método para adicionar uma aresta à lista de arestas do grafo, recebendo um ponteiro para a aresta como parâmetro
        No* getNo1();   // Método para obter o ponteiro para o nó de origem da aresta, se o grafo for direcionado, ou para um dos nós, se o grafo for não direcionado
        No* getNo2();   // Método para obter o ponteiro para o nó de destino da aresta, se o grafo for direcionado, ou para o outro nó, se o grafo for não direcionado
        bool verificaExistenciaAresta(int idAresta);    // Método para verificar se uma aresta com o mesmo identificador já existe no grafo, recebendo o identificador da aresta como parâmetro, retornando true se uma aresta de mesmo id já existir no grafo ou false caso contrário
        Aresta* getAresta(int idAresta);    // Método para buscar uma aresta no grafo pelo seu identificador, recebendo o identificador da aresta como parâmetro, retornando um ponteiro para a aresta encontrada ou nullptr se nenhuma aresta com o identificador especificado for encontrada
};