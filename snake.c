/**
 * @file snake.c
 * 
 * @brief construction du jeu snake
 *
 * @author Groupe 9
 * 
 * @version 1.0
 * 
 * @date 14 Fevrié 2016
 */


#include "snake.h"


matrix allocmatrice (int n,int p) 
{
	matrix res;
	res.lig=n;
	res.col=p;
	int i;
	res.mat= malloc (n* sizeof (int*));
	for (i=0; i<n; i++) 
	{
		res.mat[i]=malloc(p* sizeof (int));
	}
	return res;
}


matrix create_terrain(int n, int p) 
{
	matrix M = allocmatrice(n,p);
	int i,j;
	for (i=0; i<n; i++)
	{
		for (j=0; j<p; j++) 
		{
			M.mat[i][j]=0;
			if(i==0 || i==n-1 || j==0 || j==p-1)
			{
				M.mat[i][j]=1;
			}
		}
	}
	return M;
}
void affiche (matrix M)
{
	int i,j;
	int n=M.lig; int p=M.col;
	for (i=0; i<n; i++) 
	{
		for (j=0; j<p; j++)
		{
			printf("%3d", M.mat[i][j]);
		}
		printf("\n");
	}
}

void free_serpent(serpent s)
{
	while (s != NULL)
	{
		free(&(s->tete));
		s = s->queue;
	}
	s = NULL;
}

couple queue_serpent(serpent s)
{
    serpent aux = s;
    while (aux->queue != NULL)
        aux = aux->queue;
    couple c = {aux->tete.x, aux->tete.y};

    return c;
}

void affiche_serpent(serpent s)
{
	serpent t = s;
	printf("\n");
	while (t!=NULL)
	{
		printf("( %d, %d, %d)", t->tete.x, t->tete.y, t->tete.z);
		t = t->queue;
	}
	printf("\n");
}



void blit(matrix map , SDL_Surface* ecran , tabl_obj tab)
{
	int i,j;
	SDL_Rect pos; 
	for (i=0 ; i<map.lig ; i++)
	{
		for (j=0 ; j<map.col ;j++)
		{
			pos.x = j*30;
			pos.y = i*30;
			SDL_BlitSurface(tab.obj[0], NULL, ecran, &pos);
			SDL_BlitSurface(tab.obj[map.mat[i][j]], NULL, ecran, &pos);
		}
	}
}

matrix pose_serpent(serpent s1, matrix M)
{
	triplet c;
	while(s1 != NULL)
	{
		c = s1->tete;
		M.mat[c.x][c.y]=c.z;
		s1 = s1->queue;
	}
	return M;
}



serpent cons(serpent l, triplet nvelt)
{
	serpent p;
	p = malloc(sizeof(struct maillon));
	p->tete = nvelt;
	p->queue = l;
	return p;
}

serpent reverse(serpent s)
{
	serpent t = NULL;
	while (s!=NULL)
	{
		t = cons(t, s->tete);
		s = s->queue;
	}
	free_serpent(s);
	return t;
}


//Entier direction prenant les valeurs 1,2,3,4 (pavé num) qui indique la direction
//à prendre



serpent decale(serpent s, triplet nouvtete, int nouvmaillon)
{
	triplet t; serpent s2 = NULL;
	//On lui crée sa tête
	t = nouvtete;
	s2 = cons(s2, t);
	//On lui crée son premier maillon
	t.x = s->tete.x; t.y = s->tete.y; t.z = nouvmaillon;
	
	//On lui décale tous les maillons jusqu'à la queue
	if (s->queue != NULL)
	{
		s = s->queue;
		s2 = cons(s2, t);
		while (s->queue->queue != NULL)
		{
				s2 = cons(s2, s->tete);
				s = s->queue;
		}
	}
	
	//On lui crée sa nouvelle queue
	t.x = s->tete.x; t.y = s->tete.y;
	t.z = 11;
	if ((s->tete.z == 10 && s->queue->tete.z == 6) || 
			(s->tete.z == 14 && s->queue->tete.z == 9) ||
			(s->tete.z == 15 && s->queue->tete.z == 8))
	{
			t.z = 6;
	}
	if ((s->tete.z == 10 && s->queue->tete.z == 7) || 
			(s->tete.z == 13 && s->queue->tete.z == 9) ||
			(s->tete.z == 12 && s->queue->tete.z == 8))
	{
			t.z = 7;
	}
	if ((s->tete.z == 11 && s->queue->tete.z == 8) || 
			(s->tete.z == 13 && s->queue->tete.z == 6) ||
			(s->tete.z == 14 && s->queue->tete.z == 7))
	{
			t.z = 8;
	}
	if ((s->tete.z == 11 && s->queue->tete.z == 9) || 
			(s->tete.z == 12 && s->queue->tete.z == 6) ||
			(s->tete.z == 15 && s->queue->tete.z == 7))
	{
			t.z = 9;
	}
	
	s2 = cons(s2, t);
	s2 = reverse(s2);
	return s2;
}

// 0 = Herbe
// 1 = Bord
// 2 = serpent1_tête_haut
// 3 = serpent1_tête_bas
// 4 = serpent1 _tête_droite
// 5 = serpent1_tête_gauche
// 6 = s1_queue_haut
// 7 = s1_queue_bas
// 8 = s1 queue droite
// 9 = s1 queu gauche
// 10 = s1 tronc v
// 11 = s1 tronc h
// 12 = s1 coude 1
// 13 = s1 coude 2
// 14 = s1 coude 3
// 15 = s1 coude 4


serpent nouveau_serpent(serpent s, int direc, int nouvdirec)
{
	triplet t;
	t.x = s->tete.x;
	t.y = s->tete.y;
	if (direc == 1)
	{
		if (nouvdirec == 1 || nouvdirec == 3)
		{
			t.y = s->tete.y - 1;
			t.z = 5;
			s = decale(s, t, 11);
		}
		if (nouvdirec == 2)
		{
			t.x = s->tete.x + 1;
			t.z = 3;
			s = decale(s, t, 13);
		}
		if (nouvdirec == 4)
		{
			t.x = s->tete.x - 1;
			t.z = 2;
			s = decale(s, t, 14);
		}
	}
	if (direc == 2)
	{
		if (nouvdirec == 2 || nouvdirec == 4)
		{
			t.x = s->tete.x + 1;
			t.z = 3;
			s = decale(s, t, 10);
		}
		if (nouvdirec == 1)
		{
			t.y = s->tete.y - 1;
			t.z = 5;
			s = decale(s, t, 15);
		}
		if (nouvdirec == 3)
		{
			t.y = s->tete.y + 1;
			t.z = 4;
			s = decale(s, t, 14);
		}
	}
	if (direc == 3)
	{
		if (nouvdirec == 1 || nouvdirec == 3)
		{
			t.y = s->tete.y + 1;
			t.z = 4;
			s = decale(s, t, 11);
		}
		if (nouvdirec == 2)
		{
			t.x = s->tete.x + 1;
			t.z = 3;
			s = decale(s, t, 12);
		}
		if (nouvdirec == 4)
		{
			t.x = s->tete.x - 1;
			t.z = 2;
			s = decale(s, t, 15);
		}
	}
	if (direc == 4)
	{
		if (nouvdirec == 2 || nouvdirec == 4)
		{
			t.x = s->tete.x - 1;
			t.z = 2;
			s = decale(s, t, 10);
		}
		if (nouvdirec == 1)
		{
			t.y = s->tete.y - 1;
			t.z = 5;
			s = decale(s, t, 12);
		}
		if (nouvdirec == 3)
		{
			t.y = s->tete.y + 1;
			t.z = 4;
			s = decale(s, t, 13);
		}
	}
	return s;
}

int test(serpent s, int dir, matrix M)
{
	triplet t = s->tete;
	switch (dir)
	{
		case 1 : 
		if (M.mat[t.x][t.y-1] != 0 && M.mat[t.x][t.y-1] < 30) {return 0;} break;
		case 2 : 
		if (M.mat[t.x+1][t.y] != 0 && M.mat[t.x+1][t.y] < 30) {return 0;} break;
		case 3 : 
		if (M.mat[t.x][t.y+1] != 0 && M.mat[t.x][t.y+1] < 30) {return 0;} break;
		case 4 : 
		if (M.mat[t.x-1][t.y] != 0 && M.mat[t.x-1][t.y] < 30) {return 0;} break;
		default : return 0;
	}
	return 1;
}

serpent construit_serpent(int n, int snake, matrix M) {
	serpent s=NULL;
	int c = n / 2;
	if (snake==1)
	{
		triplet t;
		t.x=4; t.y=M.col/2 + c; t.z=4;
		s=cons(s,t);
		int i;
		t.z = 11;
		for (i = n; i>2; i--)
		{
			t.y = t.y-1;
			s=cons(s,t);
		}
		t.x = 4; t.y = t.y - 1; t.z=8;
		s=cons(s,t);
	}
	if (snake==1)
	{
		triplet t;
		t.x=M.lig-4; t.y=M.col/2 - c; t.z=19;
		s=cons(s,t);
		t.z = 25;
		int i;
		for (i = n; i>2; i--)
		{
			t.y = t.y+1;
			s=cons(s,t);
		}
		t.y = t.y+1; t.z=23;
		s=cons(s,t);
	}
	s = reverse(s);
	return(s);
}