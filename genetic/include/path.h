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

// Définition de la structure pour représenter un chemin
typedef struct _path
{
    lst startAdr;      ///< Pointeur vers le premier nœud (tête) de la liste chaînée d'adresses du chemin.
    adress* lastAdr;       ///< Pointeur vers le dernier nœud (queue) de la liste chaînée d'adresses du chemin.
    double fitness;     ///< Valeur numérique représentant la qualité (fitness) de ce chemin. Une valeur plus élevée indique généralement un meilleur chemin.
    float fullTime;     ///< Temps total ou coût associé à la traversée de ce chemin.

}Path;

/**
 * @brief Évalue la qualité (fitness) d'un chemin donné en fonction d'une matrice de coûts.
 *
 * @param matrix La matrice représentant les distances et le temps entre les adresses.
 * @param startAdr Le pointeur vers le premier nœud de la liste chaînée représentant le chemin.
 * @return La valeur de fitness du chemin. Cette valeur est calculée en fonction des coûts (distances, temps) présents dans la `matrix` pour le parcours défini par la liste d'adresses.
 */
double evaluateFitness(Matrix matrix, lst startAdr);

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
 * @brief Vérifie si un tableau de chemins est valide selon certains critères.
 * Le paramètre `nbPaths` pourrait représenter le nombre de chemins dans le tableau à vérifier ou un autre critère de validation lié à la quantité de chemins.
 *
 * @param paths Un pointeur vers le premier élément d'un tableau de structures `Path` à vérifier.
 * @param nbPaths Un entier représentant un critère de validation appliqué à l'ensemble des chemins (la signification exacte dépend de l'implémentation).
 * @return 1 si tous les chemins dans le tableau sont valides selon les critères définis, 0 sinon (ou si au moins un chemin est invalide).
 */
int checkPaths(Path* paths, int nbPaths);

/**
 * @brief Applique l'opération de croisement (crossover) entre deux chemins parents pour créer un nouveau chemin enfant.
 * Cette opération combine des séquences d'adresses des deux chemins parents pour explorer de nouvelles solutions potentielles.
 *
 * @param path1 La première structure `Path` représentant le premier parent.
 * @param path2 La deuxième structure `Path` représentant le deuxième parent.
 * @return Une nouvelle structure `Path` représentant le chemin enfant résultant du croisement des deux parents.
 */
Path crossover(Path path1, Path path2);

/**
 * @brief Applique l'opération de mutation à un chemin donné. La mutation introduit de petites modifications
 * aléatoires dans la séquence d'adresses du chemin pour augmenter la diversité de la population et éviter de rester bloqué
 * dans des optima locaux.
 *
 * @param path Un pointeur vers le chemin à muter. La mutation pourrait impliquer l'échange de deux adresses, l'insertion ou la suppression d'une adresse, etc.
 */
void mutate(Path* path);

#endif