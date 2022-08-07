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
  int **matrizAdjacencia = matriz_adjacencia(g);
  int tamanho = n_vertices(g);
  int *visitados = (int *) malloc(tamanho * sizeof(int));

  int numeroComponentes = 0;
  
  // Nosso vetor de vistidados deve iniciar zerado
  for(int i = 0; i < tamanho; i++) {
    visitados[i] = 0;
  }

  // Agora, basta visitar os vertices adjacentes
  for (int i = 0; i < tamanho; i++) {
    if (visitados[i] == 0) {
      buscaConexo(i, tamanho, visitados, matrizAdjacencia);
      numeroComponentes++;
    }

    // Liberacao de Malloc
    free(visitados);
    free(matrizAdjacencia);

    return numeroComponentes;
  }

  
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
  // para grafos nao direcionados somente
  vertice u, v;
  unsigned int i, j;
  unsigned int tamanho = (unsigned int) n_vertices(g);

  int **matrizAdjacente;
  matrizAdjacente = malloc(tamanho*sizeof(int*) + tamanho*tamanho*sizeof(int));
  if(!matrizAdjacente) 
    return NULL;
  matrizAdjacente[0] = (int*) (matrizAdjacente + tamanho) ;  // ajusta o ponteiro da primeira linha
  for (i=1; i < tamanho; i++)      // ajusta os ponteiros das demais linhas (i > 0)
    matrizAdjacente[i] = matrizAdjacente[0] + (i * tamanho) ;// pra facil indexacao & somente free(ma)


  // ma[i][j] = 0, se nao existe aresta {i, j}
  // ma[i][j] = 1, se existe aresta {i, j}
  for(i = 0, u = agfstnode(g); u; u = agnxtnode(g, u), i++){
    for(j = 0, v = agfstnode(g); v; v = agnxtnode(g, v), j++){
      // se {u, v} sao nodos diferentes e exite aresta
      if(i != j && agedge(g, u, v, NULL, 0) != NULL)
        matrizAdjacente[i][j] = 1;
      else 
        matrizAdjacente[i][j] = 0;
    }
  }

  return matrizAdjacente;
}

// -----------------------------------------------------------------------------
grafo complemento(grafo g) {
  
  return NULL;
}


//------------------------------------------------------------------------------
// FUNÇÕES IMPLEMENTADAS POR MIM // 

// Funcao Auxiliar de Conexo
void buscaConexo(int i, int tamanho, int *visitados, int **matrizAdjacencia) {
  visitados[i] = 1; // Conseguiu visitar

  // Agora caminha por entre os vertices de h, entra no vertice de cada aresta
  for (int j = 0; j < tamanho; j++) {
    if((matrizAdjacencia[i][j] == 1) && (!visitados[j])) {
      buscaConexo(j, tamanho, visitados, matrizAdjacencia);
    }
  }
}


