#include "bonus.h"

int FPS = 150;
int continuer=1;
int entier_fin_partie = 0;
int inverse = 0;


void genere_bonus(matrix M, int compt_bonus, int type_genere)
{
	int i,x,y;
	for (i=0 ; i<compt_bonus ; i++)
	{
		do
		{
			x = rand()%(M.lig-2)+1;
			y = rand()%(M.col-2)+1;
		}while(M.mat[x][y] != 0);
		M.mat[x][y] = type_genere;
	}
}


serpent rallonge_serpent(serpent s_new, serpent s_old)
{
	triplet old_body,old_tail;

	s_old = reverse(s_old);
	s_new = reverse(s_new);

	old_tail = s_old->tete; 
	old_body = s_old->queue->tete;

	s_new->tete = old_body;
	s_new = cons(s_new, old_tail);

	return reverse(s_new);
}


serpent raccourcie_serpent(serpent s, matrix* M)
{
	if (s->queue->queue->queue == NULL)
	{
		int a = s->tete.z;
		if ( a <= 5 && a >= 2 )
		{
			entier_fin_partie = 0;
			continuer = 0;
		}
		else
		{
			entier_fin_partie = 1;
			continuer = 0;
		}
		
		return NULL;
	}
	else
	{
		s = reverse(s);
		s = s->queue;
		triplet t = s->tete;

		M->mat[t.x][t.y]=0;
		s = s->queue;


		if ((s->tete.z == 12 || s->tete.z == 13 || s->tete.z == 10)  //Coude 1, 2, v
			&& (s->tete.x > t.x))
			t.z = 7; //haut
		if ((s->tete.z == 14 || s->tete.z == 15 || s->tete.z == 10)  //Coude 3, 4, v
			&& (s->tete.x < t.x))
			t.z = 6; //bas
		if ((s->tete.z == 15 || s->tete.z == 12 || s->tete.z == 11)  //Coude 1, 4, h
			&& (s->tete.y > t.y))
			t.z = 8; //droite
		if ((s->tete.z == 14 || s->tete.z == 13 || s->tete.z == 11)  //Coude 2, 3, h
			&& (s->tete.y < t.y))
			t.z = 9; //gauche

		if ((s->tete.z == 26 || s->tete.z ==27 || s->tete.z == 24)
			&& (s->tete.x > t.x))
			t.z = 21;
		if ((s->tete.z == 28 || s->tete.z ==29 || s->tete.z == 24)
			&& (s->tete.x < t.x))
			t.z = 20;
		if ((s->tete.z == 29 || s->tete.z ==26 || s->tete.z == 25)
			&& (s->tete.y > t.y))
			t.z = 22;
		if ((s->tete.z == 28 || s->tete.z ==27 || s->tete.z == 25)
			&& (s->tete.y < t.y))
			t.z = 23;

		s = cons(s,t);

		return reverse(s);
	}
}


serpent collision_bonus(matrix M, serpent s_new, serpent s_old, int_tab* temp_tab, Mix_Chunk* son)
{
    int x = (s_new->tete).x;
    int y = (s_new->tete).y;

    switch(M.mat[x][y])
    {
        case 30 : s_new = rallonge_serpent(s_new, s_old);(*temp_tab).tabl[0]--;
        son = Mix_LoadWAV("Pomme.wav");break;
        case 31 : s_new = raccourcie_serpent(s_new,&M);(*temp_tab).tabl[1]--;
        son = Mix_LoadWAV("Radio.wav");break;
        case 32 : FPS= (int) (((float) FPS) / 1.5); (*temp_tab).tabl[2]=0;
        son = Mix_LoadWAV("Slow.wav");break;
        case 33 : FPS = (int) (((float) FPS) * 1.5);(*temp_tab).tabl[3]=0;
        son = Mix_LoadWAV("Slow.wav");break;
        case 34 : if(s_new->tete.z <=5)
        {
        	inverse++;(*temp_tab).tabl[2]--;(*temp_tab).tabl[4] = 0 ; 
        	son = Mix_LoadWAV("Inverse.wav");
        }
        break;
        default: break;
    }
    Mix_PlayChannel(1, son, 0);
    return s_new;
}