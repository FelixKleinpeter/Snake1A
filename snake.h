/**
 * @file snake.h
 * 
 * @brief construction du jeu snake
 *
 * @author Groupe 9
 * 
 * @version 1.0
 * 
 * @date 19 Avril 2016
 */

#ifndef SNAKE
#define SNAKE

#include "structures.h"




/**
 * \fn           affiche (matrix M)
 *
 * \brief       afficher la matrix du jeu M
 *
 * \param    M  Matrice qui représente le plateau de jeu
 */
void affiche (matrix M);

/**
 * \fn           free_serpent(serpent s)
 *
 * \brief       permet de libérer la place mémoire prise par un serpent s
 *
 * \details     libére la mémoire prise par chaque élèment de la liste s, et aprés il la pointe sur la valeur NULL
 *
 * \param    s  le serpent qu'on veut libérer sa place mémoire
 */

void free_serpent(serpent s);

/**
 * \fn           affiche_serpent(serpent s)
 *
 * \brief       permet d'afficher la liste des triplets constituants le serpent du jeu
 *
 * \param    s  le serpent qu'on veut libérer sa place mémoire
 *
 * \return     écrit sur la sortir standard la liste constituant le serpent
 */

void affiche_serpent(serpent s);

/**
 * \fn           pose_serpent(serpent s1, matrix M)
 *
 * \brief       permet de poser le serpent sur le terrain du jeu
 *
 *\details      parcours la liste de triplets constituant le serpent, les deux premiers paramétres du triplet 
 				représentent les coordonnées dans la matrice, et le troisiéme représente quel maillon du serpent on doit poser
 *
 * \param    s1  le serpent qu'on veut poser sur le terrain du jeu
 *
 * \param    M  Matrice qui représente le plateau de jeu
 *
 * \return     retourne la matrice du jeu avec le serpent poser dessu
 */

matrix pose_serpent(serpent s1, matrix M);


/**
 * \fn           decale
 *
 * \brief       Fonction auxiliaire qui sert dans nouveau_serpent
 *
 *\details      On donne une "nouvelle_tête" (tête qui regarde à gauche par exemple) et 
 *				un noueau maillon (un coude par exemple) et on crée le nouveau serpent avec 
 *				cette tête et ce coude.
 *
 * \param    s  : le serpent qu'on veut modifier
 *
 * \param    triplet nouvtete : La "nouvelle tête" du serpent (tête à droite, à gauche ...)
 *
 * \param 	 int nouvmaillon : Le nouveau maillon qu'on veut connecter avec la nouvelle tête
 *								et l'ancient corps.
 *
 * \return     retourne le nouveau serpent crée
 */
serpent decale(serpent s, triplet nouvtete, int nouvmaillon);

/**
 * \fn           nouveau_serpent
 *
 * \brief       Fonction qui crée le nouveau serpent en fonction de la direction qu'il prend
 *
 *\details      On introduit un serpent, l'ancienne direction de ce serpent et la nouvelle
 				direction qu'il prend. Cette fonction va trouver une nouvelle tête et 
 				un nouveau maillon adéquate et va créer un nouveau serpent à l'aide de 
 				la fonction décale.
 *
 * \param    s  : le serpent qu'on veut modifier
 *
 * \param    int direc : entier qui désigne l'ancienne direction
 *
 * \param 	 int nouvdirect : entier qui désigne la nouvelle direction
 *
 * \return     retourne le nouveau serpent crée
 */
serpent nouveau_serpent(serpent s, int direc, int nouvdirec);

/**
 * \fn           queue_serpent(serpent s)
 *
 * \brief       Fonction qui renvoie la position de la queue du serpent
 *
 *\details      Un serpent est définit par une liste de triplet donc le 1er élement
 				et son abscisse, la deuxième son ordonnée, et le troisième, le type
 				de maillon que c'est (tête, corps, coude, queu).
 *
 * \param    serpent s : le serpent
 *
 * \return     retourne les coordonnées de la queue du serpent
 */
couple queue_serpent(serpent s);

/**
 * \fn           blit(matrix map , SDL_Surface* ecran , tabl_obj tab)
 *
 * \brief       Fonction d'affichage
 *
 *\details      Cette fonction affiche une image à une position précise. On travaille avec une
 				matrice de taille n,p et avec des images 30x30 pixel. En fonction du chiffre
 				de la matrice, on affiche l'image correspondate dans le tableau d'image tab.
 *
 * \param    matrix map :	la matrice qui désigne le terrain 
 *
 * \param    SDL_Surface* ecran : 	l'écran sur lequel on affiche les images
 *
 * \param 	 tabl_obj tab : 	tableau qui contient toutes les images qu'on veut afficher
 *
 */
void blit(matrix map , SDL_Surface* ecran , tabl_obj tab);

/**
 * \fn          construit_serpent(int n, int snake, matrix M)
 *
 * \brief       Fonction qui place les serpents sur le terrain au début du jeu
 *
 *\details      En fonction de la taille des serpents, on les pose sur la matrice d'une 
 				certaine manière
 *
 * \param    int n : taille des serpents
 *
 * \param    int snake : nombre de serpent
 *
 * \param 	 matrix M : matrice qui désigne le terrain
 *
 * \return     retourne un serpent
 */
serpent construit_serpent(int n, int snake, matrix M);



#endif
