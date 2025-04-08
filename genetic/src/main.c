#include "parser.h"
#include "genetic.h"
#include <stdio.h>

#define POPULATION_SIZE 32

int main(int argc, char* argv[]) {
    if(argc < 2) {
        fprintf(stderr, "You have to specify the path to a csv as argument\n");
        return 1;
    }

    Matrix* m = parse_file(argv[1]);
    if (m == NULL) {
        return 2;
    }

    Population* population = create_population();
    int result = init_random_population(*m, population, POPULATION_SIZE);
    if(!result) {
        free_matrix(m);
        return 1;
    }
    int i;
    for(i = 0; i < 2; i++) {
        result = evolve_population(*m, population);
        if(!result) {
            free_population(population);
            free_matrix(m);
            return 1;
        }
        printf("\n\n");
    }
    free_matrix(m);
    return 0;
}