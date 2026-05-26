#include <iostream>
#include <vector>
#include "Aresta.hpp"

using namespace std;

class No
{
    private:
        int idNo;                   // Identificador do nó
        int valor;                  // Valor associado ao nó
        Aresta* arestas;            // Lista de arestas que incidem sobre o nó
        vector<No*> listaDeNos;     // Lista de nós do grafo
        
    public:
        No(int idNo, int valor);
        ~No();
        void adicionaNoLista(No* no);   // Método para adicionar um nó à lista de nós do grafo, recebendo um ponteiro para o nó como parâmetro
        bool verificaExistenciaNo(int idNo);  // Método para verificar se um nó com o mesmo identificador já existe no grafo, recebendo o identificador do nó como parâmetro, retornando true se um nó de mesmo id já existir no grafo ou false caso contrário
        No* getNo(int idNo);    // Método para buscar um nó no grafo pelo seu identificador, recebendo o identificador do nó como parâmetro, retornando um ponteiro para o nó encontrado ou nullptr se nenhum nó com o identificador especificado for encontrado
};