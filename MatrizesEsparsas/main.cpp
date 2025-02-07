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
    arquivo >> linhas >> colunas; // Lendo número de linhas e colunas
    m = new SparseMatrix(linhas, colunas); // Ajustando o tamanho da matriz esparsa

    int i, j;
    double valor;
    while (arquivo >> i >> j >> valor) { // Lendo cada tripla (linha, coluna, valor)
        m->insert(i, j, valor); // Inserindo na estrutura de dados da matriz esparsa
    }

    arquivo.close();
}

SparseMatrix* sum(SparseMatrix*& A, SparseMatrix*& B) {
    if(A->getLinhas() != B->getLinhas() || A->getColunas() != B->getColunas()) {
        throw invalid_argument("As medidas das matrizes precisam ser iguais!");
    }
    
    SparseMatrix* C = new SparseMatrix(A->getLinhas(), A->getColunas()); // Cria a matriz da soma

    Node* atualA = A->getHeadLinha()->abaixo;
    // Esse while vai percorrendo as linhas da matriz A e vai inserindo os elementos na matriz C
    while(atualA != A->getHeadLinha()) {
        Node* colunaA = atualA->direita; // Cria um node para percorrer as colunas
        // Cria um while para percorrer as colunas e inserir os elementos na matriz C
        while(colunaA != atualA) {
            C->insert(colunaA->linha, colunaA->coluna, colunaA->value); // Insere na matriz C
            colunaA = colunaA->direita; // Atualiza a posição da coluna
        }
        atualA = atualA->abaixo; // Atualiza a posição da linha
    }

    Node* atualB = B->getHeadLinha()->abaixo;
    // Esse while vai percorrendo as linhas da matriz B
    while(atualB != B->getHeadLinha()) {
        Node* colunaB = atualB->direita; // Cria um node para percorrer as colunas
        while(colunaB != atualB) {
            // Cria um node para percorrer a matriz C para verificar os nós existentes
            Node* atualC = C->getHeadLinha()->abaixo;
            bool existe = false; // Para saber se existe o nó na matriz C
            // Começa pela linha
            while(atualC != C->getHeadLinha()) {
                Node* colunaC = atualC->direita; // Cria um node para percorrer as colunas da matriz C
                // Esse while percorre as colunas da matriz C já dentro das linhas
                while(colunaC != atualC) {
                    // Esse if verifica se os índices da matriz B existem e são iguais aos mesmos da C (que veio da matriz A)
                    // Se sim, ele soma os valores, confirma que existe e fecha o loop
                    if(colunaC->linha == colunaB->linha && colunaC->coluna == colunaB->coluna) {
                        colunaC->value += colunaB->value;
                        existe = true;
                        break;
                    }
                    colunaC = colunaC->direita; // Atualiza a posição da coluna da matriz C
                }
                // Se deu tudo certo ele quebra o loop da linha da matriz C
                if(existe == true) {
                    break;
                }
                atualC = atualC->abaixo; // Atualiza a posição da linha da matriz C
            }
            // Caso o nó não existe, ele cria e insere na posição desejada
            if(existe == false) {
                C->insert(colunaB->linha, colunaB->coluna, colunaB->value);
            }
            colunaB = colunaB->direita; // Atualiza a posição da coluna da matriz B
        }
        atualB = atualB->abaixo; // Atualiza a posição da linha da matriz B
    }
    return C;
}

SparseMatrix* sub(SparseMatrix*& A, SparseMatrix*& B) {
    if(A->getLinhas() != B->getLinhas() || A->getColunas() != B->getColunas()) {
        throw invalid_argument("As medidas das matrizes precisam ser iguais!");
    }
    
    SparseMatrix* C = new SparseMatrix(A->getLinhas(), A->getColunas()); // Cria a matriz da soma

    Node* atualA = A->getHeadLinha()->abaixo;
    // Esse while vai percorrendo as linhas da matriz A e vai inserindo os elementos na matriz C
    while(atualA != A->getHeadLinha()) {
        Node* colunaA = atualA->direita; // Cria um node para percorrer as colunas
        // Cria um while para percorrer as colunas e inserir os elementos na matriz C
        while(colunaA != atualA) {
            C->insert(colunaA->linha, colunaA->coluna, colunaA->value); // Insere na matriz C
            colunaA = colunaA->direita; // Atualiza a posição da coluna
        }
        atualA = atualA->abaixo; // Atualiza a posição da linha
    }

    Node* atualB = B->getHeadLinha()->abaixo;
    // Esse while vai percorrendo as linhas da matriz B
    while(atualB != B->getHeadLinha()) {
        Node* colunaB = atualB->direita; // Cria um node para percorrer as colunas
        while(colunaB != atualB) {
            // Cria um node para percorrer a matriz C para verificar os nós existentes
            Node* atualC = C->getHeadLinha()->abaixo;
            bool existe = false; // Para saber se existe o nó na matriz C
            // Começa pela linha
            while(atualC != C->getHeadLinha()) {
                Node* colunaC = atualC->direita; // Cria um node para percorrer as colunas da matriz C
                // Esse while percorre as colunas da matriz C já dentro das linhas
                while(colunaC != atualC) {
                    // Esse if verifica se os índices da matriz B existem e são iguais aos mesmos da C (que veio da matriz A)
                    // Se sim, ele soma os valores, confirma que existe e fecha o loop
                    if(colunaC->linha == colunaB->linha && colunaC->coluna == colunaB->coluna) {
                        colunaC->value -= colunaB->value;
                        existe = true;
                        break;
                    }
                    colunaC = colunaC->direita; // Atualiza a posição da coluna da matriz C
                }
                // Se deu tudo certo ele quebra o loop da linha da matriz C
                if(existe == true) {
                    break;
                }
                atualC = atualC->abaixo; // Atualiza a posição da linha da matriz C
            }
            // Caso o nó não existe, ele cria e insere na posição desejada
            if(existe == false) {
                C->insert(colunaB->linha, colunaB->coluna, colunaB->value * -1);
            }
            colunaB = colunaB->direita; // Atualiza a posição da coluna da matriz B
        }
        atualB = atualB->abaixo; // Atualiza a posição da linha da matriz B
    }
    return C;
}

 /* SparseMatrix* multiply(SparseMatrix*& A, SparseMatrix*& B) {
    if(A->getColunas() != B->getLinhas()) {
        throw out_of_range("Erro: tamanhos inválidos das matrizes para realizar a multiplicação!");
    }

    SparseMatrix C* = new SparseMatrix(A->getLinhas(), B->getColunas());
 } */

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

int main(){
    
    cout << "Bem-vindo" << endl;

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
    cout << "---------------------------\n";
    //C->print();
    cout << "---------------------------\n";
    C = sub(A, B);
    cout << "---------------------------\n";
    C->print();


    
    delete A;
    delete B;
    delete C;

    
     /*string comando;
     while(true) {
        cout << "Digite um comando: ";
        string entrada;
        getline(cin, entrada);
        istringstream iss(entrada);
        iss >> comando;
        if(comando == "sair") {
            cout << "Saindo do programa..." << endl;
            break;
        } else if(comando == "multiply") { 
            return 0;
            
        } else if(comando == "create") {
            int linhas, colunas;
            if(iss >> linhas >> colunas) {
                matrizes.push_back(SparseMatrix(linhas, colunas));
                cout >> "Matriz criada com " << linhas " linhas e " << colunas << "colunas ;)";
            } else {
                cout << " Entrada invalida :/ Lembre-se que voce deve passar o numero de linhas e colunas da matriz";
            }
            return 0;
            
        } else if(comando == "show") {
            return 0;
        
        } else if(comando == "insert") {
            return 0;

        } else if(comando == "menu") {
            mostrarMenu();
        }
    } */
    
     // readSparseMatrix(A, "teste.txt");
    

    
    /* // Inserir valores na matriz
    A.insert(1, 1, 10);
    A.insert(1, 2, 20);
    A.insert(1, 3, 30);

    A.insert(2, 1, 40);
    A.insert(2, 2, 50);
    A.insert(2, 3, 60);
    
    A.insert(3, 1, 70);
    A.insert(3, 2, 80);
    A.insert(3, 3, 90);

    // Testar a função get para os valores inseridos
    cout << "Valor na posicao (1, 1): " << A.get(1, 1) << endl;
    cout << "Valor na posicao (1, 2): " << A.get(1, 2) << endl;
    cout << "Valor na posicao (1, 3): " << A.get(1, 3) << endl;
    
    cout << "Valor na posicao (2, 1): " << A.get(2, 1) << endl;
    cout << "Valor na posicao (2, 2): " << A.get(2, 2) << endl;
    cout << "Valor na posicao (2, 3): " << A.get(2, 3) << endl;

    
    cout << "Valor na posicao (3, 1): " << A.get(3, 1) << endl;
    cout << "Valor na posicao (3, 2): " << A.get(3, 2) << endl;
    cout << "Valor na posicao (3, 3): " << A.get(3, 3) << endl;
    
    cout << "----------------------------------------------------" << endl;
    A.insert(1, 1, 11);
    A.insert(2, 2, 25);
    A.insert(3, 3, 35);
    A.insert(2, 1, 15);

    cout << "Valor na posicao (1, 1): " << A.get(1, 1) << endl;  // Esperado: 10.5
    cout << "Valor na posicao (2, 2): " << A.get(2, 2) << endl;  // Esperado: 20.5
    cout << "Valor na posicao (3, 3): " << A.get(3, 3) << endl;  // Esperado: 20.0
    cout << "Valor na posicao (2, 1): " << A.get(2, 1) << endl;  // Esperado: 15.0
    
    /* Testar a função get para posições não preenchidas
    cout << "Valor na posicao (1, 2): " << A.get(1, 2) << endl;  // Esperado: 0.0
    cout << "Valor na posicao (2, 3): " << A.get(2, 3) << endl;  // Esperado: 0.0
    cout << "Valor na posicao (3, 1): " << A.get(3, 1) << endl;  // Esperado: 0.0
    */
    // Limpar a matriz e verificar se o código funciona sem vazamento de memória
     // A.clear();
    
    // Após chamar clear, tentaremos acessar a matriz novamente para verificar
    /*try {
        cout << "Tentando acessar valor apos limpar a matriz: " << A.get(1, 1) << endl;
    } catch (const out_of_range& e) {
        cout << "Erro esperado: " << e.what() << endl;  // Esperado: Erro de índice inválido
    }
*/
    return 0;
}

