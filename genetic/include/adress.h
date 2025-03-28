#ifndef __ADRESS__
#define __ADRESS__

/**
 * @file adress.h
 * @brief Définit la structure de données pour représenter une adresse
 * sous forme de nœud dans une liste chaînée, et déclare les fonctions
 * associées à la manipulation de ces adresses.
 */

// Définition de la structure pour représenter une adresse dans un chemin (liste chaînée)
typedef struct _adress_node{
    int pharmacyIndex;      ///< L'index identifiant une pharmacie spécifique.
    struct _adress_node* next; ///< Pointeur vers le prochain nœud d'adresse dans la liste chaînée.
}adress_node;

typedef adress_node adress; ///< Alias pour `adress_node`, permettant d'utiliser le nom `adress` pour plus de concision.

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
 * @param firstAdr Un pointeur vers le premier nœud (tête) de la liste chaînée.
 * @return Un pointeur vers le dernier nœud d'adresse qui a été retiré de la liste.
 * Retourne NULL si la liste est vide ou ne contient qu'un seul élément (dans ce cas,
 * le seul élément est retiré). Il incombe à l'appelant de libérer la mémoire
 * du nœud retourné si nécessaire.
 *
 * @note Cette fonction nécessite un pointeur vers le début de la liste pour pouvoir
 * parcourir et atteindre le dernier élément.
 */
adress* pop_adress(adress* firstAdr);

/**
 * @brief Met à jour les informations d'un nœud d'adresse existant.
 *
 * @param adr Un pointeur vers le nœud d'adresse à modifier.
 * @param index Un int représentant l'index de la nouvelle adresse
 *
 * @note La spécificité de la mise à jour (quel membre est modifié) n'est pas précisée ici
 * et dépendra de l'implémentation de la fonction. Généralement, cela pourrait modifier
 * le `pharmacyIndex` ou le pointeur `next` (avec précaution).
 */
void update_adress(adress* adr,int index);

/**
 * @brief Permute (échange) les `pharmacyIndex` de deux nœuds d'adresse donnés.
 *
 * @param adr1 Un pointeur vers le premier nœud d'adresse dont l'index sera échangé.
 * @param adr2 Un pointeur vers le deuxième nœud d'adresse dont l'index sera échangé.
 *
 * @note Cette fonction modifie le contenu des nœuds pointés par `adr1` et `adr2`.
 * Elle n'échange pas les nœuds eux-mêmes dans la liste chaînée, mais seulement leurs valeurs d'index.
 */
void permute_adress(adress* adr1, adress* adr2);

/**
 * @brief Insère un nouveau nœud d'adresse dans une liste chaînée.
 *
 * @param firstAdr Un pointeur vers le premier nœud (tête) de la liste chaînée.
 * @param adr Un pointeur représentant l'adresse à ajouter à la liste chaînée.
 *
 * @note La position de l'insertion (début, fin, après un nœud spécifique) n'est pas précisée ici
 * et dépendra de l'implémentation de la fonction et du contexte d'appel. La fonction pourrait
 * insérer au début de la liste pointée par `firstAdr`, mais cela n'est pas garanti par la signature.
 */
void insert_adress(adress* firstAdr,adress* adr);

#endif