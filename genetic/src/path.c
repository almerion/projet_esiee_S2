
#include "path.h"
#include <time.h>
#include <stdio.h>

double evaluateFitness(Matrix matrix, Individual individual){ // Tiago
    Distime total = {0, 0};
    int i;
    for(i = 0; i < individual.nbGenes; i++) {
        Gene current = individual.gene[i];
        adress_node *current_adress = current.startAdr;
        int from = 0;
        int to = 0;
        
        while (current_adress != NULL) {
            from = to;
            to = current_adress->pharmacyIndex;

            Distime current_cell = matrix.matrix[from][to];
            total.dist += current_cell.dist;
            total.time += current_cell.time;
            current_adress = current_adress->next;
        }

        from = to;
        to = 0;
        Distime current_cell = matrix.matrix[from][to];
        total.dist += current_cell.dist;
        total.time += current_cell.time;
        current_adress = current_adress->next;
    }

    return total.dist;
}

void init_random_individual(Matrix m, Individual* ind){
    srand(time(NULL));
    int i;
    for (i=1; i < m.size; i++){
        Gene *selected_car = &ind->gene[rand() % ind->nbGenes];
        selected_car->startAdr = create_and_insert_before(selected_car->startAdr, i);
    }
}

int init_random_population(Matrix m, Population* pop, int gene_size){
    int i;
    pop->ind = (Individual*)malloc(POPULATION_SIZE * sizeof(Individual));
    if (pop->ind == NULL){
        fprintf(stderr, "Couldn't allocate memory for individuals\n");
        return 0;
    }
    pop->population_size = POPULATION_SIZE;
    for (i=0 ; i<pop->population_size ; i++){
        pop->ind->nbGenes = gene_size;
        pop->ind->gene = (Gene *) malloc(sizeof(Gene) * gene_size);
        if (pop->ind->gene == NULL){
            fprintf(stderr, "Couldn't allocate memory for genes\n");
            return 0;
        }
    
        init_random_individual(m, &pop->ind[i]);
        pop->ind[i].fitness = evaluateFitness(m, pop->ind[i]);
    }
    return 1;
}

int cmp_individual(const void * a, const void * b){
    const Individual* i = (const Individual*)a;
    const Individual* j = (const Individual*)b;

    if (i->fitness < j->fitness)
        return -1;
    if (i->fitness > j->fitness)
        return 1;
    return 0;
}

void sort_population(Population* pop){
    int i;
    qsort(pop->ind, pop->population_size, sizeof(Individual), cmp_individual);

    for (i=0 ; i<pop->population_size ; i++){
        printf("%ld\n", pop->ind[i].fitness);
    }
}

void crossover(int* father, int* mother, int matrix_size, int* child) {
    int real_matrix_size = matrix_size - 1;
    int start = rand() % real_matrix_size;
    int end   = rand() % real_matrix_size;
    if(start > end){
        int tmp = start;
        start = end;
        end = tmp;
    }

    for(int i=0; i<real_matrix_size; i++){
        child[i] = -1;
    }

    for(int i=start; i<=end; i++){
        child[i] = father[i];
    }

    int currentPos = (end+1) % real_matrix_size; 

    for(int i=0; i<real_matrix_size; i++){
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
                currentPos = (currentPos+1) % real_matrix_size;
            }
            child[currentPos] = candidate;
        }
    }

}

void mutate(int* individual, int matrix_size) {
    int real_matrix_size = matrix_size - 1;
    /*rate of a mutation of happen*/
    if (rand() % MUTATION_RATE != 0) {
        return;
    }

    int i;
    /*The individual will have a certain percentage of its genome modified by random swaps with minimum 1 swap*/
    int numberOfSwaps = (MUTATION_PERCENTAGE * real_matrix_size) / 200;
    if (numberOfSwaps < 1) {
        numberOfSwaps = 1;
    }
    for(i = 0; i < numberOfSwaps; i++) {
        int from = rand() % real_matrix_size;
        int to = rand() % real_matrix_size;

        int tmp = individual[from];
        individual[from] = individual[to];
        individual[to] = tmp;
    }
}