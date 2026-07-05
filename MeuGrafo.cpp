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

void MeuGrafo::inserirVertice(int v, float premio)
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
    nos[v] = new No(v, premio);
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

//------------------------------------------------------------------------------------------------------

float MeuGrafo::getPesoAresta(int u, int v)
{
    if (nos.find(u) == nos.end())
        return -1;

    for (auto adj : nos[u]->adjacentes)
    {
        if (adj.first == v)
            return adj.second;
    }

    return -1;
}

float MeuGrafo::getPremio(int v)
{
    if (nos.find(v) == nos.end())
        return 0.0;

    return nos[v]->premio;
}

void MeuGrafo::setPremio(int v, float premio)
{
    if (nos.find(v) == nos.end())
        return;

    nos[v]->premio = premio;
}

float MeuGrafo::calcularCustoArestas(const vector<pair<int, int>> &arestas)
{
    float custoTotal = 0.0;

    for(const auto &aresta : arestas)
    {
        int u = aresta.first;
        int v = aresta.second;

        float peso = getPesoAresta(u, v);
        if(peso >= 0)
        {
            custoTotal += peso;
        }
    }

    return custoTotal;
}

float MeuGrafo::calcularPenalidadeFora(const vector<int> &verticesSelecionados)
{
    float penalidadeTotal = 0.0;

    for(const auto &par : nos)
    {
        int v = par.first;

        if(find(verticesSelecionados.begin(), verticesSelecionados.end(), v) == verticesSelecionados.end())
        {
            penalidadeTotal += getPremio(v);
        }
    }

    return penalidadeTotal;
}

Solucao MeuGrafo::avaliarSolucao(const vector<int> &verticesSelecionados, const vector<pair<int, int>> &arestasSelecionadas)
{
    Solucao solucao;

    solucao.verticesSelecionados = verticesSelecionados;
    solucao.arestasSelecionadas = arestasSelecionadas;

    solucao.custoArestas = calcularCustoArestas(arestasSelecionadas);
    solucao.premioTotal = 0.0;

    for(const auto &v : verticesSelecionados)
    {
        solucao.premioTotal += getPremio(v);
    }

    solucao.penalidadeNaoColetada = calcularPenalidadeFora(verticesSelecionados);

    solucao.valorObjetivo = solucao.custoArestas - solucao.premioTotal   + solucao.penalidadeNaoColetada;

    return solucao;
}

Solucao MeuGrafo::arvoreSteinerColetaPremiosHeuristica(int raiz)
{
    Solucao solucaoVazia;

    if(nos.find(raiz) == nos.end())
    {
        return solucaoVazia;
    }

    vector<int> verticesSelecionados;
    vector<pair<int, int>> arestasSelecionadas;

    unordered_set<int> naArvore;
    naArvore.insert(raiz);
    verticesSelecionados.push_back(raiz);

    // evita duplicar arestas na solução
    set<pair<int, int>> arestasNaSolucao;

    /*
        Dijkstra local:
        retorna o menor caminho entre origem e destino
        como vetor de vértices.
    */

    auto dijkstraLocal = [&](int origem, int destino) -> vector<int>
    {
        const float INF = 1e9;

        unordered_map<int, float> dist;
        unordered_map<int, int> pai;
        unordered_set<int> visitados;

        for(const auto &par : nos)
        {
            dist[par.first] = INF;
            pai[par.first] = -1;
        }

        dist[origem] = 0.0f;

        while(true)
        {
            int atual = -1;
            float melhorDist = INF;

            // escolhe vértice não visitado com menor distância
            for(const auto &par : nos)
            {
                int v = par.first;
                if(!visitados.count(v) && dist[v] < melhorDist)
                {
                    melhorDist = dist[v];
                    atual = v;
                }
            }

            if(atual == -1)
            {
                break;
            }

            if(atual == destino)
            {
                break;
            }

            visitados.insert(atual);

            for(const auto &adj : nos[atual]->adjacentes)
            {
                int vizinho = adj.first;
                float peso = adj.second;

                if(dist[atual] + peso < dist[vizinho])
                {
                    dist[vizinho] = dist[atual] + peso;
                    pai[vizinho] = atual;
                }
            }
        }

        if(dist[destino] >= INF)
        {
            return {};
        }
        
        vector<int> caminho;
        int atual = destino;

        while(atual != -1)
        {
            caminho.push_back(atual);
            atual = pai[atual];
        }

        reverse(caminho.begin(), caminho.end());
        return caminho;
    };

    /*
        Soma o custo das arestas de um caminho.
        caminho = [v0, v1, v2, ...]
    */
    auto custoCaminho = [&](const vector<int> &caminho) -> float
    {
        if(caminho.size() <= 1)
        {
            return 0.0f;
        }

        float custo = 0.0f;

        for(size_t i = 0; i + 1 < caminho.size(); i++)
        {
            float peso = getPesoAresta(caminho[i], caminho[i + 1]);
            
            if(peso < 0)
            {
                return 1e9; // caminho inválido
            }

            custo += peso;
        }

        return custo;
    };

    /*
        Soma apenas os prêmios dos vértices do caminho
        que ainda não estão na árvore.
    */

    auto premioNovoCaminho = [&](const vector<int> &caminho, const unordered_set<int> &naArvoreAtual) -> float
    {
        float premio = 0.0f;

        for(int v : caminho)
        {
            if(!naArvoreAtual.count(v))
            {
                premio += getPremio(v);
            }
        }

        return premio;
    };

    /*
        Para um destino fora da árvore:
        testa todos os vértices já na árvore como origem
        e pega o caminho de menor custo até o destino.
        Depois calcula o ganho desse caminho.
    */

    auto melhorCaminhoParaVertice = [&](int destino, const unordered_set<int> &naArvoreAtual) -> Candidato
    {
        Candidato melhor;
        melhor.verticeDestino = destino;
        melhor.custo = 1e9;
        melhor.ganho = -1e9;

        for(int origem : naArvoreAtual)
        {
            vector<int> caminho = dijkstraLocal(origem, destino);

            if(caminho.empty())
            {
                continue;               
            }

            float custo = custoCaminho(caminho);

            if(custo < melhor.custo)
            {
                melhor.caminho = caminho;
                melhor.custo = custo;
            }
        }

        if(!melhor.caminho.empty())
        {
            melhor.premio = premioNovoCaminho(melhor.caminho, naArvoreAtual);
            melhor.ganho = melhor.premio - melhor.custo;
        }

        return melhor;
    };

    /*
        Adiciona um caminho escolhido à solução:
        - insere vértices novos
        - insere arestas novas
    */

    auto adicionarCaminhoNaSolucao = [&](const vector<int> &caminho, unordered_set<int> &naArvoreAtual, vector<int> &verticesSel, vector<pair<int, int>> &arestasSel, set<pair<int, int>> &arestasSet)
    {
        // adiciona vértices novos
        for(int v : caminho)
        {
            if(!naArvoreAtual.count(v))
            {
                naArvoreAtual.insert(v);
                verticesSel.push_back(v);
            }
        }

        // adiciona arestas do caminho sem duplicar
        for(size_t i = 0; i + 1 < caminho.size(); i++)
        {
            int u = caminho[i];
            int v = caminho[i + 1];

            // normaliza aresta para grafo não orientado
            if(u > v)
            {
                swap(u, v);
            }

            pair<int, int> aresta = {u, v};

            if(!arestasSet.count(aresta))
            {
                arestasSet.insert(aresta);
                arestasSel.push_back(aresta);
            }
        }
    };

    while(true)
    {
        Candidato melhorCandidato;
        melhorCandidato.ganho = -1e9;

        // testa todos os vértices fora da árvore
        for(const auto &par : nos)
        {
            int v = par.first;

            if(naArvore.count(v))
            {
                continue;
            }

            Candidato cand = melhorCaminhoParaVertice(v, naArvore);

            if(!cand.caminho.empty() && cand.ganho > melhorCandidato.ganho)
            {
                melhorCandidato = cand;
            }
        }

        // se não existe candidato viável ou o melhor ganho não compensa, para
        if(melhorCandidato.caminho.empty() || melhorCandidato.ganho <= 0)
        {
            break;
        }

        adicionarCaminhoNaSolucao(melhorCandidato.caminho, naArvore, verticesSelecionados, arestasSelecionadas, arestasNaSolucao);
    }

    return avaliarSolucao(verticesSelecionados, arestasSelecionadas);
}