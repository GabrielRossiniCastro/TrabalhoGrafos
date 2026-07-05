#include "MeuGrafo.hpp"
#include <iostream>
#include <fstream>
#include <ctime>

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

    // No PCSTP, a função objetivo é:
    // custo das arestas escolhidas + penalidade dos vértices que ficaram fora.
    solucao.valorObjetivo = solucao.custoArestas + solucao.penalidadeNaoColetada;

    return solucao;
}

Solucao MeuGrafo::gerarArvoreGulosa(int raiz)
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
// Executa o algoritmo guloso do problema.
// A ideia é escolher como raiz o vértice com maior prêmio,
// pois ele representa o maior ganho inicial.
Solucao MeuGrafo::algoritmoGulosoPCSTP()
{
    int melhorRaiz = -1;
    float maiorPremio = -1;

    // Percorre todos os vértices do grafo
    for (auto par : nos)
    {
        int idVertice = par.first;
        float premioVertice = getPremio(idVertice);

        // Escolha gulosa: fica com o vértice de maior prêmio
        if (premioVertice > maiorPremio)
        {
            maiorPremio = premioVertice;
            melhorRaiz = idVertice;
        }
    }

    // Caso o grafo esteja vazio
    if (melhorRaiz == -1)
    {
        return Solucao();
    }

    // A partir da raiz escolhida, gera a árvore da solução
    return gerarArvoreGulosa(melhorRaiz);
}


// Imprime no terminal os dados principais da solução encontrada.
void MeuGrafo::imprimirSolucao(const Solucao &solucao)
{
    cout << "\n========== SOLUCAO ENCONTRADA ==========\n";

    cout << "\nVertices selecionados:\n";
    for (int v : solucao.verticesSelecionados)
    {
        cout << v << " ";
    }

    cout << "\n\nArestas selecionadas:\n";
    for (auto aresta : solucao.arestasSelecionadas)
    {
        cout << aresta.first << " " << aresta.second << endl;
    }

    cout << "\nCusto das arestas: " << solucao.custoArestas << endl;
    cout << "Premio total coletado: " << solucao.premioTotal << endl;
    cout << "Penalidade dos vertices fora: " << solucao.penalidadeNaoColetada << endl;
    cout << "Valor objetivo: " << solucao.valorObjetivo << endl;
}

// Salva a solução em formato simples: uma aresta por linha.
void MeuGrafo::salvarSolucao(const Solucao &solucao, string nomeArquivo)
{
    ofstream arquivo(nomeArquivo);

    if (!arquivo.is_open())
    {
        cout << "Erro ao criar o arquivo da solucao." << endl;
        return;
    }

    for (auto aresta : solucao.arestasSelecionadas)
    {
        arquivo << aresta.first << " " << aresta.second << endl;
    }

    arquivo.close();

    cout << "\nArquivo gerado: " << nomeArquivo << endl;
}

// Salva os resultados da execução do algoritmo em um arquivo CSV.
void MeuGrafo::salvarResultadoCSV(string instancia, string algoritmo, double alpha, int iteracoes, int tamanhoBloco,
                                  unsigned int semente, double tempo, float valorSolucao)
{
    // Abre (ou cria) o arquivo CSV em modo de acréscimo.
    ofstream arquivo("resultados.csv", ios::app);

    if (!arquivo.is_open())
    {
        cout << "Erro ao abrir resultados.csv" << endl;
        return;
    }

    // Se o arquivo estiver vazio, escreve o cabeçalho.
    arquivo.seekp(0, ios::end);

    if (arquivo.tellp() == 0)
    {
        arquivo << "DataHora;"
                << "Instancia;"
                << "Algoritmo;"
                << "Alpha;"
                << "Iteracoes;"
                << "Bloco;"
                << "Semente;"
                << "Tempo(s);"
                << "ValorObtido"
                << endl;
    }

    // Obtém a data e hora atual da execução.
    time_t agora = time(nullptr);
    tm *dataHora = localtime(&agora);

    // Escreve a data e hora no formato: dia/mês/ano hora:minuto:segundo
    arquivo << dataHora->tm_mday << "/"
            << dataHora->tm_mon + 1 << "/"
            << dataHora->tm_year + 1900 << " "
            << dataHora->tm_hour << ":"
            << dataHora->tm_min << ":"
            << dataHora->tm_sec << ";";

    // Escreve as informações gerais do teste.
    arquivo << instancia << ";";
    arquivo << algoritmo << ";";

    if (alpha < 0)
        arquivo << "-;";
    else
        arquivo << alpha << ";";

    if (iteracoes < 0)
        arquivo << "-;";
    else
        arquivo << iteracoes << ";";

    if (tamanhoBloco < 0)
        arquivo << "-;";
    else
        arquivo << tamanhoBloco << ";";

    arquivo << semente << ";";
    arquivo << tempo << ";";
    arquivo << valorSolucao << endl;

    arquivo.close();
}

// =========================================================================
// ADICIONADOS: ALGORITMO GULOSO RANDOMIZADO (GRASP)
// =========================================================================

Solucao MeuGrafo::gerarArvoreGulosaRandomizada(int raiz, double alpha, mt19937 &gerador)
{
    Solucao solucaoVazia;
    if(nos.find(raiz) == nos.end()) return solucaoVazia;

    vector<int> verticesSelecionados;
    vector<pair<int, int>> arestasSelecionadas;
    unordered_set<int> naArvore;
    set<pair<int, int>> arestasNaSolucao;

    naArvore.insert(raiz);
    verticesSelecionados.push_back(raiz);

    auto dijkstraLocal = [&](int origem, int destino) -> vector<int> {
        const float INF = 1e9;
        unordered_map<int, float> dist;
        unordered_map<int, int> pai;
        unordered_set<int> visitados;

        for(const auto &par : nos) {
            dist[par.first] = INF;
            pai[par.first] = -1;
        }
        dist[origem] = 0.0f;

        while(true) {
            int atual = -1;
            float melhorDist = INF;
            for(const auto &par : nos) {
                int v = par.first;
                if(!visitados.count(v) && dist[v] < melhorDist) {
                    melhorDist = dist[v];
                    atual = v;
                }
            }
            if(atual == -1 || atual == destino) break;
            visitados.insert(atual);

            for(const auto &adj : nos[atual]->adjacentes) {
                int vizinho = adj.first;
                float peso = adj.second;
                if(dist[atual] + peso < dist[vizinho]) {
                    dist[vizinho] = dist[atual] + peso;
                    pai[vizinho] = atual;
                }
            }
        }
        if(dist[destino] >= INF) return {};
        
        vector<int> caminho;
        int atual = destino;
        while(atual != -1) {
            caminho.push_back(atual);
            atual = pai[atual];
        }
        reverse(caminho.begin(), caminho.end());
        return caminho;
    };

    auto custoCaminho = [&](const vector<int> &caminho) -> float {
        if(caminho.size() <= 1) return 0.0f;
        float custo = 0.0f;
        for(size_t i = 0; i + 1 < caminho.size(); i++) {
            float peso = getPesoAresta(caminho[i], caminho[i + 1]);
            if(peso < 0) return 1e9; 
            custo += peso;
        }
        return custo;
    };

    auto premioNovoCaminho = [&](const vector<int> &caminho, const unordered_set<int> &naArvoreAtual) -> float {
        float premio = 0.0f;
        for(int v : caminho) {
            if(!naArvoreAtual.count(v)) premio += getPremio(v);
        }
        return premio;
    };

    auto melhorCaminhoParaVertice = [&](int destino, const unordered_set<int> &naArvoreAtual) -> Candidato {
        Candidato melhor;
        melhor.verticeDestino = destino;
        melhor.custo = 1e9;
        melhor.ganho = -1e9;

        for(int origem : naArvoreAtual) {
            vector<int> caminho = dijkstraLocal(origem, destino);
            if(caminho.empty()) continue;               

            float custo = custoCaminho(caminho);
            if(custo < melhor.custo) {
                melhor.caminho = caminho;
                melhor.custo = custo;
            }
        }
        if(!melhor.caminho.empty()) {
            melhor.premio = premioNovoCaminho(melhor.caminho, naArvoreAtual);
            melhor.ganho = melhor.premio - melhor.custo;
        }
        return melhor;
    };

    auto adicionarCaminhoNaSolucao = [&](const vector<int> &caminho, unordered_set<int> &naArvoreAtual, vector<int> &verticesSel, vector<pair<int, int>> &arestasSel, set<pair<int, int>> &arestasSet) {
        for(int v : caminho) {
            if(!naArvoreAtual.count(v)) {
                naArvoreAtual.insert(v);
                verticesSel.push_back(v);
            }
        }
        for(size_t i = 0; i + 1 < caminho.size(); i++) {
            int u = caminho[i];
            int v = caminho[i + 1];
            if(u > v) swap(u, v);
            pair<int, int> aresta = {u, v};
            if(!arestasSet.count(aresta)) {
                arestasSet.insert(aresta);
                arestasSel.push_back(aresta);
            }
        }
    };

    // Laço da Construção Randomizada (Uso do alpha e RCL)
    while(true)
    {
        vector<Candidato> listaCandidatos;
        float maxGanho = -1e9;
        float minGanho = 1e9;

        // Avalia todos os vértices fora da árvore
        for(const auto &par : nos)
        {
            int v = par.first;
            if(naArvore.count(v)) continue;

            Candidato cand = melhorCaminhoParaVertice(v, naArvore);

            if(!cand.caminho.empty() && cand.ganho > 0)
            {
                listaCandidatos.push_back(cand);
                if(cand.ganho > maxGanho) maxGanho = cand.ganho;
                if(cand.ganho < minGanho) minGanho = cand.ganho;
            }
        }

        if(listaCandidatos.empty()) break; // Nenhum candidato vantajoso viável

        // Calcula o limite para a Lista Restrita de Candidatos (RCL)
        float limiar = maxGanho - alpha * (maxGanho - minGanho);
        vector<Candidato> rcl;

        for(const auto &cand : listaCandidatos)
        {
            if(cand.ganho >= limiar)
            {
                rcl.push_back(cand);
            }
        }

        // Sorteia um candidato dentro da RCL
        uniform_int_distribution<int> dist(0, rcl.size() - 1);
        Candidato sorteado = rcl[dist(gerador)];

        adicionarCaminhoNaSolucao(sorteado.caminho, naArvore, verticesSelecionados, arestasSelecionadas, arestasNaSolucao);
    }

    return avaliarSolucao(verticesSelecionados, arestasSelecionadas);
}

Solucao MeuGrafo::algoritmoGulosoRandomizadoPCSTP(double alpha, int numIteracoes, unsigned int semente)
{
    Solucao melhorSolucaoGlobal;
    melhorSolucaoGlobal.valorObjetivo = 1e9; 
    
    if (nos.empty()) return melhorSolucaoGlobal;

    mt19937 gerador(semente);

    // RCL para escolha randomizada da Raiz inicial
    vector<pair<int, float>> candidatosRaiz;
    float maxPremio = -1e9;
    float minPremio = 1e9;

    for (auto par : nos) {
        float premio = getPremio(par.first);
        candidatosRaiz.push_back({par.first, premio});
        if (premio > maxPremio) maxPremio = premio;
        if (premio < minPremio) minPremio = premio;
    }

    float limiarRaiz = maxPremio - alpha * (maxPremio - minPremio);
    vector<int> rclRaizes;
    for (auto r : candidatosRaiz) {
        if (r.second >= limiarRaiz) {
            rclRaizes.push_back(r.first);
        }
    }

    // Executa as iterações do GRASP
    for (int i = 0; i < numIteracoes; i++)
    {
        uniform_int_distribution<int> distRaiz(0, rclRaizes.size() - 1);
        int raizSorteada = rclRaizes[distRaiz(gerador)];

        Solucao solAtual = gerarArvoreGulosaRandomizada(raizSorteada, alpha, gerador);

        // Armazena sempre a melhor solução ao longo das iterações
        if (solAtual.valorObjetivo < melhorSolucaoGlobal.valorObjetivo)
        {
            melhorSolucaoGlobal = solAtual;
        }
    }

    return melhorSolucaoGlobal;
}