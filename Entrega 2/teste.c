/* MIHAEL SCOFIELD DE AZEVEDO - GRR20182621 - MSA18 */

#include <stdio.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void) {

  grafo g = le_grafo();

  decompoe(g);
  int i = 1;


  for (grafo subG = agfstsubg(g); subG; subG = agnxtsubg(subG)) {
    printf("Printando o componente forte %d: \n", i);
    escreve_grafo(subG);
    i++;
  }

  // Liberacao de memoria
  destroi_grafo(g);

  return 0;
}
