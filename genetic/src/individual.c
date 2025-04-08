#include <stdio.h>
#include <stdlib.h>
#include "individual.h"

Individual* create_individuals(int nb_individuals) {
    if (nb_individuals < 1) {
        fprintf(stderr, "Error, cannor allocate memory for %d individuals", nb_individuals);
        return NULL;
    }
    
    Individual* individuals = (Individual*) malloc(sizeof(Individual) * nb_individuals);
    if (individuals == NULL) {
        fprintf(stderr, "Error, couldn't allocate memory for individuals");
        return NULL;
    }

    int i;
    for(i = 0; i < nb_individuals; i ++) {
        individuals[i].nbGenes = 0;
        individuals[i].gene = NULL;
    }

    return individuals;
}

void free_individuals(Individual* individuals, int nb_individuals) {
    if(nb_individuals < 1) {
        fprintf(stderr, "Can't free %d individuals", nb_individuals);
        return;
    }

    int i;
    for(i = 0; i < nb_individuals; i ++) {
        if(individuals[i].gene != NULL) {
            free_genes(individuals[i].gene, individuals[i].nbGenes);
        }
    }
    free(individuals);
}

int init_random_individual(Matrix m, Individual* individual, int nb_genes) {
    int i;
    individual->nbGenes = nb_genes;
    individual->gene = create_genes(nb_genes);
    
    if(individual->gene == NULL) {
        return 0;
    }

    for (i=1; i < m.size; i++){
        Gene *selected_car = &individual->gene[rand() % nb_genes];
        adress_node* node = create_and_insert_before(selected_car->start_adress, i);

        if(node == NULL) {
            free_genes(individual->gene, nb_genes);
            return 0;
        }
        selected_car->start_adress = create_and_insert_before(selected_car->start_adress, i);
    }
    return 1;
}

double evaluateFitness(Matrix matrix, Individual individual){
    Distime total = {0, 0};
    int i;
    for(i = 0; i < individual.nbGenes; i++) {
        Gene current = individual.gene[i];
        adress_node *current_adress = current.start_adress;
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
        total.time += SERVICE_TIME;
    }

    return total.dist;
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

int* individual_to_list(Individual* ind, int size) {
    if (size < 2) {
        return NULL;
    }

    int* result = (int *) malloc(sizeof(int) * size);
    if (result == NULL) {
        fprintf(stderr, "Error, couldn't allocate memory for individual to list");
        return NULL;
    }

    int idx = 0;
    int gIndex;

    for(gIndex = 0; gIndex < ind->nbGenes; gIndex++){
        adress_node* cur = ind->gene[gIndex].start_adress;
        while(cur){
            result[idx++] = cur->pharmacyIndex;
            cur = cur->next;
        }
    }

    return result;
}

void list_to_individual(int* list, Matrix m, Individual* individual) {
    int i;
    for(i = 0; i < individual->nbGenes; i++) {
        free_adresses(individual->gene[i].start_adress);
        individual->gene[i].start_adress = NULL;
    }
    
    int real_matrix_size = m.size - 1;
    
    int gene_index = 0;
    /* could calculate the fitness here at the same time ? */
    while (i < real_matrix_size) {
        int from = 0;
        int current_time = 0;

        while(i < real_matrix_size) {
            int to = list[i];
            Distime dt = m.matrix[from][to];

            int new_time = current_time + dt.time;
            new_time += SERVICE_TIME;
            Distime dtBack = m.matrix[to][0];
            new_time += dtBack.time;

            if(new_time <= LIMIT_TIME){
                if(individual->gene[gene_index].start_adress == NULL) {
                    individual->gene[gene_index].start_adress = create_adress(to);
                } else {
                    /* replace by a function or struct that points to first and last*/
                    adress_node* last = individual->gene[gene_index].start_adress;
                    while(last->next != NULL) { 
                        last = last->next;
                    }
                    create_and_insert_after(last, to);
                }
                current_time = new_time;
                from = to;
                i++;
            }else {
                break;
            }
        }

        if (i < real_matrix_size) gene_index++;
    }
    individual->nbGenes = gene_index;
}