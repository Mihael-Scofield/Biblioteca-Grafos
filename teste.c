/* MIHAEL SCOFIELD DE AZEVEDO - GRR20182621 - MSA18 */

#include <stdio.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void) {

  grafo g = le_grafo();


  // Testes
  /* n_vertices */
  int n = n_vertices(g);
  printf("O grafo possui: %d vertices \n", n);

  /* n_arestas */
  n = n_arestas(g);
  printf("O grafo possui: %d arestas \n", n);

  /* Grau */
  vertice *v;
  v = agfstnode(g);
  n = grau(v, g);
  printf("O grau do primeiro vertice em G eh: %d \n", n);

  /* Grau maximo */
  n = grau_maximo(g);
  printf("O grau maximo do Grafo eh: %d \n", n);

  /* Grau Minimo */
  n = grau_minimo(g);
  printf("O grau minimo do Grafo eh: %d \n", n);

  /* Grau Medio */
  n = grau_medio(g);
  printf("O grau medio do Grafo eh: %d \n", n);  

  /* Regular */
  n = regular(g);
  printf("Regular: %d \n", n);

  /* completo */
  n = completo(g);
  printf("Completo: %d \n", n);

  /* conexo */
  n = conexo(g);
  printf("Conexo: %d \n", n);

  /* bipartido */
  n = bipartido(g);
  printf("Bipartido: %d \n", n);  

  /* Triangulos */
  n = n_triangulos(g);
  printf("O Grafo possui %d triangulos \n", n);


  // TESTES COMENTADOS PARA EVITAR POLUICAO

  /* Matriz Adjacente */
  // Eh possivel verificar a corretude dessa função pois ela foi utilizada para descobrir
  // a quantidade de triangulos

  /* Complemento */
  // grafo c = complemento(g);
  // escreve_grafo(c);
  // destroi_grafo(c);
  
  // Liberacao de memoria
  destroi_grafo(g);

  return 0;
}
