#include "../include/matrix.h"
#include <stdlib.h>
#include <stdio.h>

/*if base isn't NULL, it will be used as first line of the distime matrix else it will just be initialized as default*/
Matrix* create_matrix(int size, Distime* base) {
    Matrix* matrix = (Matrix*) malloc(sizeof(Matrix));

    if(matrix == NULL) {
        fprintf(stderr, "Couldn't allocate memory for matrix\n");
        return NULL;
    }

    matrix->size = size;
    matrix->matrix = (Distime **) malloc(sizeof(Distime*) * size);

    if(matrix->matrix == NULL) {
        fprintf(stderr, "Couldn't allocate memory for array of array of distimes\n");
        return NULL;
    }

    int i = 0;
    if(base != NULL) {
        matrix->matrix[0] = base;
        i = 1;
    }
    for(; i < size; i ++) {
        matrix->matrix[i] = create_distime(size);
        if (matrix->matrix[i] == NULL) {
            return NULL;        
        }
    }

    return matrix;
}

Distime* create_distime(int size) {
    Distime* distime = (Distime *) malloc(sizeof(Distime) * size);
    if (distime == NULL) {
        fprintf(stderr, "Couldn't allocate memory for array of distimes\n");
        return NULL;        
    }
    return distime;
}

void free_matrix(Matrix* matrix) {
    int i;
    for(i = 0; i < matrix->size; i++) {
        free(matrix->matrix[i]);
    }
    free(matrix->matrix);
    free(matrix);
}

void display_matrix(Matrix* m) {
    int i,j;

    for(i = 0; i < m->size; i++) {
        for(j = 0; j < m->size; j++) {
            printf("%f|%d ", m->matrix[i][j].dist, m->matrix[i][j].time);
        }
        putc('\n', stdout);
    }
    putc('\n', stdout);
}