#ifndef __INDIVIDUAL__
#define __INDIVIDUAL__

#include "gene.h"
#include "matrix.h"

#define LIMIT_TIME 180
#define SERVICE_TIME 3

typedef struct{
    Gene *gene;  /* The full genome */
    int nbGenes;
    long int fitness;        /* the fitness in cache */
}Individual;

Individual* create_individuals(int nb_individuals);
int init_random_individual(Matrix m, Individual* individual, int nb_genes);
int cmp_individual(const void * a, const void * b);
double evaluateFitness(Matrix matrix, Individual individual);
void list_to_individual(int* list, Matrix m, Individual* individual);
int* individual_to_list(Individual* ind, int size);
void free_individuals(Individual*, int nb_individuals);

#endif