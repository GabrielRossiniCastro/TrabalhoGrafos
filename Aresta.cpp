#include "Aresta.hpp"

Aresta::Aresta(int idNo1, int idNo2, int idAresta)
{
    if(!verificaExistenciaAresta(idAresta))   // Verifica se uma aresta com o mesmo identificador já existe no grafo, utilizando o método 'verificaExistenciaAresta' da classe 'Aresta'
    {
        this->getNo1() = idNo1;    // Atribui o valor do parâmetro 'idNo1' ao membro 'no1' da classe, utilizando o método 'getNo1' para acessar o ponteiro para o nó de origem da aresta, ou para um dos nós, se o grafo for não direcionado
        this->getNo2() = idNo2;    // Atribui o valor do parâmetro 'idNo2' ao membro 'no2' da classe, utilizando o método 'getNo2' para acessar o ponteiro para o nó de destino da aresta, ou para o outro nó, se o grafo for não direcionado
        this->idAresta = idAresta;  // Atribui o valor do parâmetro 'idAresta' ao membro 'idAresta' da classe
        adicionaArestaLista(this);  // Adiciona a aresta à lista de arestas do grafo, utilizando o identificador da aresta
    }
};

Aresta::~Aresta()
{
    //Destrutor vazio
};

void Aresta::adicionaArestaLista(Aresta* aresta)
{
    listaDeArestas.push_back(aresta);  // Adiciona a aresta à lista de arestas do grafo
};

No* Aresta::getNo1()
{
    return no1;    // Retorna o ponteiro para o nó de origem da aresta, se o grafo for direcionado, ou para um dos nós, se o grafo for não direcionado
};

No* Aresta::getNo2()
{
    return no2;    // Retorna o ponteiro para o nó de destino da aresta, se o grafo for direcionado, ou para o outro nó, se o grafo for não direcionado
};

bool Aresta::verificaExistenciaAresta(int idAresta)
{
    for(Aresta* aresta : listaDeArestas)   // Itera sobre a lista de arestas do grafo
    {
        if(aresta->idAresta == idAresta)       // Verifica se o identificador da aresta é igual ao parâmetro 'idAresta'
        {
            cout << "Uma aresta com ID " << idAresta << " já existe no grafo, portanto, esta nova aresta não pode ser adicionada." << endl;  // Imprime mensagem indicando que uma aresta de mesmo id já existe
            return true;       // Retorna true após encontrar uma aresta de mesmo id, indicando que a aresta já existe no grafo
        }
    }
    return false;             // Retorna false se a aresta não for encontrada
};

Aresta* Aresta::getAresta(int idAresta)
{
    for(Aresta* aresta : listaDeArestas)   // Itera sobre a lista de arestas do grafo
    {
        if(aresta->idAresta == idAresta)       // Verifica se o identificador da aresta é igual ao parâmetro 'idAresta'
        {
            return aresta;      // Retorna o ponteiro para a aresta encontrada
        }
    }

    cout << "Nenhuma aresta com os nós de origem " << idNo1 << " e destino " << idNo2 << " foi encontrada no grafo." << endl;  // Imprime mensagem indicando que nenhuma aresta com os identificadores dos nós de origem e destino especificados foi encontrada

    return nullptr;     // Retorna nullptr se nenhuma aresta com os identificadores dos nós de origem e destino especificados for encontrada
};