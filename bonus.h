/**
 * @file bonus.h
 * 
 * @brief construction du jeu snake
 *
 * @author Groupe 9
 * 
 * @version 1.0
 * 
 * @date 19 Avril 2016
 */

#ifndef BONUS
#define BONUS

#include "structures.h"



/**
 * @fn           genere_bonus(matrix M, int n, int type_genere)
 *
 * @brief       Cette fonction génère aléatoirement n bonus de type type_genere
 *
 * @details    Chaque bonus est représenté par un entier (ex: 30 = Pomme), cette fonction place
 *
 * 	aléatoirement n nombre 30 dans la matrice M qui réprésente le terrain. Ainsi le terrain contiendra
 *	n pommes. 
 * @param    matrix M: Matrice qui représente le plateau de jeu
 * @param	int n : nombre de bonus que l'on veut générer
 * @param 	int type_genre : représente le type de bonus que l'on veut créer (ex : 30 = Pomme) 
 * @return     Cette fonction change la matrice, après affectation des bonus
 */

void genere_bonus(matrix M, int n, int type_genere);

/**
 * \fn           rallonge_serpent(serpent s_new, serpent s_old)
 * \brief       Cette fonction change le serpent de départ en le rallongeant 
 * \details    Après avoir pris le bonus de type Pomme, le serpent se rallonge, cette fonction 
 rallonge donc la taille du serpent. Pour ce faire on regarde la forme de l'ancien serpent
 (avant être passé sur le bonuns) et la forme du nouveau serpent (un pas après). 
 On remplace la queu du nouveau serpent par la  queu de l'ancient et on rajoute un tronc
 pour connecter les 2 bouts. Le serpent a donc été rallongé.
 * \param    serpent s_new : le nouveau serpent après déplacement sur la pomme
 * \param	serpent s_old : l'ancient serpent avant déplacement sur la pomme
 * \return     Cette fonction crée un serpent plus long 
 */
 
serpent rallonge_serpent(serpent s_new, serpent s_old);


/**
 * \fn           raccourcie_serpent(serpent s, matrix* M)
 * \brief       Cette fonction change le serpent de départ en le raccourciçant 
 * \details    Après avoir pris un malus, le serpent se raccourcie, on lui enlève la queu
 et on remplace le tronc qui connectant son ancienne queu au reste du corps par une nouvelle queu.
 Le serpent a donc rétrécie.
 * \param    serpent s : le serpent que l'on veut rétrécir
 * \param	matrix M : la matrice qui représente le terrain
 * \return     Cette fonction crée un serpent plus court
 */

serpent raccourcie_serpent(serpent s, matrix* M);



/**
 * \fn           collision_bonus(matrix M, serpent s_new, serpent s_old,int_tab* tab_temp, Mix_Chunk* son)
 * \brief       Cette fonction change le serpent ou la matrice en fonction du bonus qu'il rencontre 
 * \details    En fonction de chaque bonus pris, ces bonus vont opérer un changement sur le serpent,
 le terrain ou la vitesse du jeu en lui même. 
 * \param    matrix M : le terrain
 * \param	serpent s_new : nouveau serpent (argument nécéssaire pour rallonge serpent)
 * \param	serpent s_old : ancient serpent (argument nécéssaire pour rallonge serpent)
 * \param	int_tab* tab_temp : Un tableau d'entier dont chaque case correspond au nombre de bonus
 d'un certain type qui reste sur le terrain.
  Si le serpent un bonus, la case correspondante va décrémenter. 
  Si l'une des cases arrive à 0, on génère à nouveau n bonus du type correspondant.
 *\param Mix_Chunk* son : tableau qui correspond au son que l'on entend après avoir pris un bonus
 * \return     Cette retourne le nouveau serpent après être passé sur un bonus mais change aussi 
 la matrice M et d'autre variables globales. 
 */
serpent collision_bonus(matrix M, serpent s_new, serpent s_old,int_tab* tab_temp, Mix_Chunk* son);



#endif