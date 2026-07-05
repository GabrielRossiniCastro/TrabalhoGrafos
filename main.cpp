#include <iostream>
#include <chrono>
#include <ctime>

#include "MeuGrafo.hpp"

using namespace std;
using namespace chrono;

int main()
{
    MeuGrafo grafo(false);

    // -------------------------
    // Vértices (id, prêmio)
    // -------------------------

    grafo.inserirVertice(1, 10);
    grafo.inserirVertice(2, 8);
    grafo.inserirVertice(3, 5);
    grafo.inserirVertice(4, 15);
    grafo.inserirVertice(5, 3);

    // -------------------------
    // Arestas (origem, destino, peso)
    // -------------------------

    grafo.inserirAresta(1,2,2);
    grafo.inserirAresta(2,3,3);
    grafo.inserirAresta(3,4,1);
    grafo.inserirAresta(1,4,7);
    grafo.inserirAresta(4,5,10);

    unsigned int semente = time(nullptr);

    srand(semente);

    auto inicio = high_resolution_clock::now();

    Solucao solucao = grafo.algoritmoGulosoPCSTP();

    auto fim = high_resolution_clock::now();

    duration<double> tempo = fim - inicio;

    grafo.imprimirSolucao(solucao);

    grafo.salvarSolucao(solucao, "solucao.txt");

    grafo.salvarResultadoCSV(
        "Teste Manual",
        "Guloso",
        -1,
        -1,
        -1,
        semente,
        tempo.count(),
        solucao.valorObjetivo
    );

    cout << "\nResultado salvo em resultados.csv\n";

    return 0;
}