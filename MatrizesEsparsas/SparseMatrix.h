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

    // Construtor default
    SparseMatrix() {
        linhas = 0;
        colunas = 0;
        m_headLinha = nullptr;
        m_headColuna = nullptr;
    }

    // Construtor que recebe como parâmetro o numero de linhas e colunas
    SparseMatrix(int m, int n) {
        if (m <= 0 || n <= 0) {
            throw invalid_argument("As medidas precisam ser positivas");
            return;
        }
        inicializar(m, n);
    }

    void inicializar(int m, int n) {
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
    ~SparseMatrix() {
        clear();  // Chama a função clear para liberar a memória corretamente
        cout << "Matriz esparsa destruída" << endl;
}


    /* Primeiro ele faz a verificação se os índices são válidos, se forem o código continua.
    Depois disso ele verifica se o value é 0, se não for, o código continua.
    Depois, ele cria dois nós auxiliares para a linha e coluna, começando pelo nó sentinela.
    Depois, ele possui dois loops que percorrem a lista de linhas e colunas para chegar na posição desejada.
    Depois, ele faz uma verificação para saber se o elemento no índice (i,j) já existe.
    Caso exista, ele só atualiza o valor.
    Caso não exista, ele cria um novo nó e insere nas estruturas de linhas e colunas
    */
    void insert(int i, int j, double value) {
        if (i > linhas || i < 1 || j > colunas || j < 1) {
            throw out_of_range("Índices inválidos");
        }

        if (value == 0) {
            return;
        }

        Node* auxLinha = m_headLinha;
        // Acha a linha anterior á linha que queremos
        while(auxLinha->abaixo != m_headLinha && auxLinha->abaixo->linha < i) {
            auxLinha = auxLinha->abaixo;
        }

        if(auxLinha->abaixo != m_headLinha && auxLinha->abaixo->linha == i) {
            // Caso em que já existia uma linha: avanço pra ela
            auxLinha = auxLinha->abaixo;
        } else {// Se nao existia a linha, criamos ela
            Node* novoL = new Node(i, 0, 0);
            // Insere nó na lista de m_headLinhas 
            novoL->abaixo = auxLinha->abaixo;// Aponta pro próximo abaixo
            auxLinha->abaixo = novoL;// O anterior aponta pra ele 
            auxLinha = novoL;// Aux representa a nova linha
            auxLinha->direita = auxLinha;//Aponta pra ele mesmo pois ainda nao tem as colunas
        }

        Node* auxColuna = auxLinha;// Começa na linha que encontrei
        // Enquanto nao chegamos no ultimo elemento e indice do elemento for menor que J
        // Encontra a coluna anterior
        while(auxColuna->direita != auxLinha && auxColuna->direita->coluna < j) {
            auxColuna = auxColuna->direita;
        }
        // Caso em que a coluna ja existe 
        if(auxColuna->direita != auxLinha && auxColuna->direita->coluna == j) {
            auxColuna->direita->value = value;
        } else {// Caso em que crio a coluna
            Node* novoC = new Node(i, j, value);// Novo nó com valores passados
            novoC->direita = auxColuna->direita;// Aponta pro proximo
            auxColuna->direita = novoC; // O anterior aponta pra ele
        }
    }

    double get(int i, int j) {
        if(i < 1 || i > linhas || j < 1 || j > colunas){
            throw out_of_range("Índices inválidos");
        }
        
        Node* linhaAtual = m_headLinha;
        // Encontro a linha anterior a que foi passada como parâmetro
        while(linhaAtual -> abaixo != m_headLinha && linhaAtual -> abaixo -> linha < i){
            // Chego na linha anterior a que quero
            linhaAtual = linhaAtual -> abaixo;
        }

        if(linhaAtual -> abaixo == m_headLinha || linhaAtual -> abaixo -> linha != i) {
            // Caso em que linha nao existe
            return 0.0;
        }
        // Se linha existe, vou pra ela
        linhaAtual = linhaAtual -> abaixo;

        // Inicializo na linha anterior e na primeira coluna que ele aponta
        Node* aux = linhaAtual -> direita;
        // Encontro a coluna anterior a que foi passada como parametro
        while (aux != linhaAtual && aux -> coluna < j) {
            // Coluna anterior a que quero
            aux = aux -> direita;
        }

        // Se coluna existe, retorno o valor do elemento nela 
        if (aux != linhaAtual && aux -> coluna == j) {
            return aux -> value;
        }
        // Se nao existe retorno 0.0
        return 0.0;

    }
    
    // Esse imprime a matriz pegando os valores pelo get reconhecendo casos em que existe 0
    void print() {
        for(int i = 1; i <= linhas; i++) {
            for(int j = 1; j <= colunas; j++) {
                cout << get(i, j) << " ";
            }
            cout << endl;
        }
    }

    void clear() {
    // Apaga os elementos das linhas
    Node* linhaAtual = m_headLinha->abaixo;

    while (linhaAtual != m_headLinha) {
        Node* atual = linhaAtual->direita;
        
        // Apaga todos os nós na linha
        while (atual != linhaAtual) {
            Node* aux = atual;
            atual = atual->direita;
            delete aux;
        }
        
        Node* auxLinha = linhaAtual;
        linhaAtual = linhaAtual->abaixo;
        delete auxLinha;
    }

    // Apaga os elementos das colunas
    Node* colunaAtual = m_headColuna->direita;
    while (colunaAtual != m_headColuna) {
        Node* aux = colunaAtual;
        colunaAtual = colunaAtual->direita;
        delete aux;
    }

    // Apaga os cabeçalhos
    delete m_headLinha;
    delete m_headColuna;

    // Atualiza os índices para 0
    linhas = 0;
    colunas = 0;

    cout << "Matriz destruida" << endl;
}


    // Esses métodos são opcionais
    // Criei apenas caso a gente precise (consequências do Java)
    int getLinhas() const {
        return linhas;
    }

    int getColunas() const {
        return colunas;
    }

    Node* getHeadLinha() const {
        return m_headLinha;
    }

    Node* getHeadColuna() const {
        return m_headColuna;
    }

};

#endif