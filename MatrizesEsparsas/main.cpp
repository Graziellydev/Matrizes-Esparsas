#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "SparseMatrix.h"
using namespace std;

void readSparseMatrix(SparseMatrix*& m, const string& filename) {
    ifstream arquivo(filename);
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo!\n";
        return;
    }

    int linhas, colunas;
    arquivo >> linhas >> colunas;
    m = new SparseMatrix(linhas, colunas);

    int i, j;
    double valor;
    while (arquivo >> i >> j >> valor) {
        m->insert(i, j, valor);
    }

    arquivo.close();
}

SparseMatrix* sum(SparseMatrix*& A, SparseMatrix*& B) {
    if(A->getLinhas() != B->getLinhas() || A->getColunas() != B->getColunas()) {
        throw invalid_argument("As medidas das matrizes precisam ser iguais!");
    }
    
    SparseMatrix* C = new SparseMatrix(A->getLinhas(), A->getColunas());

    int i = 1;
    while(i <= A->getLinhas()) {
        int j = 1;
        double soma = 0;
        while(j <= A->getColunas()) {
            soma = A->get(i, j) + B->get(i, j);
            if(soma != 0) {
                C->insert(i, j, soma);  
            }
            j++;
        }
        i++;
    }

    return C;
}

SparseMatrix* sub(SparseMatrix*& A, SparseMatrix*& B) {
    if(A->getLinhas() != B->getLinhas() || A->getColunas() != B->getColunas()) {
        throw invalid_argument("As medidas das matrizes precisam ser iguais!");
    }
    
    SparseMatrix* C = new SparseMatrix(A->getLinhas(), A->getColunas());

    int i = 1;
    while(i <= A->getLinhas()) {
        int j = 1;
        double subtracao = 0;
        while(j <= A->getColunas()) {
            subtracao = A->get(i, j) - B->get(i, j);
            C->insert(i, j, subtracao);  
            j++;
        }
        i++;
    }

    return C;
}

SparseMatrix* multiply(SparseMatrix*& A, SparseMatrix*& B) {
    if (A->getColunas() != B->getLinhas()) {
        throw invalid_argument("Os tamanhos das matrizes são inválidos para realizar a multiplicação!");
    }

    SparseMatrix* C = new SparseMatrix(A->getLinhas(), B->getColunas());
    
    int i = 1;
    while(i <= A->getLinhas()) {
        int j = 1;
        while(j <= B->getColunas()) {
            int k = 1;
            double multiplicacao = 0;
            while(k <= B->getLinhas()) {
                multiplicacao += A->get(i, k) * B->get(k, j);
                k++;
            }
            if(multiplicacao != 0) {
                C->insert(i, j, multiplicacao);
            }
            j++;
        }
        i++;
    }

    return C;
}

void mostrarMenu() {
    cout << "------------------------ MENU DE OPCOES :) ------------------------\n"
         << "| sair -> sai do programa :( \n"
         << "| create n m -> passe o numero de linhas (n) e o numero de colunas (m) para criar uma nova matriz\n"
         << "| sum A B -> soma as matrizes A e B\n"
         << "| multiply A B -> multiplica as matrizes A e B\n"
         << "| sub A B -> subtrai as matrizes A e B\n"
         << "| show i -> mostra matriz de indice i\n"
         << "| vec -> mostra uma pequena descricao do vetor de matrizes\n"
         << "| randomMatriz -> cria uma matriz com valores aleatorios\n"
         
         << "-------------------------------------------------------------------\n";
}

/*int main(){
    
   /* cout << "Bem-vindo!" << endl;

    vector<SparseMatrix*> matrizes;

    SparseMatrix* A = nullptr;
    readSparseMatrix(A, "teste.txt");
    A->print();
    SparseMatrix* B = nullptr;
    readSparseMatrix(B, "teste2.txt");
    B->print();
    cout << endl;
    matrizes.push_back(A);
    matrizes.push_back(B);

    matrizes[0]->print();
    cout << endl;
    matrizes[1]->print();

    cout << endl;
    SparseMatrix* C = nullptr;
    //C = sum(A, B);
    //C->print();
    C = sub(A, B);
    C->print();


    
    delete A;
    delete B;
    delete C;
*/
    
int main() {
    int linhas, colunas;
    cout << "Digite o número de linhas e colunas da matriz: ";
    cin >> linhas >> colunas;
    SparseMatrix matriz(linhas, colunas);
    
    string comando;
    do {
        mostrarMenu();
        cin >> comando;
        // São ponteiros! Se criarmos sem ponteiros teremos que fazer um construtor de cópia e um operador!!!
        //suspeitei
        // Pq tu alterou o print? Não tava correto?
        if (comando == "create") {
            cin >> linhas >> colunas;
            matriz = SparseMatrix(linhas, colunas);
        } else if (comando == "sum") {
            SparseMatrix matrizB(linhas, colunas);
            SparseMatrix resultado = sum(matriz, matrizB);
            resultado.print();
        } else if (comando == "multiply") {
            SparseMatrix matrizB(linhas, colunas);
            SparseMatrix resultado = multiply(matriz, matrizB);
            resultado.print();
        } else if (comando == "sub") {
            SparseMatrix matrizB(linhas, colunas);
            // Implementação da subtração aqui
        } else if (comando == "show") {
            matriz.print();
        } else if (comando == "vec") {
            cout << "Mostrando descricao do vetor de matrizes...\n";
        } else if (comando == "randomMatriz") {
            cout << "Criando matriz com valores aleatórios...\n";
            // Implementação da geração aleatória aqui
        } else if (comando != "sair") {
            cout << "Comando inválido!\n";
        }
        
    } while (comando != "sair");
    
    cout << "Saindo..." << endl;
    return 0;
}