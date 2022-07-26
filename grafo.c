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
  return agnnodes(g);
}

// -----------------------------------------------------------------------------
int n_arestas(grafo g) {
  agnedges(g);
}

// -----------------------------------------------------------------------------
int grau(vertice v, grafo g) {
  return agdegree(g, v, TRUE, TRUE);
}

// -----------------------------------------------------------------------------
int grau_maximo(grafo g)  {
  int grauMax = 0;
  int aux = 0;
  vertice *vertices;

  for (vertices = agfstnode(g); vertices; vertices = agnxtnode(g, vertices)) {
    aux = grau(vertices, g);
    if (aux >= grauMax) {
      grauMax = aux;
    }
  }
  return grauMax;
}

// -----------------------------------------------------------------------------
int grau_minimo(grafo g)  {
  int grauMin = 0;
  int aux = 0;
  vertice *vertices;

  for (vertices = agfstnode(g); vertices; vertices = agnxtnode(g, vertices)) {
    aux = grau(vertices, g);
    if (aux < grauMin || grauMin == 0) { // OR necessario para considerar o primeiro caso
      grauMin = aux;
    }
  }
  return grauMin;
}

// -----------------------------------------------------------------------------
int grau_medio(grafo g) {
  int grauMedio = 0;
  int aux = 0;
  vertice *vertices;

  for (vertices = agfstnode(g); vertices; vertices = agnxtnode(g, vertices)) {
    aux = grau(vertices, g);
    grauMedio += aux;
  }
  
  return grauMedio/n_vertices(g);
}

// -----------------------------------------------------------------------------
int regular(grafo g) {
  
  return 0;
}

// -----------------------------------------------------------------------------
// A ideia eh testar se todos os graus sao iguais
// para isso, garanti que no looping eu tenha um valor do vertice anterior e um do atual
int completo(grafo g) {
  int grauAtual = 0;
  int grauAnterior = 0;
  vertice *vertices;

  for (vertices = agfstnode(g); vertices; vertices = agnxtnode(g, vertices)) {
    grauAtual = grau(vertices, g);
    if (grauAtual != grauAnterior && grauAnterior != 0) {
      return 0;
    }
    grauAnterior = grauAtual;
  }

  if (n_arestas(g) - 1 != grauAtual) { // Verifica se o grafo eh um Kn
    return 0; 
  }
  
  return 1;
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

