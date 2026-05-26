#include "Grafo.hpp"

Grafo::Grafo()
{
    // Construtor da classe Grafo
};

Grafo::~Grafo()
{
    // Destrutor da classe Grafo
}

void Grafo::adicionarNo(int id, int valor)
{
    No* no = new No(id, valor);  // Cria um novo nó com o identificador e valor especificados
    this->no = no;  // Atribui o ponteiro para o nó do grafo
};

void Grafo::adicionarAresta(Aresta* aresta, int idNo1, int idNo2)
{
    aresta = new Aresta(idNo1, idNo2);  // Cria uma nova aresta com os identificadores dos nós de origem e destino
    this->aresta = aresta;  // Atribui o ponteiro para a aresta do grafo
};

No* Grafo::getNo()
{
    return no;    // Retorna o ponteiro para o nó do grafo
};

Aresta* Grafo::getAresta()
{
    return aresta;    // Retorna o ponteiro para a aresta do grafo
};

No* Grafo::buscaNo(int idNo)
{
    return no->getNo(idNo);  // Utiliza o método 'getNo' da classe 'No' para buscar um nó no grafo pelo seu identificador, retornando o ponteiro para o nó encontrado ou nullptr se nenhum nó com o identificador especificado for encontrado
};

Aresta* Grafo::buscaAresta(int idAresta)
{
    return aresta->getAresta(idAresta);  // Utiliza o método 'getAresta' da classe 'Aresta' para buscar uma aresta no grafo pelo seu identificador, retornando o ponteiro para a aresta encontrada ou nullptr se nenhuma aresta com o identificador especificado for encontrada
};