
#include "../include/path.h"

#define LIMIT_TIME 180

double evaluateFitness(Matrix matrix,lst adrs); // Tiago

Path generatePath(Matrix matrix,lst startAdr){
    
}; //Ethan

Path* initPaths(Matrix matrix,int nbPaths); // Tiago

int checkPaths(Path* path,int nbPaths); // Ethan

Path crossover(Path path1,Path path2); // Tiago

void mutate(Path* path); // Ethan