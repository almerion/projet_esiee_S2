#ifndef __MATRIX__
#define __MATRIX__

/**
 * @file matrix.h
 * @brief Définit les structures de données pour représenter une matrice
 * contenant à la fois des informations de distance et de temps entre des points,
 * et déclare les fonctions associées à la manipulation de cette matrice.
 */

// Définition de la structure pour stocker une distance et un temps associés.
typedef struct distime{
    float dist; ///< La distance entre deux points (en kilomètres, mètres, etc.).
    int time;   ///< Le temps nécessaire pour aller d'un point à l'autre (en minutes, secondes, etc.).
}Distime,*Distimes; ///< `Distime` est le type structure, `Distimes` est un pointeur vers une structure `Distime`.

// Définition de la structure pour représenter une matrice de distances et de temps.
typedef struct matrix {
    Distimes* matrix; ///< Un pointeur vers un tableau de pointeurs `Distimes`.
                      ///< Chaque élément de ce tableau pourrait représenter une ligne de la matrice,
                      ///< et pointer vers un tableau de structures `Distime` représentant les colonnes.
    int size;        ///< La dimension de la matrice (nombre de lignes et de colonnes, supposée carrée).
}Matrix;

/**
 * @brief Affiche le contenu de la matrice de distances et de temps.
 *
 * @param m La structure `Matrix` à afficher.
 *
 * @note Cette fonction est probablement utilisée à des fins de débogage ou d'affichage des données de la matrice.
 * Le format d'affichage dépendra de l'implémentation de la fonction.
 */
void display_matrix(Matrix* m);

Matrix* create_matrix(int size, Distime* base);
Distime* create_distime(int size);
void free_matrix(Matrix* matrix);

#endif