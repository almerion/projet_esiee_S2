#ifndef __POPULATION__
#define __POPULATION__

#include "individual.h"

typedef struct{
    Individual* individuals;         /* Array of individuals */
    int population_size;     /* Size of the population */
}Population;

Population* create_population();
int init_random_population(Matrix m,Population* population, int nb_individuals);
void free_population(Population* population);
void sort_population(Population* population);
void print_fitnesses(Population* population);

#endif