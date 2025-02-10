/* Co-autores: Thalisson Perdigão e Grazielly Lima */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ctime>
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
            if(subtracao != 0) {
                C->insert(i, j, subtracao);
            }
            j++;
        }
        i++;
    }

    return C;
}

SparseMatrix* multiply(SparseMatrix*& A, SparseMatrix*& B) {
    if (A->getColunas() != B->getLinhas()) {
        throw invalid_argument("Os tamanhos das matrizes são invalidos para realizar a multiplicacao!");
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

SparseMatrix* randomMatriz(int linhas, int colunas) {
    SparseMatrix* matriz = new SparseMatrix(linhas, colunas);
    srand(time(0));
    
    int elementos = (linhas * colunas) / 2;
    for (int k = 0; k < elementos; k++) {
        int i = rand() % linhas + 1;  // Índices começam em 1
        int j = rand() % colunas + 1;
        int valor = rand() % 10 - 5;  // Valores entre -5 e 4
        if (valor != 0) matriz->insert(i, j, valor);
    }
    return matriz;
}

void salvarMatriz(vector<SparseMatrix*>& matrizes, SparseMatrix* resultado) {
    if (!resultado) {
        cout << "Erro: matriz invalida.\n";
        return;
    }

    char opcao;
    cout << "Deseja salvar a matriz resultante? (s/n): ";
    cin.ignore();
    cin >> opcao;
    cin.ignore();
    
    if (opcao == 's' || opcao == 'S') {
        matrizes.push_back(resultado);
        cout << "Matriz salva no indice " << matrizes.size() - 1 << ".\n";
    } else {
        delete resultado;  // Libera a memória se o usuário não quiser salvar
        cout << "Matriz descartada.\n";
    }
}


void mostrarMenu() {
    cout << "------------------------ MENU DE OPCOES :) ------------------------\n"
         << "| sair -> sai do programa :( \n"
         << "| create n m -> passe o numero de linhas (n) e o numero de colunas (m) para criar uma nova matriz\n"
         << "| sum i j -> soma as matrizes presentes nos índices i e j\n"
         << "| sub i j -> subtrai as matrizes presentes nos índices i e j\n"
         << "| multiply i j -> multiplica as matrizes presentes nos indices i e j\n"
         << "| show i -> mostra matriz de indice i\n"
         << "| showidx -> mostra os indices da matrizes\n"
         << "| vec -> mostra uma pequena descricao do vetor de matrizes\n"
         << "| randomMatriz n m -> cria uma matriz com valores aleatorios\n"
         << "| clear i -> limpa a matriz no indice i\n"
         << "| read 'm.txt' -> le uma matriz esparsa de um arquivo de texto\n"
         << "| insert m i j value -> insere o valuer nos indices (i,j) da matriz m\n"
         << "| eraseAll -> apaga todas as matrizes\n"
         
         << "-------------------------------------------------------------------\n";
}
    
int main() {

    vector<SparseMatrix*> matrizes;
    string input, comando;

    do {
        mostrarMenu();
        getline(cin, input);
        stringstream ss(input);
        ss >> comando;

        if (comando == "create") {
            cout << "Criando matriz...\n";
            int linhas, colunas;
            ss >> linhas >> colunas;
            SparseMatrix* matriz = new SparseMatrix(linhas,colunas);
            matrizes.push_back(matriz);
        } else if (comando == "sum") {
            cout << "Somando matrizes...\n";
            int m1, m2;
            ss >> m1 >> m2;
            SparseMatrix* resultado = sum(matrizes[m1], matrizes[m2]);
            resultado -> print();
            salvarMatriz(matrizes, resultado);
        } else if (comando == "sub") {
            cout << "Subtraindo matrizes...\n";
            int m1, m2;
            ss >> m1 >> m2;
            SparseMatrix* resultado = sub(matrizes[m1], matrizes[m2]);
            resultado -> print();
            salvarMatriz(matrizes, resultado);
        } else if (comando == "multiply") {
            cout << "Multiplicando matrizes...\n";
            int m1, m2;
            ss >> m1 >> m2;
            SparseMatrix* resultado = multiply(matrizes[m1], matrizes[m2]);
            resultado -> print();
            salvarMatriz(matrizes, resultado);
        }  else if (comando == "show") {
            int ind;
            ss >> ind;
            if(ind >= matrizes.size() || ind < 0){
                cout << "Indice invalido!\n";
            } else {
                matrizes[ind] -> print();
            }
        } else if (comando == "showidx") {
            cout << "Os indices do vetor sao: ";
            for(int i = 0; i < matrizes.size(); i++) {
                cout << i << " ";
            }
            cout << "\n";
        } else if (comando == "vec") {
            if(matrizes.size() == 0) {
                cout << "Vetor de matrizes esta vazio no momento\n";
            } else if (matrizes.size() == 1) {
                cout << "Nesse momento, o vetor comporta 1 matriz\n";
            } else {
                cout << "Nesse momento, o vetor comporta " << matrizes.size() << " matrizes!\n";
            }
        } else if (comando == "randomMatriz") {
            cout << "Criando matriz com valores aleatorios...\n";
            int n, m;
            ss >> n >> m;
            SparseMatrix* random = randomMatriz(n, m);
            matrizes.push_back(random);
        } else if (comando == "clear") {
            cout << "Limpando matriz...\n";
            int i;
            ss >> i;
            if(i < 0 || i >= matrizes.size()) {
                cout << "Indice invalido\n";
            }
            delete matrizes[i];
            matrizes.erase(matrizes.begin() + i); //Reorganiza matrizes pra esquerda
            cout << "Matriz " << i << " deletada com sucesso! Os indices foram atualizados :)\n";
        } else if (comando == "read") {
            string file;
            ss >> file;
            SparseMatrix* D = nullptr;
            readSparseMatrix(D, file);
            matrizes.push_back(D);
        } else if (comando == "insert") {
            int m, i, j, value;
            ss >> m >> i >> j >> value;
            matrizes[m] -> insert(i, j, value);
        } else if (comando == "eraseAll") {
            cout << "Limpando vetor de matrizes...\n";
            for(SparseMatrix* matriz : matrizes) {
                delete matriz;
            }
            matrizes.clear();
            cout << "O vetor de matrizes foi limpo\n";
        }
    } while (comando != "sair");
    
    cout << "Saindo..." << endl;
    for(SparseMatrix* matriz: matrizes) {
        delete matriz;
    }
    
    return 0;
}