/* MIHAEL SCOFIELD DE AZEVEDO - GRR20182621 - MSA18 */

/* 1° decisão do trabalho */
Na função n_arestas percebi que o looping de caminhar pelas arestas estavão contando a mesma aresta
duas vezes, portante resolvi tentar levar em consideração apenas "arestas de saída", mas a solução
falhou.

O que resolveu o problema foi dividir por 2 no final, para "cortar" as repetições.