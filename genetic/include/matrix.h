#ifndef __MATRIX__
#define __MATRIX__

typedef struct distime{
    float dist;
    int time;
}Distime,*Distimes;

typedef struct matrix {
    Distimes* matrix;
    int size; 
}Matrix;

void displayMatrix(Matrix matrix);

#endif