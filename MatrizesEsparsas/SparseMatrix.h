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
    SparseMatrix(int m, int n) {
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
    ~SparseMatrix(){
        clear();
        cout << "Matriz esparsas destruída" << endl;
    }


    // Depois vou fazer uma explicação do método aqui!
    void insert(int i, int j, double value) {
        if (i > linhas || i < 1 || j > colunas || j < 1) {
            throw out_of_range("Índices inválidos");
        }

        if (value == 0) {
            return;
        }

        Node* auxLinha = m_headLinha;
        Node* auxColuna = m_headColuna;
        
        while(auxLinha->abaixo != m_headLinha && auxLinha->abaixo->linha < i) {
            auxLinha = auxLinha->abaixo;
        }
        
        while(auxColuna->direita != m_headColuna && auxColuna->direita->coluna < j) {
            auxColuna = auxColuna->direita;
        }

        if(auxLinha->abaixo != m_headLinha && auxLinha->abaixo->linha == i) {
            auxLinha->abaixo->value = value;
        } else {
            Node* nodeL = new Node(i, j, value);
            nodeL->abaixo = auxLinha->abaixo;
            auxLinha->abaixo = nodeC;
        }
        
        if(auxColuna->direita != m_headColuna && auxColuna->direita->coluna == j) {
            auxColuna->abaixo->value = value;
        } else {
            Node* nodeC = new Node(i, j, value);
            nodeC->direita = auxColuna->direita;
            auxColuna->direita = nodeC;
        }
        
    }

    // Acessa valores que estão na matriz reconhecendo casos em que o valor é 0
    double get(int i, int j) {
        if(i < 1 || i > linhas || j < 1 || j > colunas){
            throw out_of_range("Índices inválidos");
        }
        
        Node* linhaAtual = m_headLinha;
        // Encontro a linha que foi passada como parâmetro
        while(linhaAtual -> abaixo != m_headLinha && linhaAtual -> abaixo -> linha <= i){
            linhaAtual = linhaAtual -> abaixo;
        }

        Node* aux = linhaAtual -> direita;
        while(aux != linhaAtual && aux -> coluna <= j) {
            if(aux -> coluna == j) {
                return aux -> value;
            }
            aux = aux -> direita;
        }

        return 0.0;

    }
    
    // Esse imprime a matriz pegando os valores pelo get reconhecendo casos em que existe 0
void print() {
    Node* linhaAtual = m_headLinha->abaixo; // Começa pela primeira linha válida

    for (int i = 1; i <= linhas; i++) {
        if (linhaAtual != m_headLinha && linhaAtual->linha == i) {
            Node* atual = linhaAtual->direita; // Primeiro elemento da linha
            for (int j = 1; j <= colunas; j++) {
                if (atual != linhaAtual && atual->coluna == j) {
                    cout << atual->value << " ";
                    atual = atual->direita; // Avança para o próximo nó na linha
                } else {
                    cout << " 0 ";
                }
            }
            linhaAtual = linhaAtual->abaixo; // Passa para a próxima linha
        } else {
            // Linha não tem elementos armazenados, imprime apenas zeros
            for (int j = 1; j <= colunas; j++) {
                cout << " 0 ";
            }
        }
        cout << endl;
    }
}

    void clear() {// apaga os elementos da lista
	    Node* linhaAtual = m_headLinha -> abaixo;
        
        while (linhaAtual != m_headLinha) {
		        Node *atual = linhaAtual -> direita;
                
                while(atual != linhaAtual){
                    Node* aux = atual;
                    atual = atual -> direita;
                    delete aux;
                }
                Node* auxLinha = linhaAtual;
                linhaAtual = linhaAtual -> abaixo;
                delete auxLinha;
            }

            Node* colunaAtual = m_headColuna -> direita;
            while(colunaAtual != m_headColuna){
                Node* aux = colunaAtual;
                colunaAtual = colunaAtual -> direita;
                delete aux;
            }
            
            delete m_headLinha;
            delete m_headColuna;
	    // Atualiza os ínidices para 0
	    linhas = 0;
        colunas = 0;
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