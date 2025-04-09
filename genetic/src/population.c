#include <stdio.h>
#include <stdlib.h>
#include "population.h"
#include "individual.h"

Population* create_population() {
    Population* population = (Population*) malloc(sizeof(Population));
    
    if(population == NULL) {
        fprintf(stderr, "Error, couldn't allocate memory for population");
        return NULL;
    }

    population->individuals = NULL;
    population->population_size = 0;
    
    return population;
}

int init_random_population(Matrix m, Population* population, int nb_individuals) {
    population->population_size = nb_individuals;
    population->individuals = create_individuals(nb_individuals);

    if(population->individuals == NULL) {
        return 0;
    }

    int i;
    for(i = 0; i < nb_individuals; i ++) {
        int nb_genes = get_random_nb_genes(m);
        int result = init_random_individual(m, &population->individuals[i], nb_genes);
        
        if(!result) {
            /*free all the already created individuals*/
            free_individuals(population->individuals, i);
            return 0;
        }
        population->individuals[i].fitness = evaluateFitness(m, population->individuals[i]);
    }

    return 1;
}

void free_population(Population* population) {
    free_individuals(population->individuals, population->population_size);
    free(population);
}

void print_fitnesses(Population* population) {
    int i;
    for(i = 0; i < population->population_size; i++) {
        printf("%f\n", population->individuals[i].fitness);
    }
}