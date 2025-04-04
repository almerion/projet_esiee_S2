#ifndef __ADRESS__
#define __ADRESS__


#include "matrix.h"
/**
 * @file adress.h
 * @brief Définit la structure de données pour représenter une adresse
 * sous forme de nœud dans une liste chaînée, et déclare les fonctions
 * associées à la manipulation de ces adresses.
 * 
 * @note lst startAdr-> liste chaînée / adress *adr -> pointeur vers une adresse
 */

// Définition de la structure pour représenter une adresse dans un chemin (liste chaînée)
typedef struct _adress_node{
    int pharmacyIndex;      ///< L'index identifiant une pharmacie spécifique.
    struct _adress_node* next; ///< Pointeur vers le prochain nœud d'adresse dans la liste chaînée.
}adress_node;

typedef adress_node adress; ///< Alias pour `adress_node`, permettant d'utiliser le nom `adress` pour plus de concision.
typedef adress_node* lst;    ///< Alias pour un pointeur vers le premier nœud d'une liste chaînée d'adresses.

/**
 * @brief Crée un nouveau nœud d'adresse avec l'index de pharmacie spécifié.
 *
 * @param pharmacyIndex L'index de la pharmacie à stocker dans le nouveau nœud.
 * @return Un pointeur vers le nouveau nœud d'adresse créé. Retourne NULL en cas d'échec d'allocation mémoire.
 */
adress* create_adress(int pharmacyIndex);

/**
 * @brief Retire le dernier élément de la liste chaînée d'adresses et le retourne.
 *
 * @param startAdr Un pointeur vers le premier nœud (tête) de la liste chaînée.
 * @return Un pointeur vers le dernier nœud d'adresse qui a été retiré de la liste.
 * Retourne NULL si la liste est vide ou ne contient qu'un seul élément (dans ce cas,
 * le seul élément est retiré). Il incombe à l'appelant de libérer la mémoire
 * du nœud retourné si nécessaire.
 *
 * @note Cette fonction nécessite un pointeur vers le début de la liste pour pouvoir
 * parcourir et atteindre le dernier élément. L'utilisation de l'alias `lst` pour le
 * paramètre indique qu'elle opère sur une liste chaînée d'adresses.
 */
adress* pop_adress(lst startAdr);

/**
 * @brief Met à jour l'index de pharmacie d'un nœud d'adresse existant.
 *
 * @param adr Un pointeur vers le nœud d'adresse à modifier.
 * @param index Un entier représentant l'index de la nouvelle adresse de pharmacie à assigner au nœud.
 *
 * @note Cette fonction modifie la valeur du membre `pharmacyIndex` du nœud pointé par `adr`.
 * Le pointeur `next` du nœud n'est pas modifié par cette fonction.
 */
void update_adress(adress *adr, int index);

/**
 * @brief Permute (échange) les `pharmacyIndex` de deux nœuds d'adresse donnés.
 *
 * @param adr1 Un pointeur vers le premier nœud d'adresse dont l'index sera échangé.
 * @param adr2 Un pointeur vers le deuxième nœud d'adresse dont l'index sera échangé.
 *
 * @note Cette fonction modifie le contenu des nœuds pointés par `adr1` et `adr2`.
 * Elle n'échange pas les nœuds eux-mêmes dans la liste chaînée, mais seulement leurs valeurs d'index.
 */
void permute_adress(adress *adr1, adress *adr2);

/**
 * @brief Insère un nouveau nœud d'adresse dans une liste chaînée.
 *
 * @param startAdr Un pointeur vers le premier nœud (tête) de la liste chaînée.
 * @param adr Un pointeur représentant l'adresse à ajouter à la liste chaînée.
 *
 * @note La position de l'insertion (début, fin, après un nœud spécifique) n'est pas précisée ici
 * et dépendra de l'implémentation de la fonction et du contexte d'appel. L'utilisation de l'alias `lst` pour le
 * paramètre indique qu'elle opère sur une liste chaînée d'adresses.
 */
void insert_adress(lst startAdr, adress *adr);

/**
 * @brief Récupère le temps de trajet direct entre deux adresses consécutives dans un chemin (ou une liste).
 *
 * @param matrix La matrice représentant les distances et le temps entre les adresses.
 * @param first Un pointeur vers le premier nœud d'adresse.
 * @param second Un pointeur vers le deuxième nœud d'adresse (le suivant de `first` dans la liste).
 * @return Un entier représentant le temps de trajet entre les deux adresses, tel que spécifié dans la matrice.
 */
int getTime(Matrix matrix, adress *first, adress *second);

#endif