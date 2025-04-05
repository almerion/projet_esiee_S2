
#include "../include/path.h"
#include <stdio.h> 

#define MAX_ADRESSE 85
#define LIMIT_TIME 180
double evaluateFitness(Matrix matrix,lst adrs){ // Tiago
    Distime total = {0, 0};
    
    while (adrs->next != NULL){
        int from = adrs->pharmacyIndex;
        int to = adrs->next->pharmacyIndex;

        Distime current = matrix.matrix[from][to];
        total.dist += current.dist;
        total.time += current.time;
    }

    return total.dist * (total.time > LIMIT_TIME ? 10 : 1);
}

Path generatePath(Matrix matrix,lst startAdr){
    Path path = {startAdr,0}; 
    path.fitness = evaluateFitness(matrix,startAdr);

    return path;
    
}; //Ethan

Path* initPaths(Matrix matrix,int nbPaths); // Tiago

int compare(const void* a, const void* b){
    return ((*(Path*)a).fitness - (*(Path*)b).fitness);
};
void sortPaths(Path* path,int nbPaths){    
    qsort(path,sizeof(Path),nbPaths,compare);
}; // Ethan

Path crossover(Path path1,Path path2); // Tiago
Path mutatePath(Matrix matrix,Path path){
    lst list = path.startAdr;
    int mutable = 0;
    while ( list != NULL)
    {
        if(mutable == 1 && list->next != NULL){
            int tmp = list->pharmacyIndex;
            list->pharmacyIndex = list->next->pharmacyIndex;
            list->next->pharmacyIndex = tmp;
            mutable = 0;
        }
        else {
            mutable = rand()%1;
            list = list->next;
        }

    }

    path.fitness = evaluateFitness(matrix,path.startAdr);
    return path;
    
    
    
}
void mutate(Matrix matrix,Path* path,int nbPaths){
    int pathIndex;
    for(pathIndex = 0;pathIndex<nbPaths;pathIndex++){
        path[pathIndex] = mutatePath(matrix,path[pathIndex]);
    }
}; // Ethan

void printGen(Path* path,int nbPaths){
    int i;
    for(i=0;i<nbPaths;i++){
        Path currPath = path[i];
        lst curr = currPath.startAdr;
        printf("path %d : ",i);
        while(curr->next != NULL){
            printf("%d -> ",curr->pharmacyIndex);
        }
        printf("%d\n",curr->pharmacyIndex);
        printf("fitness : %d\n\n",currPath.fitness);
    }
}