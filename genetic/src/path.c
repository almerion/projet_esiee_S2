
#include "../include/path.h"

#define LIMIT_TIME 180

double evaluateFitness(Matrix matrix,adress* adrs); // Tiago

Path generatePath(Matrix matrix,int* avoidAdressIndexes,int startIndex,int endIndex){
    int i,j;
    Path path = {NULL,NULL,0,0};
    adress* adr = create_adress(startIndex);
    int isValid=0;
    path.first = adr;
    path.last = adr;


    for(i = 1; i < matrix.size;i++){
        int newIndex = 1+rand()%(matrix.size-1);
        for(j = 0;avoidAdressIndexes[j]!= -1;j++){
            if(newIndex == avoidAdressIndexes[j]){
                isValid=1;
                break;
            }
        }
        if(isValid == 1){
            isValid=0;
            continue;
        }
        if(path.fullTime+matrix.matrix[newIndex][path.last->pharmacyIndex].time < LIMIT_TIME){
            adress* new = create_adress(i);
            insert_adress(path.first,new);
            path.last = new;
            path.fullTime += matrix.matrix[newIndex][path.last->pharmacyIndex].time;
        }
        else{
            continue;
        }
    }
    while(path.fullTime+matrix.matrix[path.last->pharmacyIndex][endIndex].time > LIMIT_TIME){
        adress* newLast = pop_adress(path.first);
        path.last = newLast;
    }
    adress* end = create_adress(endIndex);
    insert_adress(path.first,end);
    path.fullTime = path.fullTime+matrix.matrix[path.last->pharmacyIndex][endIndex].time;
    path.last=end;

    return path;
}; //Ethan

Path* initPaths(Matrix matrix,int nbPaths); // Tiago

int checkPaths(Path* path,int nbPaths); // Ethan

Path crossover(Path path1,Path path2); // Tiago

void mutate(Path* path); // Ethan