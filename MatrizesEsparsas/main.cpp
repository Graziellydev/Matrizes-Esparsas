#include <iostream>
#include <fstream>
#include <string>
#include "SparseMatrix.h"
using namespace std;

void readSparseMatrix(SparseMatrix& m, string teste) {
    ifstream arquivo(teste);
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo!\n";
        return;
    }

    int linhas, colunas;
    arquivo >> linhas >> colunas; // Lendo número de linhas e colunas
    m = SparseMatrix(linhas, colunas); // Ajustando o tamanho da matriz esparsa

    int i, j;
    double valor;
    while (arquivo >> i >> j >> valor) { // Lendo cada tripla (linha, coluna, valor)
        m.insert(i, j, valor); // Inserindo na estrutura de dados da matriz esparsa
    }

    arquivo.close();
}

SparseMatrix sum(SparseMatrix& A, SparseMatrix& B);

SparseMatrix multiply(SparseMatrix& A, SparseMatrix& B);

int main();


