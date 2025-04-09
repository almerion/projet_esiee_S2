#include <stdio.h>
#include <stdlib.h>
#include "gene.h"

Gene *create_genes(int nb_genes) {
    if(nb_genes < 1) {
        fprintf(stderr, "Error, tried to allocate %d genes", nb_genes);
        return NULL;
    }

    Gene* genes = (Gene*) malloc(sizeof(Gene) * nb_genes);
    if (genes == NULL) {
        fprintf(stderr, "Error, couldn't allocate memory for gene");
        return NULL;
    }
    
    int i;
    for(i = 0; i < nb_genes; i ++) {
        genes[i].start_adress = NULL;
    }

    return genes;
}

int get_random_nb_genes(Matrix m) {
    int min_genes = (m.size * MIN_PHARMACY_CAR_RATIO) / 100;
    int max_genes = (m.size * MAX_PHARMACY_CAR_RATIO) / 100;
    int nb_genes = rand() % (max_genes - min_genes + 1) + min_genes;
    if(nb_genes < MIN_CAR) {
        nb_genes = MIN_CAR;
    }
    return nb_genes;
}

void free_genes(Gene* genes, int nb_genes) {
    if(nb_genes < 1) {
        fprintf(stderr, "Error, tried to free %d genes", nb_genes);
    }

    int i;
    for(i = 0; i < nb_genes; i++) {
        if(genes[i].start_adress != NULL) {
            free_adresses(genes[i].start_adress);
        }
    }
    free(genes);
}

void print_genes(Gene *genes, int nb_genes) {
    int i;
    for(i = 0; i < nb_genes; i++) {
        printf("G%d (", i);
        print_adresses(genes[i].start_adress);
        printf(")");
        printf("\n");
    }
}