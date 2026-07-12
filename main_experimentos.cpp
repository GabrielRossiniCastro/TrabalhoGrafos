#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include "MeuGrafo.hpp"

using namespace std;
using namespace chrono;

struct Instancia
{
    string nome;
    string caminho;
    double melhorConhecido;
};

struct ConfigAlgoritmo
{
    string chave;
    string nome;
    double alpha;
    int iteracoes;
    int bloco;
};

struct Estatistica
{
    double melhorValor;
    double somaValores;
    double somaTempos;
    unsigned int melhorSemente;

    Estatistica()
        : melhorValor(numeric_limits<double>::infinity()),
          somaValores(0.0),
          somaTempos(0.0),
          melhorSemente(0)
    {
    }
};

string dataHoraAtual()
{
    time_t agora = time(nullptr);
    tm *dataHora = localtime(&agora);

    char buffer[32];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", dataHora);

    return string(buffer);
}

string valorCampo(double valor)
{
    if (valor < 0)
    {
        return "-";
    }

    ostringstream oss;
    oss << fixed << setprecision(1) << valor;
    return oss.str();
}

string valorLatex(double valor, int casas, bool negrito)
{
    ostringstream oss;
    oss << fixed << setprecision(casas) << valor;

    if (negrito)
    {
        return "\\textbf{" + oss.str() + "}";
    }

    return oss.str();
}

double desvioPercentual(double valorObtido, double melhorConhecido)
{
    if (melhorConhecido == 0.0)
    {
        return 0.0;
    }

    return ((valorObtido - melhorConhecido) / melhorConhecido) * 100.0;
}

bool linhaAssinaturaSTP(const string &linha, bool primeiraLinhaUtil)
{
    if (!primeiraLinhaUtil)
    {
        return false;
    }

    size_t inicio = linha.find_first_not_of(" \t\r\n");
    if (inicio == string::npos)
    {
        return false;
    }

    string conteudo = linha.substr(inicio);

    return conteudo.find("STP File") != string::npos;
}

bool prepararInstanciaSTP(const string &caminhoOriginal, const string &caminhoTemporario)
{
    ifstream entrada(caminhoOriginal.c_str());

    if (!entrada.is_open())
    {
        cout << "Erro ao abrir instancia original: " << caminhoOriginal << endl;
        return false;
    }

    ofstream saida(caminhoTemporario.c_str());

    if (!saida.is_open())
    {
        cout << "Erro ao criar instancia temporaria: " << caminhoTemporario << endl;
        return false;
    }

    string linha;
    bool primeiraLinhaUtil = true;

    while (getline(entrada, linha))
    {
        size_t inicio = linha.find_first_not_of(" \t\r\n");

        if (inicio == string::npos)
        {
            saida << linha << '\n';
            continue;
        }

        if (linhaAssinaturaSTP(linha, primeiraLinhaUtil))
        {
            primeiraLinhaUtil = false;
            continue;
        }

        primeiraLinhaUtil = false;
        saida << linha << '\n';
    }

    return true;
}

Solucao executarAlgoritmo(MeuGrafo &grafo,
                          const ConfigAlgoritmo &config,
                          unsigned int semente,
                          const vector<double> &alphasReativo)
{
    if (config.chave == "guloso")
    {
        return grafo.algoritmoGulosoPCSTP();
    }

    if (config.chave == "reativo")
    {
        return grafo.algoritmoGulosoRandomizadoReativo(
            alphasReativo,
            config.iteracoes,
            config.bloco,
            semente);
    }

    return grafo.algoritmoGulosoRandomizado(
        config.alpha,
        config.iteracoes,
        semente);
}

vector<Instancia> montarInstancias()
{
    vector<Instancia> instancias;

    instancias.push_back({"b01", "B/b01.stp", 82});
    instancias.push_back({"b03", "B/b03.stp", 138});
    instancias.push_back({"b08", "B/b08.stp", 104});

    return instancias;
}

void escreverCabecalhoTabela(ofstream &arquivo, const vector<ConfigAlgoritmo> &configs)
{
    arquivo << "Instancia;MelhorConhecido";

    for (const ConfigAlgoritmo &config : configs)
    {
        arquivo << ";" << config.nome;
    }

    arquivo << endl;
}

void escreverLinhaTabela(ofstream &arquivo,
                         const Instancia &instancia,
                         const vector<double> &valores)
{
    arquivo << instancia.nome << ";"
            << fixed << setprecision(6) << instancia.melhorConhecido;

    for (double valor : valores)
    {
        arquivo << ";" << fixed << setprecision(6) << valor;
    }

    arquivo << endl;
}

void escreverLinhaLatex(ofstream &arquivo,
                        const Instancia &instancia,
                        const vector<double> &valores,
                        int casas,
                        bool destacarMenor)
{
    double menor = numeric_limits<double>::infinity();

    if (destacarMenor)
    {
        for (double valor : valores)
        {
            if (valor < menor)
            {
                menor = valor;
            }
        }
    }

    arquivo << instancia.nome;

    for (double valor : valores)
    {
        bool negrito = destacarMenor && (abs(valor - menor) < 1e-9);
        arquivo << " & " << valorLatex(valor, casas, negrito);
    }

    arquivo << " \\\\" << endl;
}

int main(int argc, char *argv[])
{
    const int execucoesPorInstancia = 10;
    const int iteracoesRandomizado = 30;
    const int iteracoesReativo = 300;
    const int tamanhoBlocoReativo = 30;
    const string arquivoTemporario = "instancia_stp_preprocessada.tmp";

    vector<double> alphasReativo;
    alphasReativo.push_back(0.2);
    alphasReativo.push_back(0.3);
    alphasReativo.push_back(0.4);

    vector<ConfigAlgoritmo> configs;
    configs.push_back({"guloso", "Guloso", -1.0, -1, -1});
    configs.push_back({"rand02", "Randomizado_alpha_0.2", 0.2, iteracoesRandomizado, -1});
    configs.push_back({"rand03", "Randomizado_alpha_0.3", 0.3, iteracoesRandomizado, -1});
    configs.push_back({"rand04", "Randomizado_alpha_0.4", 0.4, iteracoesRandomizado, -1});
    configs.push_back({"reativo", "Reativo_0.2_0.3_0.4", -1.0, iteracoesReativo, tamanhoBlocoReativo});

    vector<Instancia> instancias = montarInstancias();

    if (argc > 1)
    {
        string filtro = argv[1];
        vector<string> filtros;
        string filtroAtual;
        stringstream ssFiltro(filtro);

        while (getline(ssFiltro, filtroAtual, ','))
        {
            if (!filtroAtual.empty())
            {
                filtros.push_back(filtroAtual);
            }
        }

        vector<Instancia> filtradas;

        for (const Instancia &instancia : instancias)
        {
            for (const string &itemFiltro : filtros)
            {
                if (instancia.nome == itemFiltro || instancia.nome.find(itemFiltro) == 0)
                {
                    filtradas.push_back(instancia);
                    break;
                }
            }
        }

        instancias = filtradas;
    }

    if (instancias.empty())
    {
        cout << "Nenhuma instancia encontrada para o filtro informado." << endl;
        return 1;
    }

    ofstream execucoes("resultados_execucoes.csv");
    ofstream resumo("resultados_resumo.csv");
    ofstream tabelaDesvioMelhor("tabela_desvio_melhor.csv");
    ofstream tabelaDesvioMedia("tabela_desvio_media.csv");
    ofstream tabelaTempoMedio("tabela_tempo_medio.csv");
    ofstream latex("linhas_latex_relatorio.txt");

    if (!execucoes.is_open() ||
        !resumo.is_open() ||
        !tabelaDesvioMelhor.is_open() ||
        !tabelaDesvioMedia.is_open() ||
        !tabelaTempoMedio.is_open() ||
        !latex.is_open())
    {
        cout << "Erro ao criar arquivos de saida dos experimentos." << endl;
        return 1;
    }

    execucoes << "DataHora;Instancia;Algoritmo;Alpha;Iteracoes;Bloco;Semente;Tempo(s);ValorObtido" << endl;
    resumo << "Instancia;MelhorConhecido;Algoritmo;Alpha;Iteracoes;Bloco;Melhor10Execucoes;Media10Execucoes;TempoMedio(s);DesvioMelhor(%);DesvioMedia(%);MelhorSemente" << endl;

    escreverCabecalhoTabela(tabelaDesvioMelhor, configs);
    escreverCabecalhoTabela(tabelaDesvioMedia, configs);
    escreverCabecalhoTabela(tabelaTempoMedio, configs);

    latex << "Tabela 1 - Desvio percentual da melhor solucao das 10 execucoes" << endl;
    latex << "Instancia & Guloso & Rand. $\\alpha=0.2$ & Rand. $\\alpha=0.3$ & Rand. $\\alpha=0.4$ & Reativo \\\\" << endl;

    unsigned int sementeBase = 100000;

    cout << "Executando experimentos com " << execucoesPorInstancia
         << " execucoes por instancia." << endl;
    cout << "Use um filtro opcional, por exemplo: programa.exe b ou programa.exe c01" << endl;

    for (size_t indiceInstancia = 0; indiceInstancia < instancias.size(); indiceInstancia++)
    {
        const Instancia &instancia = instancias[indiceInstancia];

        cout << "\n[" << (indiceInstancia + 1) << "/" << instancias.size()
             << "] Instancia " << instancia.nome << endl;

        if (!prepararInstanciaSTP(instancia.caminho, arquivoTemporario))
        {
            return 1;
        }

        MeuGrafo grafo(false);

        if (!grafo.lerArquivo(arquivoTemporario))
        {
            cout << "Nao foi possivel carregar a instancia: "
                 << instancia.caminho << endl;
            return 1;
        }

        vector<Estatistica> estatisticas(configs.size());

        for (int execucao = 0; execucao < execucoesPorInstancia; execucao++)
        {
            unsigned int semente = sementeBase
                                   + static_cast<unsigned int>(indiceInstancia * 100)
                                   + static_cast<unsigned int>(execucao);

            for (size_t indiceConfig = 0; indiceConfig < configs.size(); indiceConfig++)
            {
                const ConfigAlgoritmo &config = configs[indiceConfig];

                auto inicio = high_resolution_clock::now();
                Solucao solucao = executarAlgoritmo(grafo, config, semente, alphasReativo);
                auto fim = high_resolution_clock::now();

                duration<double> tempo = fim - inicio;
                double valorObtido = solucao.valorObjetivo;

                Estatistica &estatistica = estatisticas[indiceConfig];
                estatistica.somaValores += valorObtido;
                estatistica.somaTempos += tempo.count();

                if (valorObtido < estatistica.melhorValor)
                {
                    estatistica.melhorValor = valorObtido;
                    estatistica.melhorSemente = semente;
                }

                execucoes << dataHoraAtual() << ";"
                          << instancia.nome << ";"
                          << config.nome << ";"
                          << valorCampo(config.alpha) << ";";

                if (config.iteracoes < 0)
                {
                    execucoes << "-;";
                }
                else
                {
                    execucoes << config.iteracoes << ";";
                }

                if (config.bloco < 0)
                {
                    execucoes << "-;";
                }
                else
                {
                    execucoes << config.bloco << ";";
                }

                execucoes << semente << ";"
                          << fixed << setprecision(6) << tempo.count() << ";"
                          << fixed << setprecision(6) << valorObtido << endl;
            }
        }

        vector<double> desviosMelhor;
        vector<double> desviosMedia;
        vector<double> temposMedios;

        for (size_t indiceConfig = 0; indiceConfig < configs.size(); indiceConfig++)
        {
            const ConfigAlgoritmo &config = configs[indiceConfig];
            const Estatistica &estatistica = estatisticas[indiceConfig];

            double mediaValores = estatistica.somaValores / execucoesPorInstancia;
            double tempoMedio = estatistica.somaTempos / execucoesPorInstancia;
            double desvioMelhor = desvioPercentual(estatistica.melhorValor, instancia.melhorConhecido);
            double desvioMedia = desvioPercentual(mediaValores, instancia.melhorConhecido);

            desviosMelhor.push_back(desvioMelhor);
            desviosMedia.push_back(desvioMedia);
            temposMedios.push_back(tempoMedio);

            resumo << instancia.nome << ";"
                   << fixed << setprecision(6) << instancia.melhorConhecido << ";"
                   << config.nome << ";"
                   << valorCampo(config.alpha) << ";";

            if (config.iteracoes < 0)
            {
                resumo << "-;";
            }
            else
            {
                resumo << config.iteracoes << ";";
            }

            if (config.bloco < 0)
            {
                resumo << "-;";
            }
            else
            {
                resumo << config.bloco << ";";
            }

            resumo << fixed << setprecision(6) << estatistica.melhorValor << ";"
                   << fixed << setprecision(6) << mediaValores << ";"
                   << fixed << setprecision(6) << tempoMedio << ";"
                   << fixed << setprecision(6) << desvioMelhor << ";"
                   << fixed << setprecision(6) << desvioMedia << ";"
                   << estatistica.melhorSemente << endl;
        }

        escreverLinhaTabela(tabelaDesvioMelhor, instancia, desviosMelhor);
        escreverLinhaTabela(tabelaDesvioMedia, instancia, desviosMedia);
        escreverLinhaTabela(tabelaTempoMedio, instancia, temposMedios);

        escreverLinhaLatex(latex, instancia, desviosMelhor, 2, true);

        cout << "Concluida " << instancia.nome << endl;
    }

    tabelaDesvioMedia.flush();
    tabelaTempoMedio.flush();

    latex << endl;
    latex << "Tabela 2 - Desvio percentual da media das 10 execucoes" << endl;
    latex << "Instancia & Guloso & Rand. $\\alpha=0.2$ & Rand. $\\alpha=0.3$ & Rand. $\\alpha=0.4$ & Reativo \\\\" << endl;

    ifstream tabelaMedia("tabela_desvio_media.csv");
    string linha;
    getline(tabelaMedia, linha);

    while (getline(tabelaMedia, linha))
    {
        stringstream ss(linha);
        string campo;
        vector<string> campos;

        while (getline(ss, campo, ';'))
        {
            campos.push_back(campo);
        }

        if (campos.size() < 7)
        {
            continue;
        }

        vector<double> valores;
        for (size_t i = 2; i < campos.size(); i++)
        {
            valores.push_back(atof(campos[i].c_str()));
        }

        Instancia instanciaLatex;
        instanciaLatex.nome = campos[0];
        escreverLinhaLatex(latex, instanciaLatex, valores, 2, true);
    }

    latex << endl;
    latex << "Tabela 3 - Tempo medio das 10 execucoes em segundos" << endl;
    latex << "Instancia & Guloso & Rand. $\\alpha=0.2$ & Rand. $\\alpha=0.3$ & Rand. $\\alpha=0.4$ & Reativo \\\\" << endl;

    ifstream tabelaTempo("tabela_tempo_medio.csv");
    getline(tabelaTempo, linha);

    while (getline(tabelaTempo, linha))
    {
        stringstream ss(linha);
        string campo;
        vector<string> campos;

        while (getline(ss, campo, ';'))
        {
            campos.push_back(campo);
        }

        if (campos.size() < 7)
        {
            continue;
        }

        vector<double> valores;
        for (size_t i = 2; i < campos.size(); i++)
        {
            valores.push_back(atof(campos[i].c_str()));
        }

        Instancia instanciaLatex;
        instanciaLatex.nome = campos[0];
        escreverLinhaLatex(latex, instanciaLatex, valores, 4, false);
    }

    cout << "\nArquivos gerados:" << endl;
    cout << "- resultados_execucoes.csv" << endl;
    cout << "- resultados_resumo.csv" << endl;
    cout << "- tabela_desvio_melhor.csv" << endl;
    cout << "- tabela_desvio_media.csv" << endl;
    cout << "- tabela_tempo_medio.csv" << endl;
    cout << "- linhas_latex_relatorio.txt" << endl;

    return 0;
}
