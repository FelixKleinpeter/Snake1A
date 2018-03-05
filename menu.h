/**
 * @file menu.h
 * 
 * @brief création des boutons et des menus
 *
 * @author Groupe 9
 * 
 * @version 1.0
 * 
 * @date 1 avril 2016
 */


#ifndef MENU
#define MENU

#include "structures.h"

typedef struct 
{
	int x;
	int y;
	int hauteur;
	int largeur;
	SDL_Surface* texte;
	SDL_Surface* fond;
}Bouton;


		/**
 * \fn       creer_bouton(int x, int y, int hauteur, int largeur, char* texte_en_char, 
	int r, int v, int b, TTF_Font *police, SDL_Surface* ecran, char* image)
 * \brief    Crée un objet de type Bouton
 * \details  Remplis les champs de l'objet en fontion des paramètres.
 * \param    x L'ordonnée du buton
 * \param    y L'abcisse du bouton
 * \param    hauteur La hauteur du bouton
 * \param    largeur La largeur du bouton
 * \param    texte_en_char Le texte qui va être écrit sur le bouton
 * \param    r La valeur en rouge
 * \param    v La valeur en vert
 * \param    b La valeur en bleu
 * \param    police La police utilisée
 * \param    ecran L'écran
 * \param    image L'image de fond du bouton (pa utilisée ici)
 * \return   Renvoi le bouon créé
 */
Bouton creer_bouton(int x, int y, int hauteur, int largeur, char* texte_en_char, 
	int r, int v, int b, TTF_Font *police, SDL_Surface* ecran, char* image);

		/**
 * \fn       blit_bouton(Bouton b, SDL_Surface* ecran, SDL_Surface* aux)
 * \brief    Affiche un bouton sur l'écran
 * \details  Utilise les paramètres du bouton pour le bliter sur l'écran
 * \param    b Le bouton à afficher
 * \param    ecran L'écran
 * \param    aux Une surface déjà alloué qui permet de faire un fond, non utilisé ici
 * \return   Fonction void
 */
void blit_bouton(Bouton b, SDL_Surface* ecran, SDL_Surface* aux);

		/**
 * \fn       bliter_les_boutons(Bouton* tableau_de_boutons, int taille, SDL_Surface* ecran, SDL_Surface* aux)
 * \brief    Affiche tous les boutons du tableau de boutons
 * \details  Parcours le tableau et utilise la fonction blit_bouton
 * \param    tableau_de_boutons Le tableau des bouton à afficher
 * \param    taille La taille du tableau
 * \param    ecran L'écran
 * \param    aux Une surface déjà alloué qui permet de faire un fond, non utilisé ici
 * \return   Fonction void
 */
void bliter_les_boutons(Bouton* tableau_de_boutons, int taille, SDL_Surface* ecran, SDL_Surface* aux);

		/**
 * \fn       trouver_bouton(SDL_Event event, Bouton* tableau_de_boutons, int taille, SDL_Surface* ecran)
 * \brief    Renvoi le bouton à la position en laquelle on a cliqué
 * \details  On observe si le clic est compris entre la hauteur et la largeur du bouton. 
 On suppose que les boutons ne se superposent pas.
 * \param    event L'évenement clic qui contiendra l'abcisse et l'ordonnée de celui-ci
 * \param    tableau_de_boutons Le tableau des boutons dans lequel on cherche
 * \param    ecran L'écran
 * \param    taille La taille du tableau
 * \return   Renvoi le bouton trouvé
 */
Bouton trouver_bouton(SDL_Event event, Bouton* tableau_de_boutons, int taille, SDL_Surface* ecran);

		/**
 * \fn       egal_bouton(Bouton b, Bouton c)
 * \brief    Test si deux boutons sont égaux
 * \details  On test l'égalité vis à vis de leur position
 * \param    b Le premier bouton à tester
 * \param    c Le second bouton à tester
 * \return   Renvoi le résultat du test d'égalite
 */
int egal_bouton(Bouton b, Bouton c);

		/**
 * \fn       free_bouton(Bouton b)
 * \brief    Free un bouton
 * \details  Free chacune des surfaces que contient le bouton
 * \param    b Le bouton à free
 * \return   Fonction void
 */
void free_bouton(Bouton b);

		/**
 * \fn       menu(SDL_Surface* ecran)
 * \brief    Affiche le premier menu
 * \details  Affiche tout les bouton et combine les fonctions précédentes pour voir sur lequel on clic. 
 On effectue les actions en conséquence.
 * \param    ecran L'écran
 * \return   Renvoie la largeur, la hauteur du plateau, la longeur des serpents et le type d'IA choisi
 */
quadruplet menu(SDL_Surface* ecran);

		/**
 * \fn       menu_fin(SDL_Surface *ecran)
 * \brief    Affiche le second menu
 * \details  Affiche tout les bouton et combine les fonctions précédentes pour voir sur lequel on clic. 
 On effectue les actions en conséquence.
 * \param    ecran L'écran
 * \return   Renvoi un entier disant si l'on quitte où si on reprends au premier menu
 */
int menu_fin(SDL_Surface *ecran);



#endif
