#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <iostream>
#include <stdexcept>
#include "Node.h"

using namespace std;

class SparseMatrix {
private:

    int linhas, colunas;
    Node* m_headLinha;
    Node* m_headColuna;
    

public:

// OBS: Grazi, esse comentários são apenas para nós 2
// Não é pro Atílio, não se preocupe ;)

    // Construtor que recebe como parâmetro o numero de linhas e colunas
    void SparseMatrix(int m, int n) {
        if (m <= 0 || n <= 0) {
            throw invalid_argument("As medidas precisam ser positivas");
            return;
        }
            
        linhas = m;
        colunas = n;
            
        m_headLinha = new Node(0, 0, 0);
        Node* auxLinha = m_headLinha;

        for(int i = 1; i <= m; i++) {
            Node* node = new Node(i, 0, 0);
            auxLinha -> abaixo =  node;
            auxLinha = node;
            auxLinha -> direita = auxLinha;
        }
        auxLinha->abaixo = m_headLinha;

        m_headColuna = new Node(0, 0, 0);
        Node* auxColuna = m_headColuna;
        
        for(int i = 1; i <= n; i++) {
            Node* node = new Node(0, i, 0);
            auxColuna -> direita = node;
            auxColuna = node;
            auxColuna -> abaixo = auxColuna;
        }
        auxColuna->direita = m_headColuna;
    }

    // Destrutor
    ~SparseMatrix();


    // Esse aqui insere um valor na matriz (ou escreve por cima)
    void insert(int i, int j, double value) {
        if (i > linhas || i < 1 || j > colunas || j < 1) {
            throw out_of_range("Índices inválidos");
        }

        if (value == 0) {
            return;
        }

        // Continuo depois...
    }

    // Esse aqui pega os valores que estão na matriz
    double get(int i, int j) {
        Node* aux = new Node(0, 0, 0);
        aux = m_headLinha;
        int indice = 1;
        for(int i = 1; i <= linhas; i++) {
            for(int j = 1; j <= colunas; j++){

            }
        }


    }


    // Esse só imprime a matriz pegando os valores pelo get
    void print() {
        for (int i = 1; i <= linhas; i++) {
            for (int j = 1; j <= colunas; j++) {
                cout << get(i, j) << " ";
            }
            cout << endl;
        }
    }

    // Esses métodos são opcionais
    // Criei apenas caso a gente precise (consequências do Java)
    int getLinhas() {
        return linhas;
    }

    int getColunas() {
        return colunas;
    }

};

#endif