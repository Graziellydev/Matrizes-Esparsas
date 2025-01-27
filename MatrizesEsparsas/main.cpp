#include <iostream>
#include <fstream>
#include <string>
#include "SparseMatrix.h"
using namespace std;

//void readSparseMatrix(SparseMatrix& m, String ?); //Temos que colocar o nome do arquivo como parâmetro

SparseMatrix sum(SparseMatrix& A, SparseMatrix& B);

SparseMatrix multiply(SparseMatrix& A, SparseMatrix& B);

int main();