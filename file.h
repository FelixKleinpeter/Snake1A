/**
 * @file file.h
 * 
 * @brief Structure de file permettant le stockage des coups du joueur
 *
 * @author Groupe 9
 * 
 * @version 1.0
 * 
 * @date 17 mai 2016
 */

#ifndef FILES
#define FILES


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

typedef struct
{
	int curseur;
	int taille;
	int taille_totale;
	int* tab;
} file;

		/**
 * \fn       creer_file_vide(int t)
 * \brief    Crée une file vide
 * \details  Initialise le tableau annexe utilisé dans la file à l'entier donné en paramètre.
 * \param    t La taille du tableau qui servira de support à la file
 * \return   Renvoi la file créée
 */
file creer_file_vide(int t);


		/**
 * \fn       affiche_file(file f)
 * \brief    Affiche les données d'une file
 * \details  Parcours le tableau support du curseur de début au curseur de fin.
 * \param    f La file à afficher
 * \return   Fonction void
 */
void affiche_file(file f);

		/**
 * \fn       retrait(file* f)
 * \brief    Enlève l'élement de queue de la file
 * \details  Prends en compte le déplacement des curseurs et le cas de la file nulle
 * \param    f La file dont on enlève le dernier élément
 * \return   L'entier de queue
 */
int retrait(file* f);

		/**
 * \fn       detruit(file* f)
 * \brief    Free la file
 * \details  Free la file
 * \param    f La file à free
 * \return   Fonction void
 */
void detruit(file* f);

		/**
 * \fn       ajout(file* f, int elm)
 * \brief    Ajoute un élément en tête
 * \details  Prends en compte les déplacement de curseur en bout de tableau et les tableaux trop petits
 * \param    f La file à free
 * \return   Fonction void
 */
void ajout(file* f, int elm);


#endif