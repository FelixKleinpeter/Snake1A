/**
 * @file min-max.h
 * 
 * @brief algorithme de l'intelligence artificiel du shlanga
 *
 * @author Groupe 9
 * 
 * @version 1.0
 * 
 * @date 1 avril 2016
 */

#ifndef MINMAX
#define MINMAX

#include "structures.h"


		/**
 * \fn       dist(couple p1, couple p2)
 *
 * \brief    Calcul la distance entre deux points
 *
 * \details  C'est un calcul de la distance de Manhattan, de la forme |x-x'| + |y-y'|
 *
 * \param    p1 Le point n°1
 *
 * \param    p2 Le point n°2
 *
 * \return   Renvoi le résultat du calcul
 */
int dist(couple p1, couple p2);

		/**
 *
 * \fn       cons_liste(liste l, int a)
 *
 * \brief    Ajoute un entier à une liste
 *
 * \details  Cette fonction s'occupe de l'allocation
 *
 * \param    l La liste à concaténer
 *
 * \param    a L'entier à ajouter
 *
 * \return   Renvoi la nouvelle liste
 */
liste cons_liste(liste l, int a);

		/**
 *
 * \fn       nb_elm_liste(liste l)
 *
 * \brief    Compte le nombre d'éléments d'une liste
 *
 * \details  Parcours la liste et compte le nombre d'éléments qu'elle possède
 *
 * \param    l La liste à étudier
 *
 * \return   Renvoi la longueur de la liste
 */
int nb_elm_liste(liste l);

		/**
 *
 * \fn       affiche_liste(liste l)
 *
 * \brief    Affiche les éléments de la liste
 *
 * \details  Parcours la liste et affiche chacun de ses éléments
 *
 * \param    l La liste à étudier
 *
 * \return   Fonction de type void
 */
void affiche_liste(liste l);


		/**
 *
 * \fn       eval(serpent s1, serpent s2, matrix M)
 *
 * \brief    Affecte un entier qui juge de la qualité d'une situation
 *
 * \details  La fonction basera son jugement sur plusieurs facteurs qu'elle ponderera en fonction de la valeur que
 le programmeur leur juge. Ceux-ci sont : la distance entre les serpents (têtes), la distance au mur de chacun et leur
 nombre de case accessible (autour de la tête).
 *
 * \param    s1 Le serpent pour lequel la situation est bonne lorsque le retour de eval est haut (ici le Schlanga)
 *
 * \param    s2 Le serpent ennemi(ici le Snake)
 *
 * \param    M Le terrain
 *
 * \return   Renvoi l'entier carractérisant la valeur de la situation
 */
int eval(serpent s1, serpent s2, matrix M);

		/**
 *
 * \fn       eval_aggro(serpent s1, serpent s2, matrix M)
 *
 * \brief    Affecte un entier qui juge de la qualité d'une situation
 *
 * \details  La fonction basera son jugement sur plusieurs facteurs qu'elle ponderera en fonction de la valeur que
 le programmeur leur juge. Ceux-ci sont : la distance entre les serpents (têtes), la distance au mur de chacun et leur
 nombre de case accessible (autour de la tête). Les critères seront ici plus aggressifs.
 *
 * \param    s1 Le serpent pour lequel la situation est bonne lorsque le retour de eval_aggro est haut (ici le Schlanga)
 *
 * \param    s2 Le serpent ennemi(ici le Snake)
 *
 * \param    M Le terrain
 *
 * \return   Renvoi l'entier carractérisant la valeur de la situation
 */
int eval_aggro(serpent s1, serpent s2, matrix M);


		/**
 *
 * \fn       distance_au_mur(serpent s, matrix M)
 *
 * \brief    Calcul la distance entre la tête d'un serpent et le mur le plus proche
 *
 * \details  On pars dans toute les directions, et on regarde dans laquelle le mur est proche de la tête
 *
 * \param    s Le serpent que l'on va étudier
 *
 * \param    M Le terrain
 *
 * \return   Renvoi la distance eu mur le plus proche
 *
 */
int distance_au_mur(serpent s, matrix M);

		/**
 *
 * \fn       direc_serpent(serpent s)
 *
 * \brief    Renvoi la direction actuelle de la tête d'un serpent
 *
 * \details  On la déduit du type d'élément que contient la tête du serpent
 *
 * \param    s Le serpent que l'on va étudier
 *
 * \return   Renvoi la direction du serpent (1, 2, 3 où 4)
 */
int direc_serpent(serpent s);

		/**
 *
 * \fn       envisageable(int direc, serpent s, matrix M)
 *
 * \brief    Vérifie si le serpent peut emprunter cette direction
 *
 * \details  Un serpent ne peux pas emprunter une direction si elle est opposée à sa direction actuelle (pas de 
 demi-tour) où si la case à laquelle elle mènerait est obstruée
 *
 * \param    direc la direction à analyser
 *
 * \param    s Le serpent qui veut l'empruter
 *
 * \param    M Le terrain
 *
 * \return   Renvoi 1 si la direction est envisageable, 0 sinon
 */
int envisageable(int direc, serpent s, matrix M);

		/**
 *
 * \fn       meilleur_snake(serpent s1, serpent s2, matrix M)
 *
 * \brief    Trouve le mouvement que ferait le Snake dans une situation
 *
 * \details  On se base pour juger de la direction que doit prendre le serpent du renvoi de la fonction eval.
On imagine que le Snake va tenter de minimiser ce renvoi.
 *
 * \param    s1 Le Schlanga
 *
 * \param    s2 Le Snake
 *
 * \param    M Le terrain
 *
 * \return   Renvoi la direction déduite
 */
int meilleur_snake(serpent s1, serpent s2, matrix M);

		/**
 *
 * \fn       remplis_matrice(serpent s1, serpent s2, matrix M)
 *
 * \brief    Place les serpents dans une nouvelle matrice
 *
 * \details  On crée une nouvelle matrice vide à partir des dimensions de celle donnée en argument et on y place
 les serpents
 *
 * \param    s1 Le serpent 1 (Snake où Schlangà)
 *
 * \param    s2 Le serpent 2 (Snake où Schlangà)
 *
 * \param    M Le terrain
 *
 * \return   Renvoi la matrice déduite
 */
matrix remplis_matrice(serpent s1, serpent s2, matrix M);

		/**
 *
 * \fn       jouer(serpent s1, serpent s2, matrix M, int compt, int n, int* res, int type_dia)
 *
 * \brief    Fonction récursive qui sera appelée dans coup_a_jouer
 *
 * \details  On s'arrête lorsque l'on est arrivé au nombre n d'itération, compté dans la variable compt.
 A chaque coup, on crée autant de Snake, de Shclangà et de matrice que le Schlangà a de directions accessibles. 
 Chaque Schlangà ira dans une de ces directions. On comparera alors le rappel de cette fonction sur chacune des possibilités
 et on choisira la plus grande, sachant qu'au cas d'arrêt on va appeler la fonction eval (où eval_aggro). On regarde
 enfin si on en est au premier appel de la fonction, et on sauvegarde la valeur de la direction retenue dans res.
 *
 * \param    s1 Le Schlanga
 *
 * \param    s2 Le Snake
 *
 * \param    M Le terrain
 *
 * \param    compt Le compteur indiquant le nombre de rappel actuel de la fonction
 *
 * \param    n Le nombre de rappel total désiré
 *
 * \param    res Le pointeur dans lequel on stockera le résultat
 *
 * \param    type_dia l'entier indiquant si on utilise un Schlangà offensif où défensif
 *
 * \return   Renvoi l'évaluation de la dierction lorsque compt=n et jouer sinon
 */
int jouer(serpent s1, serpent s2, matrix M, int compt, int n, int* res, int type_dia);

		/**
 *
 * \fn       coup_a_jouer(serpent s1, serpent s2, matrix M, int n, int type_dia)
 *
 * \brief    Donne le coup que doit jouer le Schlangà
 *
 * \details  On crée le pointeur res et on appelle la fonction jouer avec tous les paramètres nécéssaires.
 On renvoie la valeur de res après l'application de jouer.
 *
 * \param    s1 Le Schlangà
 *
 * \param    s2 Le Snake
 *
 * \param    M Le terrain
 *
 * \param    n Le nombre coup à l'avance désiré
 *
 * \param    type_dia l'entier indiquant si on utilise un Schlangà offensif où défensif
 *
 * \return   Renvoi la direction du Shclangà au coup suivant
 */
int coup_a_jouer(serpent s1, serpent s2, matrix M, int n, int type_dia);

		/**
 *
 * \fn       free_mat(matrix M)
 *
 * \brief    Libère la mémoire contenue par une matrice
 *
 * \details  On la parcours et on free chaque tableaux pour ensuite free le tableau total.
 *
 * \param    M La matrice à free
 *
 * \return   Fonction void
 */
void free_mat(matrix M);

		/**
 *
 * \fn       accessibles(serpent s, matrix M)
 *
 * \brief    Liste les directions accessibles
 *
 * \details  Une direction est accessible si elle n'est pas opposée à la direction actuelle et si elle n'est pas obstruée.
 *
 * \param    s Le serpent à tester
 *
 * \param    M Le terrain
 *
 * \return   Renvoi la liste des directions accessibles
 *
 */
liste accessibles(serpent s, matrix M);

		/**
 *
 * \fn       direc_random(serpent s, matrix M, SDL_Surface* ecran)
 *
 * \brief    Trouve une direction aléatoire parmi les accessibles
 *
 * \details  Utilise la fonction accessibles pour trouver quelles directions sont disponibles, et en choisit
 une aléatoirement parmi celles-ci.
 *
 * \param    s Le Schlangà
 *
 * \param    M Le terrain
 *
 * \return   Renvoi la direction aléatoire choisie
 */
int direc_random(serpent s, matrix M, SDL_Surface* ecran);

#endif