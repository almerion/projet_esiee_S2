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