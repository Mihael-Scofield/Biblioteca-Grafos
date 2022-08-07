/* MIHAEL SCOFIELD DE AZEVEDO - GRR20182621 - MSA18 */

#ifndef _GRAFO_H
#define _GRAFO_H

#include <graphviz/cgraph.h>

//------------------------------------------------------------------------------
typedef Agraph_t *grafo;
typedef Agnode_t *vertice;

// FUNCIONA -----------------------------------------------------------------------------
// devolve o grafo lido da entrada padrão (formato dot)


grafo le_grafo(void);

// FUNCIONA -----------------------------------------------------------------------------
// desaloca g

void destroi_grafo(grafo g);

// FUNCIONA -----------------------------------------------------------------------------
// escreve g na saída padrão em formato dot
// devolve g

grafo escreve_grafo(grafo g);

// FUNCIONA -----------------------------------------------------------------------------
// devolve o número de vértices de g

int n_vertices(grafo g);


// FUNCIONA -----------------------------------------------------------------------------
// devolve o número de arestas do grafo

int n_arestas(grafo g);


// FUNCIONA -----------------------------------------------------------------------------
// devolve o grau do vértice v em g

int grau(vertice v, grafo g);

// FUNCIONA -----------------------------------------------------------------------------
// devolve o grau máximo de g

int grau_maximo(grafo g);

// FUNCIONA -----------------------------------------------------------------------------
// devolve o grau mínimo de g

int grau_minimo(grafo g);

// FUNCIONA -----------------------------------------------------------------------------
// devolve o grau médio de g

int grau_medio(grafo g);

// FUNCIONA ------------------------------------------------------------------------------
// devolve 1 se g é regular, ou 0 caso contrário

int regular(grafo g);

// FUNCIONA ------------------------------------------------------------------------------
// devolve 1 se g é completo, ou 0 caso contrário

int completo(grafo g);

// FUNCIONA ------------------------------------------------------------------------------
// devolve 1 se g é conexo, ou 0 caso contrário

int conexo(grafo g);

//------------------------------------------------------------------------------
// devolve 1 se g é bipartido, ou 0 caso contrário

int bipartido(grafo g);

// FUNCIONA ------------------------------------------------------------------------------
// devolve o número de triângulos (subgrafos completos de 3 vértices) em g

int n_triangulos(grafo g);

// FUNCIONA ------------------------------------------------------------------------------
// devolve uma matriz de adjacência de g onde as linhas/colunas
// estão ordenadas do mesmo modo que agfstnode() e agnxtnode()
// em libcgraph

int **matriz_adjacencia(grafo g);

//------------------------------------------------------------------------------
// devolve o grafo complementar a g

grafo complemento(grafo g);


//------------------------------------------------------------------------------
// FUNÇÕES IMPLEMENTADAS POR MIM
// Funcao Auxiliar de Conexo
void buscaConexo(int i, int tamanho, int *visitados, int **matrizAdjacencia);

#endif
