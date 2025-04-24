#include <stdio.h>
#include <stdlib.h>
#include "../include/genetic.h"

int evolve_population(Matrix m, Population* population) {
    int last_father = (population->population_size * PERCENT_FATHER) / 100;
    int start_children = (population->population_size * PERCENT_KEPT) / 100;
    int start_new = (population->population_size * PERCENT_NEW) / 100;
    int nb_pharmacies = m.size - 1;
    int i, p1, p2;

    /* Mutations on best individuals */
    for (i=start_children/2 ; i<start_children ; i++){
        int* individual = individual_to_list(&population->individuals[i], nb_pharmacies);
        if(individual == NULL) {
            return 0;
        }
        mutate(individual, nb_pharmacies);
        list_to_individual(individual, m, &population->individuals[i]);
        free(individual);

        population->individuals[i].fitness = evaluateFitness(m, population->individuals[i]);
    }

    /* Children time */
    for (i=start_children ; i<start_new ; i++){
        p1 = rand() % last_father;
        while (p1 == i)
            p1 = rand() % last_father;
        p2 = rand() % population->population_size;
        while (p2 == i || p2 == p1)
            p2 = rand() % population->population_size;

        int* father = individual_to_list(&population->individuals[p1], nb_pharmacies);
        if (father == NULL) {
            return 0;
        }

        int* mother = individual_to_list(&population->individuals[p2], nb_pharmacies);
        if (mother == NULL) {
            free(father);
            return 0;
        }

        int* children = (int*) malloc(sizeof(int) * nb_pharmacies);
        if (children == NULL) {
            fprintf(stderr, "Error, couldn't allocate memory for children list");
            free(father);
            free(mother);
            return 0;
        }

        crossover(father, mother, nb_pharmacies, children);
        list_to_individual(children, m, &population->individuals[i]);
        free(father);
        free(mother);
        free(children);

        population->individuals[i].fitness = evaluateFitness(m, population->individuals[i]);
    }

    for (i=start_new ; i<population->population_size ; i++){
        free_genes(population->individuals[i].gene, population->individuals[i].nbGenes);
        int nb_genes = get_random_nb_genes(m);
        init_random_individual(m, &population->individuals[i], nb_genes);
        population->individuals[i].fitness = evaluateFitness(m, population->individuals[i]);
    }

    sort_population(population);
    return 1;
}

void sort_population(Population* population){
    int i;
    qsort(population->individuals, population->population_size, sizeof(Individual), cmp_individual);

    for (i=0 ; i<population->population_size ; i++){
        printf("%f\n", population->individuals[i].fitness);
    }
}

void crossover(int* father, int* mother, int size, int* child) {
    int start = rand() % size;
    int end   = rand() % size;
    if(start > end){
        int tmp = start;
        start = end;
        end = tmp;
    }

    for(int i=0; i<size; i++){
        child[i] = -1;
    }

    for(int i=start; i<=end; i++){
        child[i] = father[i];
    }

    int currentPos = (end+1) % size; 

    for(int i=0; i<size; i++){
        int candidate = mother[i];
        
        int alreadyIn = 0;
        for(int c=start; c<=end; c++){
            if(child[c] == candidate){
                alreadyIn = 1;
                break;
            }
        }
        if(!alreadyIn){
            while(child[currentPos] != -1){
                currentPos = (currentPos+1) % size;
            }
            child[currentPos] = candidate;
        }
    }
}

void mutate(int* individual, int size) {
    /*rate of a mutation of happen*/
    if (rand() % MUTATION_RATE != 0) {
        return;
    }

    int i;
    /*The individual will have a certain percentage of its genome modified by random swaps*/
    int numberOfSwaps = (MUTATION_PERCENTAGE_SWAPS * size) / 200;
    if (numberOfSwaps < MUTATION_MIN_NB_SWAPS) {
        numberOfSwaps = MUTATION_MIN_NB_SWAPS;
    }
    for(i = 0; i < numberOfSwaps; i++) {
        int from = rand() % size;
        int to = rand() % size;

        int tmp = individual[from];
        individual[from] = individual[to];
        individual[to] = tmp;
    }
}
