#include <iostream>
#include <vector>
#include "MeuGrafo.hpp"

using namespace std;

void mostrarComponentes(MeuGrafo &g)
{
    vector<vector<int>> componentes = g.componentesConexas();

    cout << "\nCOMPONENTES CONEXAS:\n";

    for (int i = 0; i < componentes.size(); i++)
    {
        cout << "Componente " << i + 1 << ": ";

        for (int v : componentes[i])
        {
            cout << v << " ";
        }

        cout << endl;
    }
}

int main()
{
    /*
        TESTE 1:
        0 -- 1 -- 2

        3 -- 4
    */

    cout << "=====================================\n";
    cout << "TESTE 1 - DUAS COMPONENTES CONEXAS\n";
    cout << "=====================================\n";

    MeuGrafo g1(false);

    for (int i = 0; i <= 4; i++)
    {
        g1.inserirVertice(i);
    }

    g1.inserirAresta(0, 1, 1);
    g1.inserirAresta(1, 2, 1);
    g1.inserirAresta(3, 4, 1);

    cout << "GRAFO:\n";
    g1.exibirGrafo();

    mostrarComponentes(g1);

    /*
        TESTE 2:
        0 -- 1 -- 2 -- 3 -- 4
    */

    cout << "\n=====================================\n";
    cout << "TESTE 2 - GRAFO TOTALMENTE CONECTADO\n";
    cout << "=====================================\n";

    MeuGrafo g2(false);

    for (int i = 0; i <= 4; i++)
    {
        g2.inserirVertice(i);
    }

    g2.inserirAresta(0, 1, 1);
    g2.inserirAresta(1, 2, 1);
    g2.inserirAresta(2, 3, 1);
    g2.inserirAresta(3, 4, 1);

    cout << "GRAFO:\n";
    g2.exibirGrafo();

    mostrarComponentes(g2);

    /*
        TESTE 3:
        0 -- 1 -- 2

        3 isolado
    */

    cout << "\n=====================================\n";
    cout << "TESTE 3 - VERTICE ISOLADO\n";
    cout << "=====================================\n";

    MeuGrafo g3(false);

    for (int i = 0; i <= 3; i++)
    {
        g3.inserirVertice(i);
    }

    g3.inserirAresta(0, 1, 1);
    g3.inserirAresta(1, 2, 1);

    cout << "GRAFO:\n";
    g3.exibirGrafo();

    mostrarComponentes(g3);

    return 0;
}