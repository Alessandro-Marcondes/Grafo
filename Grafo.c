#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definindo o tipo de dado para o peso das arestas
typedef int TIPOPESO;

// Estrutura para representar a adjacência
typedef struct adjacencia {
    int vertice;
    TIPOPESO peso;
    struct adjacencia* prox;
    bool visitado;
} ADJACENCIA;

// Estrutura para representar um vértice
typedef struct vertice {
    bool visitado;
    ADJACENCIA* cab;
} VERTICE;

// Estrutura para representar o grafo
typedef struct grafo {
    int vertices;
    int arestas;
    VERTICE* adj;
} GRAFO;

// Estrutura para representar um nó na fila
typedef struct noFila {
    int dado;
    struct noFila* prox;
} NoFila;

// Estrutura para representar a fila
typedef struct fila {
    NoFila* frente;
    NoFila* tras;
} Fila;

// Função para criar um novo grafo
GRAFO* criarGrafo(int vertices) {
    int i;
	GRAFO* grafo = (GRAFO*)malloc(sizeof(GRAFO));
    grafo->vertices = vertices;
    grafo->arestas = 0;
    grafo->adj = (VERTICE*)malloc(vertices * sizeof(VERTICE));
	
    for (i = 0; i < vertices; ++i) {
        grafo->adj[i].visitado = false;
        grafo->adj[i].cab = NULL;
    }

    return grafo;
}

// Função para criar uma nova adjacência
ADJACENCIA* criarAdjacencia(int vertice, TIPOPESO peso) {
    ADJACENCIA* novaAdjacencia = (ADJACENCIA*)malloc(sizeof(ADJACENCIA));
    novaAdjacencia->vertice = vertice;
    novaAdjacencia->peso = peso;
    novaAdjacencia->prox = NULL;
    novaAdjacencia->visitado = false;
    return novaAdjacencia;
}

// Função para adicionar uma aresta ao grafo
void adicionarAresta(GRAFO* grafo, int origem, int destino, TIPOPESO peso) {
    ADJACENCIA* novaAdjacencia = criarAdjacencia(destino, peso);
    novaAdjacencia->prox = grafo->adj[origem].cab;
    grafo->adj[origem].cab = novaAdjacencia;

    // Como o grafo é não direcionado, adicione uma aresta do destino para a origem também
    novaAdjacencia = criarAdjacencia(origem, peso);
    novaAdjacencia->prox = grafo->adj[destino].cab;
    grafo->adj[destino].cab = novaAdjacencia;

    grafo->arestas++;
}

// Função para criar uma nova instância da fila
Fila* criarFila() {
    Fila* novaFila = (Fila*)malloc(sizeof(Fila));
    novaFila->frente = NULL;
    novaFila->tras = NULL;
    return novaFila;
}

// Função para enfileirar um dado na fila
void enfileirar(Fila* fila, int dado) {
    NoFila* novoNo = (NoFila*)malloc(sizeof(NoFila));
    novoNo->dado = dado;
    novoNo->prox = NULL;

    if (fila->tras == NULL) {
        fila->frente = novoNo;
        fila->tras = novoNo;
    } else {
        fila->tras->prox = novoNo;
        fila->tras = novoNo;
    }
}

// Função para desenfileirar um dado da fila
int desenfileirar(Fila* fila) {
    if (fila->frente == NULL) {
        return -1; // Fila vazia
    }

    NoFila* temp = fila->frente;
    int dado = temp->dado;

    fila->frente = temp->prox;
    free(temp);

    if (fila->frente == NULL) {
        fila->tras = NULL;
    }

    return dado;
}

// Função para verificar se a fila está vazia
bool filaVazia(Fila* fila) {
    return (fila->frente == NULL);
}

// Função para realizar a busca em profundidade (DFS)
void BuscaEmProfundidade(GRAFO* grafo, int vertice) {
    // Marca o vértice como visitado
    grafo->adj[vertice].visitado = true;

    // Imprime o vértice visitado
    printf("Visitando vértice: %d\n", vertice);

    // Explora os vértices adjacentes não visitados de maneira recursiva
    ADJACENCIA* temp = grafo->adj[vertice].cab;
    while (temp) {
        int verticeAdjacente = temp->vertice;
        if (!grafo->adj[verticeAdjacente].visitado) {
            BuscaEmProfundidade(grafo, verticeAdjacente);
        }
        temp = temp->prox;
    }
}


void BuscaEmLargura(GRAFO* grafo, int verticeInicial) {
    Fila* fila = criarFila();

    printf("Busca em Largura a partir do vértice %d:\n", verticeInicial);

    // Marca o vértice inicial como visitado e o enfileira
    grafo->adj[verticeInicial].visitado = true;
    enfileirar(fila, verticeInicial);

    while (!filaVazia(fila)) {
        printf("Fila: ");
        NoFila* tempFila = fila->frente;
        while (tempFila) {
            printf("%d ", tempFila->dado);
            tempFila = tempFila->prox;
        }
        printf("\n");

        int verticeAtual = desenfileirar(fila);
        printf("Visitando vértice: %d\n", verticeAtual);

        ADJACENCIA* temp = grafo->adj[verticeAtual].cab;
        while (temp) {
            int verticeAdjacente = temp->vertice;
            if (!grafo->adj[verticeAdjacente].visitado) {
                grafo->adj[verticeAdjacente].visitado = true;
                enfileirar(fila, verticeAdjacente);
            }
            temp = temp->prox;
        }
    }

    free(fila);
    printf("\n");
}

// Função para imprimir o grafo
void imprimirGrafo(GRAFO* grafo) {
    int i;
	for (i = 0; i < grafo->vertices; ++i) {
        ADJACENCIA* temp = grafo->adj[i].cab;
        printf("Vértice %d: ", i);
        while (temp) {
            printf("(%d, %d) ", temp->vertice, temp->peso);
            temp = temp->prox;
        }
        printf("\n");
    }
}

int main() {
    
	printf("EXERCICIO 1\n");
	GRAFO* grafo1 = criarGrafo(15);

    adicionarAresta(grafo1, 0, 1, 0);
    adicionarAresta(grafo1, 0, 2, 0);
    adicionarAresta(grafo1, 1, 3, 0);
    adicionarAresta(grafo1, 1, 4, 0);
    adicionarAresta(grafo1, 1, 5, 0);
    adicionarAresta(grafo1, 3, 6, 0);
    adicionarAresta(grafo1, 3, 7, 0);
    adicionarAresta(grafo1, 5, 8, 0);
    adicionarAresta(grafo1, 5, 9, 0);
    adicionarAresta(grafo1, 7, 10, 0);
    adicionarAresta(grafo1, 7, 11, 0);
    adicionarAresta(grafo1, 7, 12, 0);
    adicionarAresta(grafo1, 9, 13, 0);
    adicionarAresta(grafo1, 9, 14, 0);

    printf("Representação do Grafo:\n");
    imprimirGrafo(grafo1);

    BuscaEmLargura(grafo1, 1);

	
	printf("\n\nEXERCICIO 2\n");
	GRAFO* grafo2 = criarGrafo(15);

    adicionarAresta(grafo2, 0, 1, 0);
    adicionarAresta(grafo2, 0, 2, 0);
    adicionarAresta(grafo2, 1, 3, 0);
    adicionarAresta(grafo2, 1, 4, 0);
    adicionarAresta(grafo2, 1, 5, 0);
    adicionarAresta(grafo2, 3, 6, 0);
    adicionarAresta(grafo2, 3, 7, 0);
    adicionarAresta(grafo2, 5, 8, 0);
    adicionarAresta(grafo2, 5, 9, 0);
    adicionarAresta(grafo2, 7, 10, 0);
    adicionarAresta(grafo2, 7, 11, 0);
    adicionarAresta(grafo2, 7, 12, 0);
    adicionarAresta(grafo2, 9, 13, 0);
    adicionarAresta(grafo2, 9, 14, 0);

    printf("Representação do Grafo:\n");
    imprimirGrafo(grafo2);

    
    BuscaEmProfundidade(grafo2, 0);

    return 0;
}
