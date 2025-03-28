# Participants
- DOROTHEE Ethan  
- LOUSA NARCISO Tiago  
- PREVOT Maxime  
- SENE Mouhamed  

# Sujet
Une entreprise nous fournit un fichier CSV contenant une liste de pharmacies à livrer. Grâce à un programme, nous disposons d’un nombre illimité de camionnettes et devons trouver, en une minute, le parcours le plus optimal pour chacune d’elles. La sortie devra être un PDF comprenant une carte pour visualiser le parcours de chaque camionnette, ainsi qu’un tableau récapitulatif indiquant, pour chaque camionnette, son parcours et ses heures de départ et d’arrivée estimées.

# Structure
Le projet est structuré en trois programmes principaux :  
1. Le premier programme prendra un CSV contenant la liste des pharmacies à livrer en paramètre et générera deux fichiers : une matrice de distances et une liste de coordonnées.  
2. Le deuxième programme lira la matrice de coordonnées et, grâce à un algorithme génétique, essaiera de trouver le meilleur chemin (minimisant les kilomètres à parcourir) pour chaque camionnette, tout en desservant toutes les destinations. Il produira un fichier de sortie indiquant, pour chaque camionnette, le parcours à suivre.  
3. Le dernier programme lira ces différents fichiers et produira un PDF final indiquant, pour chaque camionnette, son heure de départ, son heure d’arrivée à chaque pharmacie, son parcours, les kilomètres parcourus, le coût moyen du trajet, l’essence utilisée et une carte permettant de visualiser le parcours de chaque camionnette.

# Les programmes

## Programme n°1
Le premier programme, écrit en Python, lit le CSV contenant les pharmacies à livrer avec leurs adresses. Grâce à l’API Nominatim, il obtient les coordonnées géographiques de chaque pharmacie. Ensuite, avec GraphHopper, il détermine le chemin le plus court pour toutes les destinations, afin de générer une matrice de distances et de temps. Ces deux tableaux sont sauvegardés dans deux fichiers distincts pour être utilisés par les programmes suivants. La première ligne et la première colonne de ces matrices correspondent au dépôt, c’est-à-dire l’endroit d’où chaque camionnette commence et termine son parcours.

## Programme n°2
Le deuxième programme récupère la matrice des distances et des temps générée par le premier programme. Grâce à un algorithme génétique, il produit une liste de chemins et la sauvegarde dans un fichier. Celui-ci contient une liste de listes d’entiers représentant les parcours de chaque camionnette, où chaque entier correspond à l’indice d’une pharmacie dans le CSV d’origine. La fonction de fitness est calculée pour chaque camionnette en fonction de la distance parcourue et du nombre de pharmacies visitées (une notion de temps pourrait également être envisagée pour que la durée se rapproche le plus possible de 3 heures sans les dépasser).  
(À compléter)

## Programme n°3
Le dernier programme réunit tous les fichiers afin de générer le PDF final. Il lit le fichier produit par le programme n°2 pour récupérer le nombre de camionnettes et leurs parcours (sous forme d’indices de pharmacies). Puis, il lit le CSV de base pour faire correspondre ces indices aux noms des pharmacies, ce qui permet de créer les tableaux lisibles dans le PDF. Enfin, il utilise le CSV contenant les coordonnées pour générer la carte, incluse dans le PDF, qui illustre le parcours de chaque camionnette.