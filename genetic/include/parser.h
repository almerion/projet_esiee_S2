#ifndef __PARSER__
#define __PARSER__

#include "matrix.h"

/**
 * @file parser.h
 * @brief Déclare les fonctions nécessaires pour parser (analyser) un fichier
 * et extraire des informations pour créer une structure de données `Matrix`.
 */

/**
 * @brief Parse un fichier spécifié par son chemin et crée une structure `Matrix`
 * à partir des données contenues dans ce fichier.
 *
 * @param filePath Un pointeur vers une chaîne de caractères représentant le chemin
 * du fichier à parser.
 * @return Une structure `Matrix` contenant les données extraites du fichier.
 * La fonction devra gérer l'allocation de mémoire pour la matrice et
 * le remplissage de ses données en fonction du format du fichier.
 * En cas d'erreur lors du parsing ou de l'ouverture du fichier,
 * la fonction pourrait retourner une matrice vide ou signaler l'erreur
 * d'une autre manière (par exemple, en retournant NULL).
 */
Matrix parseFile(char* filePath);

#endif