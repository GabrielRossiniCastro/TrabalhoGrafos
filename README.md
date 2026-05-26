TRABALHO PRÁTICO 1 - TEORIA DOS GRAFOS

INSTRUÇÕES DE COMPILAÇÃO E EXECUÇÃO

==================================================

REQUISITOS:
- Compilador C++ (g++)
- MinGW/MSYS2 no Windows
ou GCC no Linux

==================================================

ARQUIVOS DO PROJETO:

- main.cpp
- MeuGrafo.cpp
- MeuGrafo.hpp
- No.cpp
- No.hpp
- testAll.cpp

==================================================
EXECUÇÃO DOS TESTES DE COMPONENTES CONEXAS
(main.cpp)
==================================================

COMPILAÇÃO:

Linux / GitHub Codespaces:

g++ main.cpp MeuGrafo.cpp No.cpp -o teste

Windows:

g++ main.cpp MeuGrafo.cpp No.cpp -o teste.exe

EXECUÇÃO:

Linux:

./teste

Windows:

.\teste.exe

==================================================
EXECUÇÃO DA BATERIA COMPLETA DE TESTES
(testAll.cpp)
==================================================

COMPILAÇÃO:

Linux / GitHub Codespaces:

g++ main.cpp MeuGrafo.cpp No.cpp testAll.cpp -o programa

Windows:

g++ main.cpp MeuGrafo.cpp No.cpp testAll.cpp -o programa.exe

EXECUÇÃO:

Linux:

./programa

Windows:

.\programa.exe

==================================================

DESCRIÇÃO:

O projeto implementa um grafo utilizando
lista de adjacência e determina componentes
conexas utilizando DFS (Depth First Search).

O main.cpp contém testes demonstrativos
das componentes conexas.

O testAll.cpp contém a bateria completa
de testes obrigatórios do trabalho.

==================================================
