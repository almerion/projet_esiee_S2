#include "adress.h"
#include <stdlib.h>
#include <stdio.h>

adress_node* create_adress(int pharmacyIndex) {
    adress_node* new_adress = (adress_node *) malloc(sizeof(adress_node));
    if (new_adress == NULL) {
        fprintf(stderr, "Couldn't allocate memory for a new adress");
        return NULL;
    }
    new_adress->pharmacyIndex = pharmacyIndex;
    new_adress->prev = NULL;
    new_adress->next = NULL;

    return new_adress;
}

adress_node* create_and_insert_after(adress_node* prev, int pharmacyIndex) {
    if (prev == NULL) return NULL;

    adress_node * new_adress = create_adress(pharmacyIndex);

    if (new_adress == NULL) return NULL;
    
    new_adress->next = prev->next;
    if (prev->next != NULL) {
        prev->next->prev = new_adress;
    }
    prev->next = new_adress;
    new_adress->prev = prev;
    return new_adress;
}

adress_node* create_and_insert_before(adress_node* next, int pharmacyIndex) {
    adress_node * new_adress = create_adress(pharmacyIndex);
    if (new_adress == NULL) return NULL;
    if (next == NULL) return new_adress;

    if (next->prev == NULL) {
        next->prev = new_adress;
    } else {
        adress_node* tmp = next->prev;
        if(tmp != NULL) {
            tmp->next = new_adress;
        }
        new_adress->prev = next->prev;
        next->prev = new_adress;
        new_adress->next = next;
    }

    return new_adress;
}


void free_adresses(adress_node* adress) {
    adress_node* tmp = adress;
    if (tmp != NULL) {
        tmp->prev->next = NULL;
    }
    while (tmp != NULL) {
        tmp = adress->next;
        free(adress);
        adress = tmp;
    }
}

int* individual_to_list(Individual* ind, int matrixSize) {
    if (matrixSize < 3) {
        return NULL;
    }

    /*matrix size -1 car on compte pas la permière ligne qui est le dépot*/
    int* result = (int *) malloc(sizeof(int) * matrixSize - 1);
    int idx = 0;
    int gIndex;

    for(gIndex = 0; gIndex < ind->nbGenes; gIndex++){
        adress_node* cur = ind->gene[gIndex].startAdr;
        while(cur){
            result[idx++] = cur->pharmacyIndex;
            cur = cur->next;
        }
    }

    return result;
}

Individual* list_to_individual(int* list, Matrix *m, Individual* individual) {
    int i;
    for(i = 0; i < individual->nbGenes; i++) {
        free_adresses(individual->gene[i].startAdr);
        individual->gene[i].startAdr = NULL;
    }
    
    int real_matrix_size = m->size - 1;
    
    int geneIndex = 0;
    /* coulc calculate the fitness here at the same time ? */
    while (i < real_matrix_size) {
        int from = 0;
        int currentTime = 0;

        while(i < real_matrix_size) {
            int to = list[i];
            Distime dt = m->matrix[from][to];

            int newTime = currentTime + dt.time;
            newTime += SERVICE_TIME;
            Distime dtBack = m->matrix[to][0];
            newTime += dtBack.time;

            if(newTime <= LIMIT_TIME){
                if(individual->gene[geneIndex].startAdr == NULL) {
                    individual->gene[geneIndex].startAdr = create_adress(to);
                } else {
                    /* replace by a function or struct that points to first and last*/
                    adress_node* last = individual->gene[geneIndex].startAdr;
                    while(last->next) { 
                        last = last->next;
                    }
                    create_and_insert_after(last, to);
                }
                currentTime = newTime;
                from = to;
                i++;
            }else {
                break;
            }
        }

        if (i < real_matrix_size) geneIndex++;
    }
    individual->nbGenes = geneIndex;

    return individual;
}