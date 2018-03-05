
/**
 * \file         structures.h
 * \author    Grouope 9
 * \version   version 1
 * \date       19 avril 2016
 * \brief       Fichier qui contient toutes les structures et quelque fonctions
 * \details    Fichier qui contient des structures utiles pour le projet et des fonctions
 générales, comme la concaténation ou l'allocation de mémoire pour matrice toujours utile.
 */

#ifndef STRUCTURES
#define STRUCTURES


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <time.h>

#define NOMBRE_DE_COUPS 3


typedef struct 
{
    /**
 * \struct           int_tab
 * \brief       Un tableau d'entier
 */
    int taille;
    int* tabl;
}int_tab;

typedef struct 
{
    /**
 * \struct           triplet
 * \brief       Un élement de N*N*N
 */
	int x;
	int y;
    int z;
} triplet;

typedef struct 
{
    
    int x;
    int y;
    int z;
    int k;
} quadruplet;

typedef struct 
{
    int x;
    int y;
} couple;

typedef struct maillon *serpent;
struct maillon
{
	triplet tete;
	serpent queue;
};

typedef struct 
{
    int** mat;
    int lig;
    int col;
} matrix;

typedef struct 
{
    int taille;
    SDL_Surface** obj;
}tabl_obj;

typedef struct liste *liste;
struct liste
{
    int tete;
    liste queue;
};


/**
 * \fn           allocmatrice (int n,int p)
 * \brief       Cette fonction alloue une place mémoire suffisante pour une matrice
 * \details    Cette fonction alloue une place mémoire pour contenir une matrice de taille n,p.
 * \param    int n : désigne le nombre de ligne de la matrice
 * \param   int p : désigne le nombre de colonne de la matrice
 * \return     Cette fonction retourne une matrice vide avec une case mémoire assignée. 
 */
matrix allocmatrice (int n,int p);

/**
 * \fn           create_terrain (int n,int p)
 * \brief       Cette fonction crée une matrice qui modélisera le terrain
 * \details    Cette fonction crée une matrice de taille n p qui désignera le terrain.
 La matrice contiendra des 0 partout (désigne l'herbe ou le serpent peut se déplacer), et des 1
 qui désigneront les bords. 
 * \param    int n : désigne le nombre de ligne de la matrice, la largeur du terrain.
 * \param   int p : désigne le nombre de colonne de la matrice, la longueur du terrain.
 * \return     Cette fonction retourne une matrice avec des 0 partouts et des 1 sur les bords. 
 */
matrix create_terrain (int n,int p);

/**
 * \fn           cons(serpent l, triplet nvelt)
 * \brief       Cette fonction concatène un triplet à un serpent qui est une liste de triplet
 * \details    Cette fonction concatène un triplet à une liste de triplet qui désigne un serpent.
 * \param    serpent l : désigne le serpent
 * \param   triplet nvelt : désigne un triplet
 * \return     Cette fonction retourne un serpent concaténé à un nouvel élément
 */
serpent cons(serpent l, triplet nvelt);

/**
 * \fn           reverse(serpent s)
 * \brief       Cette fonction inverse un serpent
 * \details    Un serpent étant une liste de triplet, cette fonction inverse les éléments du serpent
 * \param    serpent s : désigne un serpent
 * \return     Cette fonction retourne un serpent inversé
 */
serpent reverse(serpent s);
int test(serpent s, int dir, matrix M);


#endif