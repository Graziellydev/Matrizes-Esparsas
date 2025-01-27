#ifndef NODE_H
#define NODE_H

struct Node {

    Node *direita;
    Node *abaixo;
    int linha;
    int coluna;
    double value;

    Node(int linha, int coluna, double value) {
        this->direita = nullptr;
        this->abaixo = nullptr;
        this->linha = linha;
        this->coluna = coluna;
        this->value = value;
    }
    
};

#endif