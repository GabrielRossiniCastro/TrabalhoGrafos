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
   
}