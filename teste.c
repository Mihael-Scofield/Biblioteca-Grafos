/* MIHAEL SCOFIELD DE AZEVEDO - GRR20182621 - MSA18 */

#include <stdio.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void) {

  grafo g = le_grafo();

  //escreve_grafo(g);
  int n = n_vertices(g);
  printf("\n %d \n", n);
  
  destroi_grafo(g);

  return 0;
}
