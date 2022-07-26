/* MIHAEL SCOFIELD DE AZEVEDO - GRR20182621 - MSA18 */

#include <stdio.h>
#include "grafo.h"

//------------------------------------------------------------------------------
grafo le_grafo(void) { 
  return agread(stdin, NULL); 
}
//------------------------------------------------------------------------------
void destroi_grafo(grafo g) { 
  agfree(g, NULL);
  return 1;
}
//------------------------------------------------------------------------------
grafo escreve_grafo(grafo g) {
  return agwrite(g, stdout);
}

// -----------------------------------------------------------------------------
int n_vertices(grafo g) {
  Agnode_t  *vertice;
  int contador = 0;
  
  for (vertice = agfstnode(g); vertice; vertice = agnxtnode(g, vertice)) {
    contador++;
  }

  return contador;
}

// -----------------------------------------------------------------------------
int n_arestas(grafo g) {
  Agnode_t  *vertice;
  Agedge_t  *aresta;
  int contador = 0;

  for (vertice = agfstnode(g); vertice; vertice = agnxtnode(g, vertice)) {
    for (aresta = agfstedge(g, vertice); aresta; aresta = agnxtedge(g, aresta, vertice)) {
      contador++;
    }
  }
  return contador/2;
}

// -----------------------------------------------------------------------------
int grau(vertice v, grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
int grau_maximo(grafo g)  {
  
  return 0;
}

// -----------------------------------------------------------------------------
int grau_minimo(grafo g)  {
  
  return 0;
}

// -----------------------------------------------------------------------------
int grau_medio(grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
int regular(grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
int completo(grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
int conexo(grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
int bipartido(grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
int n_triangulos(grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
int **matriz_adjacencia(grafo g) {
  
  return NULL;
}

// -----------------------------------------------------------------------------
grafo complemento(grafo g) {
  
  return NULL;
}

