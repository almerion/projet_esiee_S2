#ifndef __PATH__
#define __PATH__

#include <stdlib.h>
#include "adress.h"
#include "matrix.h"
/**
 * @file path.h
 * @brief Définit les structures de données pour
 * représenter un chemin sous forme de liste chaînée d'adresses et
 * déclare les fonctions associées à la manipulation de ces chemins.
 */

#define POPULATION_SIZE 32
#define PERCENT_KEPT 25    /* Est ce qu'on en garde trop ? */
#define PERCENT_FATHER 50  /* Faut-il plus accompler uniquement les meilleurs ? */
#define PERCENT_NEW 50     /* Un inidividu aléatoire ne peut plus rivaliser avec un déjà un peu optimiser */
#define MUTATION_RATE 16
#define LIMIT_TIME 180
#define SERVICE_TIME 3
#define MUTATION_PERCENTAGE 20

// Définition de la structure pour représenter un chemin
typedef struct _path {
    lst startAdr;      ///< Pointeur vers le premier nœud (tête) de la liste chaînée d'adresses du chemin.
}Path;

typedef Path Gene;

typedef struct{
    Gene *gene;  /* The full genome */
    int nbGenes;
    long int fitness;        /* the fitness in cache */
}Individual;

typedef struct{
    Individual* ind;         /* Array of individuals */
    int population_size;     /* Size of the population */
}Population;

void init_random_individual(Matrix m, Individual* ind);
int init_random_population(Matrix m,Population* pop, int gene_size);
int cmp_individual(const void * a, const void * b);
void sort_population(Population* pop);

/**
 * @brief Évalue la qualité (fitness) d'un chemin donné en fonction d'une matrice de coûts.
 *
 * @param matrix La matrice représentant les distances et le temps entre les adresses.
 * @param startAdr Le pointeur vers le premier nœud de la liste chaînée représentant le chemin.
 * @return La valeur de fitness du chemin. Cette valeur est calculée en fonction des coûts (distances, temps) présents dans la `matrix` pour le parcours défini par la liste d'adresses.
 */
double evaluateFitness(Matrix matrix, Individual individual);

/**
 * @brief Génère un nouveau chemin à partir d'une première adresse donnée.
 *
 * @param matrix La matrice représentant les distances ou les coûts entre les adresses.
 * @param startAdr Un pointeur vers le premier nœud (tête) de la liste chaînée représentant le point de départ du chemin à générer.
 * @return Le nouveau chemin généré. La logique de génération (comment les adresses suivantes sont choisies) dépendra de l'implémentation de cette fonction.
 *
 * @note Le nom de la fonction et le paramètre suggèrent que le chemin est construit à partir d'une adresse de départ existante. Les adresses à éviter et les points de départ/arrivée spécifiques ne sont pas explicitement passés ici, ce qui pourrait être géré en amont ou dans l'implémentation.
 */
Path generatePath(Matrix matrix, lst startAdr);

/**
 * @brief Génère un tableau de chemins, chacun potentiellement avec des adresses différentes.
 *
 * @param matrix La matrice représentant les distances ou les coûts entre les adresses.
 * @param nbPaths Un entier représentant le nombre de chemins à créer.
 *
 * @return Un pointeur vers le premier élément d'un tableau de structures `Path` nouvellement alloué, contenant les chemins initialisés. Il incombe à l'appelant de libérer la mémoire de ce tableau lorsqu'il n'est plus nécessaire.
 */
Path* initPaths(Matrix matrix, int nbPaths);

/**
 * @brief Trie un tableau de chemins selon un critère spécifique.
 * @param paths Un pointeur vers le premier élément du tableau de structures `Path`
 * à trier. La fonction modifiera l'ordre des éléments directement dans
 * ce tableau.
 * @param nbPaths Un entier représentant le nombre d'éléments valides dans le
 * tableau `paths` qui doivent être considérés pour le tri. Il est
 * crucial que ce paramètre reflète la taille effective de la portion
 * du tableau contenant les chemins à trier.
 */
void sortPaths(Path* paths, int nbPaths);

/**
 * @brief Applique l'opération de croisement (crossover) entre deux chemins parents pour créer un nouveau chemin enfant.
 * Cette opération combine des séquences d'adresses des deux chemins parents pour explorer de nouvelles solutions potentielles.
 *
 * @param path1 La première structure `Path` représentant le premier parent.
 * @param path2 La deuxième structure `Path` représentant le deuxième parent.
 * @return Une nouvelle structure `Path` représentant le chemin enfant résultant du croisement des deux parents.
 */
void crossover(int* father, int* mother, int matrix_size, int* child);

/**
 * @brief Applique l'opération de mutation à un chemin donné. La mutation introduit de petites modifications
 * aléatoires dans la séquence d'adresses du chemin pour augmenter la diversité de la population et éviter de rester bloqué
 * dans des optima locaux.
 *
 * @param path Un pointeur vers le chemin à muter. La mutation pourrait impliquer l'échange de deux adresses, l'insertion ou la suppression d'une adresse, etc.
 */
void mutate(int* individual, int matrix_size);

#endif