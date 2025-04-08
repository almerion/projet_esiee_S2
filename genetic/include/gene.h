#ifndef __GENE__
#define __GENE__
#include "adress.h"

#define MIN_PHARMACY_CAR_RATIO 10
#define MAX_PHARMACY_CAR_RATIO 20
#define MIN_CAR 2

typedef struct {
    adress_node* start_adress;
} Gene;

Gene* create_genes(int nb_genes);
void free_genes(Gene* genes, int nb_genes);
int get_random_nb_genes(Matrix m);

#endif 