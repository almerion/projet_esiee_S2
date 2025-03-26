#ifndef __PATH__
#define __PATH__

#include "matrix.h"


typedef struct path
{
    int* adrs; 
    double fitness;
    float fullTime; 

}Path;

double evaluateFitness(Matrix matrix,int* adrs);

Path generatePath(Matrix matrix,Path* paths,int startIndex,int endIndex,int nbVan);

Path* initPaths(Matrix matrix,int nbVan);

int checkPaths(Path* path,int nbVan);

Path crossover(Path path1,Path path2);



#endif