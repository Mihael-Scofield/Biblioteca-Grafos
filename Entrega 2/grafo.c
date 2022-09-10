/* MIHAEL SCOFIELD DE AZEVEDO - GRR20182621 - MSA18 */

#include <stdio.h>
#include "grafo.h"

int topoStack = 0;

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
    // vertice *vertices;
    // vertices = agfstnode(g);
    // vertices = agnxtnode(g, vertices);

    if (n_arestas(g) - 1 == grau_medio(g)) { // Verifica se o grafo eh um Kn
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
  int **matrizAdjacente, *cores, tamanho;
  tamanho = n_vertices(g);
  matrizAdjacente = matriz_adjacencia(g);
  cores = malloc(((unsigned int) tamanho) * sizeof(int));

  for(int i = 0; i < tamanho; i++)
      cores[i] = -1;
        
  int pos = 0;
  return colore(matrizAdjacente, cores, tamanho, pos, 1);
    
  return 0;
}

// -----------------------------------------------------------------------------
int n_triangulos(grafo g) {
  int **matrizAdjacencia, **matAux, **matMult, size;
  unsigned int u_size;
  
  size = n_vertices(g);
  matrizAdjacencia = matriz_adjacencia(g);
  u_size = (unsigned int) size;

  // Inicia as matrizes auxiliares e "seta" seus ponteiros
  matAux = malloc(u_size*sizeof(int*) + u_size*u_size*sizeof(int));
  matMult = malloc(u_size*sizeof(int*) + u_size*u_size*sizeof(int));

  matAux[0] = (int*) (matAux + size);
  for (int i=1; i < size; i++)      
    matAux[i] = matAux[0] + (i * size);

  matMult[0] = (int*) (matMult + size);
  for (int i=1; i < size; i++)
    matMult[i] = matMult[0] + (i * size);

  // Copia elementos da matriz de adjacencia para a auxiliar 
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      matAux[i][j] = matrizAdjacencia[i][j];

  // Eleva a matriz de adjacencia a 2 potencia
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      for (int k = 0; k < size; k++)
        matMult[i][j] += matrizAdjacencia[i][k]*matAux[k][j];

  // Eleva a matriz de adjacencia a 3 potencia
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      for (int k = 0; k < size; k++)
        matAux[i][j] += matMult[i][k]*matrizAdjacencia[k][j];
        
  // Calculo do Trace
  int trace = 0;
  for (int i = 0; i < size; i++)
    trace += matAux[i][i];
  
  // Liberacao de memorias
  free(matAux);
  free(matMult);
  free(matrizAdjacencia);
  
  return trace/6;
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
  grafo grafoAux;
  grafoAux = agopen(FALSE, Agundirected, NULL);

  // Copia os vertices de g em grafoAux
  for (vertice v = agfstnode(g); v; v = agnxtnode(g,v)){
    agnode(grafoAux,agnameof(v),TRUE);
  }
  
  // Faz o complemento
  for (vertice vi = agfstnode(g); vi; vi = agnxtnode(g,vi)){
    for (vertice vj = agfstnode(g); vj; vj = agnxtnode(g,vj)){
      Agedge_t *a1 = agedge(g, vi, vj, NULL, FALSE);
      Agedge_t *a2 = agedge(grafoAux, agnode(grafoAux, agnameof(vi), FALSE), agnode(grafoAux, agnameof(vj), FALSE), NULL, FALSE);
      if (a1 == NULL && a2 == NULL && vi != vj) { // Cria uma aresta no grafo auxiliar se ela nao existia no original
        agedge(grafoAux, agnode(grafoAux, agnameof(vi), FALSE), agnode(grafoAux, agnameof(vj), FALSE), NULL, TRUE);
      }
    }
  }

  return grafoAux;
}

// Funcao que decompoe o Grafo, isto eh, retira seus componentes fortes
// A estrategia aboradada para tal foi o algoritmo de Kosaraju, um algoritmo divido em 3 partes.
grafo decompoe(grafo g) {
  int nVertices = n_vertices(g);

  // Pilha de vertices
  int *stack = malloc(nVertices * sizeof(int));
  for (int i = 0; i < nVertices; i++) {
    stack[i] = 0;
  }

  // Vetores visitados para apoio do algoritmo de Kosaraju
  int *visitados = malloc(nVertices * sizeof(int));
  for (int i = 0; i < nVertices; i++) {
    visitados[i] = 0;
  }

  // Matriz Adjacencia para a busca em profundidade
  int **matrizAdjacencia = matriz_adjacencia(g);

  // Passo 1: Busca em Profundidade, marcando todos os vetores visitados e os empilhando
  // conforme encontra becos sem saida
  for (int i = 0; i < nVertices; i++) {
    if (visitados[i] == 0) {
      buscaEmProfundidade(matrizAdjacencia, i, nVertices, visitados, stack);
    }
  }

  // Passo 2: Teriamos que criar a transposta, mas como temos a Matriz Adjacencia, basta inverter
  // A maneira que a acessamos

  // Reinicia marcacao de visitados para segunda busca
  for (int i = 0; i < nVertices; i++) {
    visitados[i] = 0;
  }

  // Passo 3: Realiza a busca na ordem das definida pela pilha de becos sem saida
  while(topoStack != 0) {
    int raiz = stack[topoStack];
    stackPop(stack);

    if(visitados[raiz] == 0) {
      buscaEmProfundidadeTransposta(matrizAdjacencia, raiz, nVertices, visitados);
      printf("\n");
    }
  }
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

// Funcao Auxiliar de Bipartido
int colore(int **matrizAdjacente, int cores[], int tamanho, int pos, int c) {
  if(cores[pos] != -1 && cores[pos] !=c) {
    return 0;
  }
         
  cores[pos] = c;
  int ans = 1;

  for(int i=0;i<tamanho;i++){
      if(matrizAdjacente[pos][i]){
        if(cores[i] == -1)
          ans &= colore(matrizAdjacente,cores,tamanho,i,1-c);
        if(cores[i] !=-1 && cores[i] != 1-c)
          return 0;
      }
      if (!ans) {
        return 0;
      }
  }
   
  return 1;
}

void buscaEmProfundidade(int** matrizAdjacencia, int raiz, int nVertices, int *visitados, int *stack) {
  // Marca o vertice atual como visitado
  if (visitados[raiz] == 0) {
    visitados[raiz] = 1;

    // Visita os vertices adjacentes
    for (int i = 0; i < nVertices; i++) {
      if (matrizAdjacencia[raiz][i] == 1) {
       buscaEmProfundidade(matrizAdjacencia, i, nVertices, visitados, stack);
      }
    }

    // Todos os vertices alcancaveis a partir dele foram processados, agora o empilhamos
    stackPush(raiz, stack);
   }
}

void buscaEmProfundidadeTransposta(int** matrizAdjacencia, int raiz, int nVertices, int *visitados) {
  if (visitados[raiz] == 0) {
    // Marca o vertice atual como visitado
    visitados[raiz] = 1;
    printf("%d ", raiz);
  
    // Visita os vertices adjacentes
    for (int i = 0; i < nVertices; i++) {
      if (matrizAdjacencia[i][raiz] == 1) {
        buscaEmProfundidadeTransposta(matrizAdjacencia, i, nVertices, visitados);
      }
    }
  }
}

void stackPush(int elemento, int* stack) {
  topoStack += 1;
  stack[topoStack] = elemento;
}

void stackPop(int* stack) {
  stack[topoStack] = NULL;
  topoStack -= 1;
}