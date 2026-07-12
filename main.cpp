#include <iostream>
#include <ctime>
#include "MeuGrafo.hpp"

using namespace std;

int main()
{
    unsigned int semente = time(nullptr);

    cout << "=========================================\n";
    cout << " PCSTP - Algoritmos Heuristicos\n";
    cout << "=========================================\n\n";

    cout << "Semente utilizada: " << semente << endl;

    MeuGrafo grafo(false);

    if (!grafo.lerArquivo("instancia_teste.txt"))
    {
        cout << "Erro ao carregar a instancia.\n";
        return 1;
    }

    cout << "\nInstancia carregada com sucesso!\n";

    // ----------------------------------------------------
    // Guloso
    // ----------------------------------------------------

    cout << "\n===== GULOSO =====\n";

    Solucao guloso = grafo.algoritmoGulosoPCSTP();

    grafo.imprimirSolucao(guloso);

    // ----------------------------------------------------
    // Randomizado
    // ----------------------------------------------------

    cout << "\n===== GULOSO RANDOMIZADO =====\n";

    Solucao randomizado =
        grafo.algoritmoGulosoRandomizado(
            0.3,
            30,
            semente
        );

    grafo.imprimirSolucao(randomizado);

    // ----------------------------------------------------
    // Reativo
    // ----------------------------------------------------

    cout << "\n===== GULOSO RANDOMIZADO REATIVO =====\n";

    vector<double> alphas =
    {
        0.1,
        0.3,
        0.5
    };

    Solucao reativo =
        grafo.algoritmoGulosoRandomizadoReativo(
            alphas,
            300,
            30,
            semente
        );

    grafo.imprimirSolucao(reativo);

    cout << "\nFim da demonstracao.\n";

    return 0;
}