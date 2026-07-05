#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

#include "MeuGrafo.hpp"

using namespace std;
using namespace chrono;

int main()
{
    // A semente e gerada uma unica vez na execucao.
    // Ela e impressa e tambem salva no CSV para permitir repetir o teste.
    unsigned int semente = time(nullptr);
    srand(semente);

    cout << "Semente utilizada: " << semente << endl;

    // Cria uma instancia simples em arquivo para testar a leitura.
    // Formato:
    // quantidade_vertices quantidade_arestas
    // id premio
    // origem destino peso
    ofstream instancia("instancia_teste.txt");

    instancia << "5 5" << endl;
    instancia << "1 10" << endl;
    instancia << "2 8" << endl;
    instancia << "3 5" << endl;
    instancia << "4 15" << endl;
    instancia << "5 3" << endl;
    instancia << "1 2 2" << endl;
    instancia << "2 3 3" << endl;
    instancia << "3 4 1" << endl;
    instancia << "1 4 7" << endl;
    instancia << "4 5 10" << endl;

    instancia.close();

    MeuGrafo grafo(false);

    if (!grafo.lerArquivo("instancia_teste.txt"))
    {
        cout << "Nao foi possivel carregar a instancia." << endl;
        return 1;
    }

    cout << "\nInstancia carregada com sucesso.\n";

    // ------------------------------------------------------------
    // Teste 1: algoritmo guloso simples
    // ------------------------------------------------------------

    auto inicioGuloso = high_resolution_clock::now();

    Solucao solucaoGulosa = grafo.algoritmoGulosoPCSTP();

    auto fimGuloso = high_resolution_clock::now();
    duration<double> tempoGuloso = fimGuloso - inicioGuloso;

    cout << "\n===== TESTE DO ALGORITMO GULOSO =====\n";
    grafo.imprimirSolucao(solucaoGulosa);
    grafo.salvarSolucao(solucaoGulosa, "solucao_guloso.txt");

    grafo.salvarResultadoCSV(
        "instancia_teste.txt",
        "Guloso",
        -1,
        -1,
        -1,
        semente,
        tempoGuloso.count(),
        solucaoGulosa.valorObjetivo
    );

    // ------------------------------------------------------------
    // Teste 2: algoritmo guloso randomizado
    // ------------------------------------------------------------

    double alpha = 0.3;
    int iteracoes = 30;

    auto inicioRandomizado = high_resolution_clock::now();

    Solucao solucaoRandomizada = grafo.algoritmoGulosoRandomizado(alpha, iteracoes, semente);

    auto fimRandomizado = high_resolution_clock::now();
    duration<double> tempoRandomizado = fimRandomizado - inicioRandomizado;

    cout << "\n===== TESTE DO ALGORITMO GULOSO RANDOMIZADO =====\n";
    grafo.imprimirSolucao(solucaoRandomizada);
    grafo.salvarSolucao(solucaoRandomizada, "solucao_randomizado.txt");

    grafo.salvarResultadoCSV(
        "instancia_teste.txt",
        "Guloso Randomizado",
        alpha,
        iteracoes,
        -1,
        semente,
        tempoRandomizado.count(),
        solucaoRandomizada.valorObjetivo
    );

    cout << "\nArquivos gerados:" << endl;
    cout << "- instancia_teste.txt" << endl;
    cout << "- solucao_guloso.txt" << endl;
    cout << "- solucao_randomizado.txt" << endl;
    cout << "- solucao_reativo.txt" << endl;
    cout << "- resultados.csv" << endl;

     vector<double> alphas = {0.1, 0.3, 0.5, 0.7, 0.9};

    auto inicioReativo = high_resolution_clock::now();

    Solucao solucaoReativa = grafo.algoritmoGulosoRandomizadoReativo(
        alphas,
        300,
        30,
        semente
    );

    auto fimReativo = high_resolution_clock::now();
    duration<double> tempoReativo = fimReativo - inicioReativo;

    cout << "\n===== TESTE DO GULOSO RANDOMIZADO REATIVO =====\n";
    grafo.imprimirSolucao(solucaoReativa);
    grafo.salvarSolucao(solucaoReativa, "solucao_reativo.txt");

    grafo.salvarResultadoCSV(
        "instancia_teste.txt",
        "Guloso Randomizado Reativo",
        -1,
        300,
        30,
        semente,
        tempoReativo.count(),
        solucaoReativa.valorObjetivo
    );

    return 0;
}
