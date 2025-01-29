#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include <iostream>
#include <stdexcept>
#include "Node.h"

class SparseMatrix {
    
private:

    int linhas, colunas;
    Node* m_headLinha;
    Node* m_headColuna;

public:

// OBS: Grazi, esse comentários são apenas para nós 2
// Não é pro Atílio, não se preocupe ;)

    // Construtor
    SparseMatrix(int m, int n) {
        if (m <= 0 || n <= 0) {
            throw invalid_argument("As medidas precisam ser positivas");
        }

        m_headLinha = new Node(0, 0, 0);
        m_headColuna = new Node(0, 0, 0);

        // Continuo depois...
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
    double get(int i, int j);


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