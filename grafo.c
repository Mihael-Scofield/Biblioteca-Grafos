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
// A ideia eh testar se todos os graus sao iguais
// para isso, garanti que no looping eu tenha um valor do vertice anterior e um do atual
int regular(grafo g) {
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

  return 1; // passou em todos os testes
}

// -----------------------------------------------------------------------------

int completo(grafo g) {
  // Para ser completo precisa ser regular
  if (regular(g)) {
    // Pega um vertice qualquer 
    vertice *vertices;
    vertices = agfstnode(g);
    vertices = agnxtnode(g, vertices);

    if (n_arestas(g) - 1 == grau(vertices, g)) { // Verifica se o grafo eh um Kn
      return 1; 
    }
  }
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
/* A ideia e criar uma matriz de ponteiros onde
matriz[i][j] = 0 se nao existe aresta em {i, j}
matriz[i][j] = 1 se existe aresta em {i, j} */
int **matriz_adjacencia(grafo g) {
  int tamanho = n_vertices(g);
  vertice u, v;

  // Malloca Matriz
  int **matrizAdjacencia = malloc(tamanho*sizeof(int*) + tamanho*tamanho*sizeof(int));
  if (!(matrizAdjacencia)) { // Checa se o malloc funcionou
    return NULL;
  }
  matrizAdjacencia[0] = (int *) (matrizAdjacencia + tamanho); // Ponteiro vai para primeira linha
  for (int i = 1; i < tamanho; i++) { // posiciona ponteiros nas demais i linhas
    matrizAdjacencia = matrizAdjacencia[0] + (i * tamanho); // Boa pratica de indexacao
  }

  for (int i = 0, u = agfstnode(g); u; u = agnxtnode(g, u), i++) { // necessario camianhar com o indice e o vertice
    for (int j = 0, v = agfstnode(g); v; v = agnextnode(g, v), j++) {
      if (i != j && agedge(g, u, v, NULL, 0) != NULL) { // Nao existe aresta de looping, {i, i} deve ser verificado
        matrizAdjacencia[i][j] = 1;
      }
      else {
        matrizAdjacencia[i][j] = 0;
      }
    }
  }
  
  return matrizAdjacencia;
}

// -----------------------------------------------------------------------------
grafo complemento(grafo g) {
  
  return NULL;
}

