/**
 * @file min-max.c
 * 
 * @brief algorithme de l'intelligence artificiel du shlanga
 *
 * @author Groupe 9
 * 
 * @version 1.0
 * 
 * @date 1 avril 2016
 */


#include "min-max.h"
#include "snake.h"
#include "shlanga.h"

liste cons_liste(liste l, int a)
{
	liste p;
	p = malloc(sizeof(struct liste));
	p->tete = a;
	p->queue = l;
	return p;
}

int nb_elm_liste(liste l)
{
	int compt = 0;
	while (l!=NULL)
	{
		compt++;
		l = l->queue;
	}
	return compt;
}


void affiche_liste(liste l)
{
	while (l != NULL)
	{
		printf("%d ", l->tete);
		l = l->queue;
	}
	printf("\n");
}

void free_mat(matrix M)
{
	int i;
    for (i=0; i<M.lig; i++) 
        free(M.mat[i]);
  	free(M.mat);
}



/*
Un fonction distance qui donne simplement la distance
entre deux points.
*/

int dist(couple p1, couple p2)
{
	return (abs(p1.x-p2.x) + abs(p1.y-p2.y));
}

/*
On donne une direction, un serpent et une matrice et on renvoie si la direction est envisageable
*/

int envisageable(int direc, serpent s, matrix M)
{
	if (test(s, direc, M) && (((direc+1)%4)+1 != direc_serpent(s)))
		return 1;
	else
		return 0;
}

/*
Renvoie dans un tableau les directions accessibles à partir d'une tête de serpent
*/


liste accessibles(serpent s, matrix M)
{
	int direc = direc_serpent(s);
	liste l = NULL;

	if (test(s, direc, M))
		l = cons_liste(l, direc);
	if (test(s, direc%4+1, M))
		l = cons_liste(l, direc%4+1);
	if (test(s, (direc+2)%4+1, M))
		l = cons_liste(l, (direc+2)%4+1);
	
	return l;
}

/*
La fonction éval prends en argument un premier serpent (shlanga), un second (snake) et M.
Elle renvoie la valeur de la configuration, c'est à dire un entier qui nous dit si la situation est bonne où non.
Ici, il sera calculé en fonction du nombre de cases disponibles pondéré par un valeur val_case_dispo autour de la tête du serpent, 
et sa distance à l'autre serpent.
*/


int distance_au_mur(serpent s, matrix M)
{
	int res = 1000;
	couple c = {s->tete.x, s->tete.y};
	int aux = 1;
	
	while (M.mat[c.x+aux][c.y] != 1)
	{
		aux ++;
	}
	if (res > aux)
		res = aux;
	aux = 1;

	while (M.mat[c.x-aux][c.y] != 1)
	{
		aux ++;
	}
	if (res > aux)
		res = aux;
	aux = 1;

	while (M.mat[c.x][c.y+aux] != 1)
	{
		aux ++;
	}
	if (res > aux)
		res = aux;
	aux = 1;

	while (M.mat[c.x][c.y-aux] != 1)
	{
		aux ++;
	}
	if (res > aux)
		res = aux;
	aux = 1;

	return res;
}

int eval(serpent s1, serpent s2, matrix M)
{
	int nombre_cases_dispo = 0;
	couple c1, c2;
	c1.x = s1->tete.x; c1.y = s1->tete.y; 
	c2.x = s2->tete.x; c2.y = s2->tete.y;

	//La valeur que l'on désire donner au fait "une case de plus est disponible"
	//par rapport à la distance.
	int val_case_dispo = 8;
	int val_distance = 1;
	int val_distance_au_mur = 2;

	//On compte les cases vides autour de la tête du serpent
	liste l = accessibles(s1, M);
	nombre_cases_dispo = nb_elm_liste(l);

	free(l);

	//On regarde si la position visitée ne propose pas de case
	//pour partir
	if (nombre_cases_dispo == 0)
	{
		//Si c'est le cas, elle est très mauvaise et sera comptée comme pire possible
		//car synonime de défaite
		return 0;
	}
	else
	{
		//Sinon, on retourne le nombre de cases disponibles X val_case_dispo
		return nombre_cases_dispo*val_case_dispo 
		+ dist(c1, c2)*val_distance
		+ distance_au_mur(s1,M)*val_distance_au_mur;
	}
}

int eval_aggro(serpent s1, serpent s2, matrix M)
{
	int nombre_cases_dispo = 0;
	int nombre_cases_dispo_ennemies = 0;
	couple c1, c2;
	c1.x = s1->tete.x; c1.y = s1->tete.y; 
	c2.x = s2->tete.x; c2.y = s2->tete.y;

	//La valeur que l'on désire donner au fait "une case de plus est disponible"
	//par rapport à la distance.
	int val_case_dispo = 8;
	int val_case_dispo_ennemies = 2;
	int val_distance = 2;
	int val_distance_au_mur = 5;
	int val_distance_au_mur_ennemi = 0;

	//On compte les cases vides autour de la tête du serpent
	nombre_cases_dispo = nb_elm_liste(accessibles(s1, M));
	nombre_cases_dispo_ennemies = nb_elm_liste(accessibles(s2, M));
	

	//On regarde si la position visitée ne propose pas de case
	//pour partir
	if (nombre_cases_dispo == 0)
	{
		//Si c'est le cas, elle est très mauvaise et sera comptée comme pire possible
		//car synonime de défaite
		return 0;
	}
	else if (nombre_cases_dispo_ennemies == 0)
	{
		//Si c'est le cas, elle est très mauvaise et sera comptée comme pire possible
		//car synonime de défaite
		return 1000;
	}
	else
	{
		return 300
			+ nombre_cases_dispo * val_case_dispo
			- nombre_cases_dispo_ennemies * val_case_dispo_ennemies
			- dist(c1, c2) * val_distance
			+ distance_au_mur(s1,M) * val_distance_au_mur
			- distance_au_mur(s2,M) * val_distance_au_mur_ennemi;
	}
}

/*
Renvoie la direction d'un serpent en fonction de la valeur de sa tête
*/

int direc_serpent(serpent s)
{
	switch (s->tete.z)
	{
		case 2 : return 4;
		case 3 : return 2;
		case 4 : return 3;
		case 5 : return 1;
		case 16 : return 4;
		case 17 : return 2;
		case 18 : return 3;
		case 19 : return 1;
	}
	printf ("problème direc_serpent");
	return 1;
}





/*
Fonction qui crée le meilleur serpent (controlé par le joueur) en fonction d'une configuration donnée.
*/

int meilleur_snake(serpent s1, serpent s2, matrix M)
{
	//On parcours les directions accessibles pour s1 et on regarde laquelle donne la pire eval à s2, puis on la choisit
	int val = 1000;
	int meilleur_direc = 0;
	int direc = direc_serpent(s2);

	//Ici, comme dans la fonction précédente, s1 = shlanga et s2 = snake
	int i;
	for (i=1; i<5; i++)
	{
		s2 = nouveau_serpent_2(s2, direc, i);
		s2 = s2;
		if (eval(s1, nouveau_serpent_2(s2, direc, i), M) < val && envisageable(i, s2, M))
		{
			meilleur_direc = i;
			s2 = s2;
			val = eval(s1, nouveau_serpent_2(s2, direc, i), M);
		}
	}


	return meilleur_direc;
}




matrix remplis_matrice(serpent s1, serpent s2, matrix M)
{
	matrix M2 = create_terrain(M.lig, M.col); //Créer une fonction qui crée une matrice en fonction d'une autre en 
	//effaçant ses serpents
    M2 = pose_serpent(s1, M2);
    M2 = pose_serpent(s2, M2);
    return M2;
}


int max(int* tab, int len)
{
	int val = 0;
	int i;
	for (i=0; i<len; i++)
	{
		if (tab[i]>val)
			val = tab[i];
	}

	return val;
}



/*
Fonction récursive. On observe les coups possibles, on calcul avec "eval"
le meilleur, et le meilleur pour l'adversaire. On rappelle la fonction sur 
cette configuration. On s'arrête lorsque le compteur, initialisé à 0, arrive 
à n, notre longueur d'essais.
*/

int jouer(serpent s1, serpent s2, matrix M, int compt, int n, int* res, int type_dia)
{
	if (compt == n)
	{
		//On renvoie la valeur de la configuration finale
		//après avoir free la matrice et les serpents

		int k;
		if (type_dia)
			k = eval_aggro(s1, s2, M);
		else
			k = eval(s1, s2, M);

		free_mat(M);
		//free_serpent(s2);
		free_serpent(s1);

		return k;
	}
	else
	{
		//On crée deux serpent pour chaque configuration visitée, et on les mets dans une matrice
		//En fonction de la tête du serpent, on a à visiter jusqu'à 3 configurations.
		//Pour chacune, on test déjà si la direction est accessible. 



		//On crée une liste des directions accessibles, en prenant compte des obstacles 
		//et de l'interdiction de faire demi tour
		liste liste_accessibles = accessibles(s1, M);


		//On stock sa longueur
		int nb_accessibles = nb_elm_liste(liste_accessibles);

		//On crée des tableaux de serpents, qui contiendront les serpents hypothétiques pour 
		//chaque configuration 
		serpent tab_serpent1[nb_accessibles];
		serpent tab_serpent2[nb_accessibles];
		//Et une matrice qui les contiendra
		matrix tab_mat[nb_accessibles];
		//Ainsi qu'un tableau d'entiers
		int evalu[nb_accessibles];

		int i = 0;


		//Si nous sommes au premier coup hypothétique et qu'il n'y a pas d'accessibles, c'est
		//la défaite pour le Shlanga, et la victoire du joueur
		if (compt == 0 && nb_accessibles == 0)
		{
			extern int continuer;
			continuer = 0;
			extern int entier_fin_partie;
			entier_fin_partie = 1;
			*res = 0;
			return 0;
		}
		else
		{
			//On parcours maintenant la liste des accessibles
			while (liste_accessibles != NULL)
			{
				//On crée un nouveau serpent en fonction de l'ancienne direction et de celle choisie
				tab_serpent1[i] = nouveau_serpent_2(s1, direc_serpent(s1), liste_accessibles->tete);
	
				//On crée le snake hypothétique associé via meilleur_snake
				/*if (nb_elm_liste(accessibles(s2, M)) > 1)
					tab_serpent2[i] = nouveau_serpent(s2, direc_serpent(s2), meilleur_snake(tab_serpent1[i], s2, M));
				else*/
					tab_serpent2[i] = s2;

				//On place nos serpents dans la matrice
				tab_mat[i] = remplis_matrice(tab_serpent1[i],tab_serpent2[i],M);
	
				//On rappelle la fonction jouer sur cette nouvelle configuration
				evalu[i] = jouer(tab_serpent1[i], tab_serpent2[i], tab_mat[i], compt+1, n, res, type_dia);
	
				i++;
				liste_accessibles = liste_accessibles->queue;
			}
	
	
			//On trouve dans notre tableau la plus grande valeur d'évaluation
			int meilleure_direc = max(evalu, nb_accessibles);
	
			//On recherche à quel coup cette valeur est associée
			for (i=0; i<nb_accessibles; i++)
			{
				if (meilleure_direc == evalu[i] && compt == 0)
				{
					//Et on le stock dans res
					*res = direc_serpent(tab_serpent1[i]);
				}
			}
	
	
	
			return meilleure_direc;
		}
	}
}


/*
On prends en argument les serpent, la matrice et un entier n, on renvoie la direction
à prendre pour arriver à la meilleure configuration au nieme coup.
*/
int coup_a_jouer(serpent s1, serpent s2, matrix M, int n, int type_dia)
{
	int* res = malloc(sizeof(int));


	*res = 4;

	jouer(s1, s2, M, 0, n, res, type_dia);


	return *res;
}


int direc_random(serpent s, matrix M, SDL_Surface* ecran)
{
    liste l = accessibles(s, M);
    int nb_accessibles = nb_elm_liste(l);

    if (nb_accessibles == 0)
    {
        extern int continuer;
        continuer = 0;
        extern int entier_fin_partie;
        entier_fin_partie = 1;
        return 0;
    }

    int r = rand()%nb_accessibles;
    while (r != 0)
    {
        l = l->queue;
        r--;
    }
        
    return l->tete;
}
