#include "No.hpp"

No::No(int idNo, int valor)
{   
    if(!verificaExistenciaNo(idNo))   // Verifica se um nó com o mesmo identificador já existe no grafo, utilizando o método 'verificaExistenciaNo' da classe 'No'
    {
        this->idNo = idNo;              // Atribui o valor do parâmetro 'idNo' ao membro 'idNo' da classe
        this->valor = valor;        // Atribui o valor do parâmetro 'valor' ao membro 'valor' da classe
        this->arestas = nullptr;    // Inicializa a lista de arestas como vazia
        adicionaNoLista(this);      // Adiciona o nó à lista de nós do grafo, utilizando o identificador do nó
    }
}

No::~No()
{
    delete[] arestas;   // Libera a memória alocada para a lista de arestas
};

void No::adicionaNoLista(No* no)
{
    listaDeNos.push_back(no);  // Adiciona o nó à lista de nós do grafo
};

bool No::verificaExistenciaNo(int idNo)
{
    for(No* no : listaDeNos)   // Itera sobre a lista de nós do grafo
    {
        if(no->idNo == idNo)       // Verifica se o identificador do nó é igual ao parâmetro 'idNo'
        {
            cout << "Um nó com ID " << idNo << " já existe no grafo, portanto, este novo nó não pode ser adicionado." << endl;  // Imprime mensagem indicando que um nó de mesmo id já existe
            return true;       // Retorna true após encontrar um nó de mesmo id, indicando que o nó já existe no grafo
        }
    }
    return false;             // Retorna false se o nó não for encontrado
};

No* No::getNo(int idNo)
{
    for(No* no : listaDeNos)   // Itera sobre a lista de nós do grafo
    {
        if(no->idNo == idNo)       // Verifica se o identificador do nó é igual ao parâmetro 'idNo'
        {
            return no;          // Retorna o ponteiro para o nó encontrado
        }
    }

    cout << "Nenhum nó com ID " << idNo << " foi encontrado no grafo." << endl;  // Imprime mensagem indicando que nenhum nó com o id especificado foi encontrado

    return nullptr;             // Retorna nullptr se nenhum nó com o identificador especificado for encontrado
};