#include "MeuGrafo.hpp"

using namespace std;

/*
    Construtor.

    true  -> orientado
    false -> não orientado
*/

MeuGrafo::MeuGrafo(bool orientado)
{
    this->orientado = orientado;
}

/*
    Destrutor.

    Libera memória dos nós.
*/

MeuGrafo::~MeuGrafo()
{
    for (auto par : nos)
    {
        delete par.second;
    }
}

/*
    Insere um vértice no grafo.
*/

void MeuGrafo::inserirVertice(int v)
{
    // Verifica duplicação
    if (nos.find(v) != nos.end())
    {
        cout << "Vertice "
             << v
             << " ja existe."
             << endl;

        return;
    }

    // Cria novo nó
    nos[v] = new No(v);
}

/*
    Insere uma aresta entre u e v.
*/

void MeuGrafo::inserirAresta(int u,
                             int v,
                             double peso)
{
    // Verifica existência dos vértices
    if (nos.find(u) == nos.end() ||
        nos.find(v) == nos.end())
    {
        cout << "Vertices invalidos."
             << endl;

        return;
    }

    // Evita duplicação
    if (verificarAresta(u, v))
    {
        cout << "Aresta ja existe."
             << endl;

        return;
    }

    /*
        Adiciona v na lista
        de adjacência de u.
    */
    nos[u]->adjacentes.push_back({v, peso});

    /*
        Se não orientado,
        adiciona volta.
    */
    if (!orientado)
    {
        nos[v]->adjacentes.push_back({u, peso});
    }
}

/*
    Verifica se existe aresta.
*/

bool MeuGrafo::verificarAresta(int u, int v)
{
    // Verifica existência
    if (nos.find(u) == nos.end() ||
        nos.find(v) == nos.end())
    {
        return false;
    }

    // Percorre adjacência
    for (auto adj : nos[u]->adjacentes)
    {
        if (adj.first == v)
        {
            return true;
        }
    }

    return false;
}

/*
    Altera peso da aresta.
*/

void MeuGrafo::alterarPesoAresta(int u,
                                 int v,
                                 double peso)
{
    // Verifica existência
    if (!verificarAresta(u, v))
    {
        return;
    }

    // Atualiza u -> v
    for (auto &adj : nos[u]->adjacentes)
    {
        if (adj.first == v)
        {
            adj.second = peso;
        }
    }

    /*
        Se não orientado,
        atualiza v -> u.
    */
    if (!orientado)
    {
        for (auto &adj : nos[v]->adjacentes)
        {
            if (adj.first == u)
            {
                adj.second = peso;
            }
        }
    }
}

/*
    Retorna grau do vértice.
*/

int MeuGrafo::grauVertice(int v)
{
    if (nos.find(v) == nos.end())
    {
        return 0;
    }

    return nos[v]->adjacentes.size();
}

/*
    Lista vizinhos do vértice.
*/

vector<int> MeuGrafo::listarVizinhos(int v)
{
    vector<int> vizinhos;

    if (nos.find(v) == nos.end())
    {
        return vizinhos;
    }

    for (auto adj : nos[v]->adjacentes)
    {
        vizinhos.push_back(adj.first);
    }

    return vizinhos;
}

/*
    Verifica adjacência.
*/

bool MeuGrafo::saoAdjacentes(int u, int v)
{
    return verificarAresta(u, v);
}

/*
    Remove aresta entre u e v.
*/

void MeuGrafo::removerAresta(int u, int v)
{
    // Verifica existência
    if (!verificarAresta(u, v))
    {
        return;
    }

    /*
        Remove v da lista
        de adjacência de u.
    */

    auto &adjU = nos[u]->adjacentes;

    for (auto it = adjU.begin();
         it != adjU.end();
         it++)
    {
        if (it->first == v)
        {
            adjU.erase(it);
            break;
        }
    }

    /*
        Se não orientado,
        remove também u de v.
    */

    if (!orientado)
    {
        auto &adjV = nos[v]->adjacentes;

        for (auto it = adjV.begin();
             it != adjV.end();
             it++)
        {
            if (it->first == u)
            {
                adjV.erase(it);
                break;
            }
        }
    }
}

/*
    Remove vértice do grafo.
*/

void MeuGrafo::removerVertice(int v)
{
    // Verifica existência
    if (nos.find(v) == nos.end())
    {
        return;
    }

    /*
        Remove referências
        ao vértice.
    */

    for (auto &par : nos)
    {
        auto &adj = par.second->adjacentes;

        for (auto it = adj.begin();
             it != adj.end();)
        {
            if (it->first == v)
            {
                it = adj.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    // Libera memória
    delete nos[v];

    // Remove do mapa
    nos.erase(v);
}

/*
    Exibe o grafo.
*/

void MeuGrafo::exibirGrafo()
{
    cout << nos.size() << endl;

    /*
        Percorre todos
        os vértices.
    */

    for (auto par : nos)
    {
        int u = par.first;

        for (auto adj : par.second->adjacentes)
        {
            int v = adj.first;

            double peso = adj.second;

            /*
                Evita duplicação
                em não orientado.
            */

            if (!orientado && u > v)
            {
                continue;
            }

            cout << u
                 << " "
                 << v
                 << " "
                 << peso
                 << endl;
        }
    }
}

/*
    DFS auxiliar.
*/

void MeuGrafo::dfs(int vertice,
                   unordered_set<int> &visitados,
                   vector<int> &componente)
{
    // Marca visitado
    visitados.insert(vertice);

    // Adiciona na componente
    componente.push_back(vertice);

    // Percorre vizinhos
    for (auto adj : nos[vertice]->adjacentes)
    {
        int vizinho = adj.first;

        // Se não visitado
        if (visitados.find(vizinho) == visitados.end())
        {
            dfs(vizinho,
                visitados,
                componente);
        }
    }
}

/*
    Determina componentes conexas.
*/

vector<vector<int>>
MeuGrafo::componentesConexas()
{
    vector<vector<int>> componentes;

    unordered_set<int> visitados;

    /*
        Percorre todos os vértices.
    */

    for (auto par : nos)
    {
        int vertice = par.first;

        /*
            Se não visitado,
            cria nova componente.
        */

        if (visitados.find(vertice) == visitados.end())
        {
            vector<int> componente;

            dfs(vertice,
                visitados,
                componente);

            componentes.push_back(componente);
        }
    }

    return componentes;
}