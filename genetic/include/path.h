#ifndef __PATH__
#define __PATH__

#include <stdlib.h>
#include "adress.h"
#include "matrix.h"
/**
 * @file path.h
 * @brief Définit les structures de données pour 
 * représenter un chemin sous forme de liste chaînée d'adresses et
 * déclare les fonctions associées à la manipulation de ces chemins
 */



// Définition de la structure pour représenter un chemin
typedef struct _path
{
    adress* first;
    adress* last;
    double fitness;
    float fullTime;

}Path;

/**
 * @brief Évalue la qualité (fitness) d'un chemin donné en fonction d'une matrice de coûts.
 *
 * @param matrix La matrice représentant les distances et le temps entre les adresses.
 * @param addresses Le pointeur vers la première adresse de la liste chaînée représentant le chemin.
 * @return La valeur de fitness du chemin.
 * */
double evaluateFitness(Matrix matrix,adress* adrs);

/**
 * @brief Génère un nouveau chemin entre deux points donnés, en évitant potentiellement certaines adresses.
 *
 * @param matrix La matrice représentant les distances ou les coûts entre les adresses.
 * @param avoidAdressIndexes Un pointeur vers un tableau d'entiers contenant les index des adresses à éviter.
 * Peut être NULL si aucune adresse ne doit être évitée.
 * @param startIndex L'index de l'adresse de départ.
 * @param endIndex L'index de l'adresse d'arrivée.
 * @return Le nouveau chemin généré.
 *
 * @note Le paramètre 'avoidAdressIndexes' permet de spécifier des adresses à ne pas inclure dans le chemin généré
 * et sera modifié pour ajouter les adresses du nouveau chemin généré.
 */
Path generatePath(Matrix matrix,int* avoidAdressIndexes,int startIndex,int endIndex);

/**
 * @brief Génère un tableau de chemin avec des adresses différentes.
 *
 * @param matrix La matrice représentant les distances ou les coûts entre les adresses.
 * @param nbPaths Un entier représentant le nombre de chemin à créer
 * 
 * @return un tableau de chemin
 */
Path* initPaths(Matrix matrix,int nbPaths);

/**
 * @brief vérifie si un tableau de chemin est valide selon certains critères.
 * Le paramètre `nbPaths` pourrait représenter le nombre de chemins à vérifier ou une autre condition de validité.
 *
 * @param path Un pointeur vers le premier élément d'un tableau de structures `Path` (ou une structure de données similaire) à vérifier.
 * @param nbPaths Un entier représentant un critère de validation (la signification exacte dépend de l'implémentation).
 * @return 1 si l'ensemble des chemins sont valide, 0 sinon.
 */
int checkPaths(Path* path,int nbPaths);

/**
 * @brief Applique l'opération de croisement (crossover) entre deux chemins parents pour créer un nouveau chemin enfant.
 * Cette opération combine des parties des deux chemins parents pour explorer de nouvelles solutions.
 *
 * @param path1 La première structure `Path` représentant le premier parent.
 * @param path2 La deuxième structure `Path` représentant le deuxième parent.
 * @return Une nouvelle structure `Path` représentant le chemin enfant résultant du croisement.
 */
Path crossover(Path path1,Path path2);

/**
 * @brief Applique l'opération de mutation à un chemin donné. La mutation introduit de petites modifications
 * aléatoires dans le chemin pour augmenter la diversité de la population et éviter de rester bloqué
 * dans des optima locaux.
 *
 * @param path Un pointeur vers un chemin à muter.
 */
void mutate(Path* path);

#endif

