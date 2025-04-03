
#include "../include/path.h"

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

void sortPaths(Path* path,int nbPaths); // Ethan

Path crossover(Path path1,Path path2); // Tiago

void mutate(Path* path); // Ethan