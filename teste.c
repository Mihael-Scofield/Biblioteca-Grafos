/* MIHAEL SCOFIELD DE AZEVEDO - GRR20182621 - MSA18 */

#include <stdio.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void) {

  //vertice *v;
  grafo g = le_grafo();
  vertice f;

  //escreve_grafo(g);
  int n = n_triangulos(g);
  printf("\n %d \n", n);
  
  // Liberacao de memoria
  destroi_grafo(g);

  return 0;
}
