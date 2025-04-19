#ifndef __GENETIC__
#define __GENETIC__
#include "population.h"

#define PERCENT_KEPT 25    /* Est ce qu'on en garde trop ? */
#define PERCENT_FATHER 50  /* Faut-il plus accompler uniquement les meilleurs ? */
#define PERCENT_NEW 50     /* Un inidividu aléatoire ne peut plus rivaliser avec un déjà un peu optimiser */
#define MUTATION_RATE 16
#define MUTATION_PERCENTAGE_SWAPS 20
#define MUTATION_MIN_NB_SWAPS 1

int evolve_population(Matrix m, Population* population);
void crossover(int* father, int* mother, int size, int* child);
void mutate(int* individual, int size);

#endif