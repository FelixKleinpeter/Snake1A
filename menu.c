
#include "menu.h"









Bouton creer_bouton(int x, int y, int hauteur, int largeur, char* texte_en_char, int r, int v, int b, TTF_Font *police, SDL_Surface* ecran, char* image)
{
	Bouton res;

	SDL_Color couleur_texte = {r/2, v/2, b/2};
	SDL_Surface *fond = NULL, *texte = NULL;
	police = TTF_OpenFont("Super Mario Bros..ttf", hauteur);
    fond = IMG_Load(image);
    texte = TTF_RenderText_Blended(police, texte_en_char, couleur_texte);

    res.x = x; res.y = y; res.hauteur = hauteur; res.largeur = largeur;
    res.texte = texte; res.fond = fond;

    return res;
}



void blit_bouton(Bouton b, SDL_Surface* ecran, SDL_Surface* aux)
{
	SDL_Rect position;

    position.x = b.x;
	position.y = b.y;
	SDL_BlitSurface(b.fond, NULL, ecran, &position);

	position.x = b.x+b.largeur/8;
	position.y = b.y+b.hauteur/8;
	SDL_BlitSurface(b.texte, NULL, ecran, &position);
}

void bliter_les_boutons(Bouton* tableau_de_boutons, int taille, SDL_Surface* ecran, SDL_Surface* aux)
{
	int i;
	for (i = 0; i < taille; ++i)
	{
		blit_bouton(tableau_de_boutons[i], ecran, aux);
	}
}

Bouton trouver_bouton(SDL_Event event, Bouton* tableau_de_boutons, int taille, SDL_Surface* ecran)
{
	int i;
	Bouton b;
	for (i = 0; i<taille; i++)
	{
		b = tableau_de_boutons[i];
		if ((b.x <= event.button.x && event.button.x <= b.x + b.largeur)
			&& (b.y <= event.button.y && event.button.y <= b.y + b.hauteur))
			return b;
	}

	char a[1];
	TTF_Font *p = TTF_OpenFont("Super Mario Bros..ttf", 1);
	b = creer_bouton(0,0,0,0,a,0,0,0,p,ecran,"Bouton.png");
	return b;

}

int egal_bouton(Bouton b, Bouton c)
{
	return (b.x == c.x && b.y == c.y);
}

void free_bouton(Bouton b)
{
	SDL_FreeSurface(b.texte);
	SDL_FreeSurface(b.fond);
}


/*
Menu 1 :
- Shlangà défensif :
	-> Taille plateau
	-> Taille serpents
- Shlangà fou :
	-> Taille plateau
	-> Taille serpents
- Quitter
*/

quadruplet menu(SDL_Surface *ecran)
{
	SDL_Surface *aux = NULL;
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 30, 170, 50));
	SDL_Event event;

	SDL_Surface* image_de_fond = IMG_Load("Menu.jpg");
	SDL_Rect position_fond;
	position_fond.x = position_fond.y = 0;

	//0 = menu de base
	//1 = shl def
	//2 = shl fou

	int longueur_plateau = 23;
	int largeur_plateau = 40;
	int longueur_serpent = 10;
	int type_dia = 0;
	

	//Création des boutons :
	char tex[100];
	TTF_Font *police = NULL;
	int taille_tableau_boutons = 4;
	Bouton tableau_de_boutons[taille_tableau_boutons];
	Bouton b;

	SDL_Surface *note = NULL, *note_couleur = NULL;
	SDL_Rect position_note; position_note.x = 260; position_note.y = 185;
	SDL_Rect position_note_couleur; position_note_couleur.x = 420; position_note_couleur.y = 460;
	SDL_Color couleur_texte = {0, 20, 0}; 
	police = TTF_OpenFont("Mayan.ttf", 20);

	sprintf(tex, "Clic gauche pour augmenter, clic droit pour diminuer!");
    note = TTF_RenderText_Blended(police, tex, couleur_texte);
    sprintf(tex, "Votre Snake est le vert!");
    note_couleur = TTF_RenderText_Blended(police, tex, couleur_texte);



	//Menu 1
	sprintf(tex, "Shlanga defensif");
	Bouton shlanga_def = creer_bouton(260,230,35,465,tex, 15, 85, 25, police, ecran, "Bouton.png");
	tableau_de_boutons[0] = shlanga_def;

	sprintf(tex, "Shlanga fou");
	Bouton shlanga_fou = creer_bouton(325,315,35,350,tex, 15, 85, 25, police, ecran, "Bouton.png");
	tableau_de_boutons[1] = shlanga_fou;

	sprintf(tex, "Shlanga offensif");
	Bouton shlanga_offensif = creer_bouton(260,400,35,465,tex, 15, 85, 25, police, ecran, "Bouton.png");
	tableau_de_boutons[2] = shlanga_offensif;

	sprintf(tex, "Quitter");
	Bouton quitter = creer_bouton(392,485,35,300,tex, 15, 85, 25, police, ecran, "Bouton.png");
	tableau_de_boutons[3] = quitter;

	//Menu 2
	/*
	Taille plateau : x, y
	On monte et descend avec clic gauche et droits
	Idem taille serpents
	*/
	sprintf(tex, "Longueur plateau : %d", longueur_plateau);
	Bouton longueur = creer_bouton(245,230,30,465,tex, 15, 85, 25, police, ecran, "Bouton.png");
	

	sprintf(tex, "Largeur plateau : %d", largeur_plateau);
	Bouton largeur = creer_bouton(250,315,30,465,tex, 15, 85, 25, police, ecran, "Bouton.png");
	

	sprintf(tex, "Longueur serpents : %d", longueur_serpent);
	Bouton longueur_ser = creer_bouton(240,400,30,465,tex, 15, 85, 25, police, ecran, "Bouton.png");

	sprintf(tex, "Jouer!");
	Bouton jouer = creer_bouton(392,485,40,465,tex, 15, 85, 25, police, ecran, "Bouton.png");
	
	int conti = 1;
	int niveau_de_menu = 0;


	

	while (conti)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT : exit(1); break;

            case SDL_MOUSEBUTTONDOWN:

				if (egal_bouton(trouver_bouton(event, tableau_de_boutons, 
					taille_tableau_boutons, ecran), 
					//Bouton que l'on veut trouver
					shlanga_def) && niveau_de_menu == 0)
				{
					sprintf(tex, "Shlanga defensif");
					b = shlanga_def;
					tableau_de_boutons[0] = creer_bouton(b.x,b.y,b.hauteur,b.largeur,tex, 22, 150, 30, police, ecran, "Bouton.png");
				}
				
				if (egal_bouton(trouver_bouton(event, tableau_de_boutons, 
					taille_tableau_boutons, ecran), 
					//Bouton que l'on veut trouver
					shlanga_fou) && niveau_de_menu == 0)
				{
					sprintf(tex, "Shlanga fou");
					b = shlanga_fou;
					tableau_de_boutons[1] = creer_bouton(b.x,b.y,b.hauteur,b.largeur,tex, 22, 150, 30, police, ecran, "Bouton.png");
				}
				
				if (egal_bouton(trouver_bouton(event, tableau_de_boutons, 
					taille_tableau_boutons, ecran), 
					//Bouton que l'on veut trouver
					shlanga_offensif) && niveau_de_menu == 0)
				{
					sprintf(tex, "Shlanga offensif");
					b = shlanga_offensif;
					tableau_de_boutons[2] = creer_bouton(b.x,b.y,b.hauteur,b.largeur,tex, 22, 150, 30, police, ecran, "Bouton.png");
				}

				if (egal_bouton(trouver_bouton(event, tableau_de_boutons, 
					taille_tableau_boutons, ecran), 
					//Bouton que l'on veut trouver
					quitter) && niveau_de_menu == 0)
				{
					sprintf(tex, "Quitter");
					b = quitter;
					tableau_de_boutons[3] = creer_bouton(b.x,b.y,b.hauteur,b.largeur,tex, 22, 150, 30, police, ecran, "Bouton.png");
				}



				if (egal_bouton(trouver_bouton(event, tableau_de_boutons, 
					taille_tableau_boutons, ecran), 
					//Bouton que l'on veut trouver
					longueur) && niveau_de_menu)
				{
					sprintf(tex, "Longueur plateau : %d", longueur_plateau);
					b = longueur;
					tableau_de_boutons[0] = creer_bouton(b.x,b.y,b.hauteur,b.largeur,tex, 22, 150, 30, police, ecran, "Bouton.png");
				}
				if (egal_bouton(trouver_bouton(event, tableau_de_boutons, 
					taille_tableau_boutons, ecran), 
					//Bouton que l'on veut trouver
					largeur) && niveau_de_menu)
				{
					sprintf(tex, "Largeur plateau : %d", largeur_plateau);
					b = largeur;
					tableau_de_boutons[1] = creer_bouton(b.x,b.y,b.hauteur,b.largeur,tex, 22, 150, 30, police, ecran, "Bouton.png");
				}
				if (egal_bouton(trouver_bouton(event, tableau_de_boutons, 
					taille_tableau_boutons, ecran), 
					//Bouton que l'on veut trouver
					longueur_ser) && niveau_de_menu)
				{
					sprintf(tex, "Longueur serpents : %d", longueur_serpent);
					b = longueur_ser;
					tableau_de_boutons[2] = creer_bouton(b.x,b.y,b.hauteur,b.largeur,tex, 22, 150, 30, police, ecran, "Bouton.png");
				}

				if (egal_bouton(trouver_bouton(event, tableau_de_boutons, 
					taille_tableau_boutons, ecran), 
					//Bouton que l'on veut trouver
					jouer) && niveau_de_menu)
				{
					sprintf(tex, "Jouer!");
					b = jouer;
					tableau_de_boutons[3] = creer_bouton(b.x,b.y,b.hauteur,b.largeur,tex, 22, 150, 30, police, ecran, "Bouton.png");
				}
				break;


			case SDL_MOUSEBUTTONUP:

				

				if (egal_bouton(trouver_bouton(event, tableau_de_boutons, 
					taille_tableau_boutons, ecran), 
					//Bouton que l'on veut trouver
					shlanga_def) && niveau_de_menu == 0)
				{
					sprintf(tex, "Shlanga defensif");
					b = shlanga_def;
					//Faire ce qu'il faut faire dans shlanga_def
					tableau_de_boutons[0] = longueur;
					tableau_de_boutons[1] = largeur;
					tableau_de_boutons[2] = longueur_ser;
					tableau_de_boutons[3] = jouer;

					niveau_de_menu = 1;
					type_dia = 0;

					
				}
				if (egal_bouton(trouver_bouton(event, tableau_de_boutons, 
					taille_tableau_boutons, ecran), 
					//Bouton que l'on veut trouver
					shlanga_fou) && niveau_de_menu == 0)
				{
					sprintf(tex, "Shlanga fou");
					b = shlanga_fou;
					//Faire ce qu'il faut faire dans shlanga_fou
					tableau_de_boutons[0] = longueur;
					tableau_de_boutons[1] = largeur;
					tableau_de_boutons[2] = longueur_ser;
					tableau_de_boutons[3] = jouer;

					niveau_de_menu = 1;
					type_dia = 1;

				}

				if (egal_bouton(trouver_bouton(event, tableau_de_boutons, 
					taille_tableau_boutons, ecran), 
					//Bouton que l'on veut trouver
					shlanga_offensif) && niveau_de_menu == 0)
				{
					sprintf(tex, "Shlanga offensif");
					b = shlanga_offensif;
					//Faire ce qu'il faut faire dans shlanga_offensif
					tableau_de_boutons[0] = longueur;
					tableau_de_boutons[1] = largeur;
					tableau_de_boutons[2] = longueur_ser;
					tableau_de_boutons[3] = jouer;

					niveau_de_menu = 1;
					type_dia = 2;

				}

				if (egal_bouton(trouver_bouton(event, tableau_de_boutons, 
					taille_tableau_boutons, ecran), 
					//Bouton que l'on veut trouver
					quitter) && niveau_de_menu == 0)
				{
					sprintf(tex, "Quitter");
					exit(0);
				}



				if (egal_bouton(trouver_bouton(event, tableau_de_boutons, 
					taille_tableau_boutons, ecran), 
					//Bouton que l'on veut trouver
					longueur) && niveau_de_menu)
				{
					if (event.button.button == SDL_BUTTON_LEFT && longueur_plateau <= 22)
						longueur_plateau++;
					else if (event.button.button == SDL_BUTTON_RIGHT && longueur_plateau >= 9)
						longueur_plateau--;
					sprintf(tex, "Longueur plateau : %d", longueur_plateau);
					b = longueur;
					tableau_de_boutons[0] = creer_bouton(b.x,b.y,b.hauteur,b.largeur,tex, 15, 85, 25, police, ecran, "Bouton.png");
					longueur = tableau_de_boutons[0];
				}

				else if (egal_bouton(trouver_bouton(event, tableau_de_boutons, 
					taille_tableau_boutons, ecran), 
					//Bouton que l'on veut trouver
					largeur) && niveau_de_menu)
				{
					if (event.button.button == SDL_BUTTON_LEFT && largeur_plateau <= 39)
						largeur_plateau++;
					else if (event.button.button == SDL_BUTTON_RIGHT && largeur_plateau >= 9 && largeur_plateau > longueur_serpent+8)
						largeur_plateau--;
					sprintf(tex, "Largeur plateau : %d", largeur_plateau);
					b = largeur;
					tableau_de_boutons[1] = creer_bouton(b.x,b.y,b.hauteur,b.largeur,tex, 15, 85, 25, police, ecran, "Bouton.png");
					largeur = tableau_de_boutons[1];
				}

				else if (egal_bouton(trouver_bouton(event, tableau_de_boutons, 
					taille_tableau_boutons, ecran), 
					//Bouton que l'on veut trouver
					longueur_ser) && niveau_de_menu)
				{
					if (event.button.button == SDL_BUTTON_LEFT && longueur_serpent <= 14 && longueur_serpent < largeur_plateau-8)
						longueur_serpent++;
					else if (event.button.button == SDL_BUTTON_RIGHT && longueur_serpent >= 7)
						longueur_serpent--;
					sprintf(tex, "Longueur serpents : %d", longueur_serpent);
					b = longueur_ser;
					tableau_de_boutons[2] = creer_bouton(b.x,b.y,b.hauteur,b.largeur,tex, 15, 85, 25, police, ecran, "Bouton.png");
					longueur_ser = tableau_de_boutons[2];
				}

				else if (egal_bouton(trouver_bouton(event, tableau_de_boutons, 
					taille_tableau_boutons, ecran), 
					//Bouton que l'on veut trouver
					jouer) && niveau_de_menu)
				{

					sprintf(tex, "Jouer");
					b = jouer;
					tableau_de_boutons[3] = creer_bouton(b.x,b.y,b.hauteur,b.largeur,tex, 15, 85, 25, police, ecran, "Bouton.png");
					jouer = tableau_de_boutons[3];
					conti = 0;
				}
				break;
        }
        
        SDL_BlitSurface(image_de_fond, NULL, ecran, &position_fond);
        if (niveau_de_menu)
        {
        	SDL_BlitSurface(note, NULL, ecran, &position_note);
        	SDL_BlitSurface(note_couleur, NULL, ecran, &position_note_couleur);
        }
        bliter_les_boutons(tableau_de_boutons, taille_tableau_boutons, ecran, aux);
        SDL_Flip(ecran);
    }


    TTF_CloseFont(police);

    free_bouton(jouer);
    free_bouton(longueur_ser);
    free_bouton(largeur);
    free_bouton(longueur);
    free_bouton(quitter);
    free_bouton(shlanga_def);
    free_bouton(shlanga_fou);
    free_bouton(shlanga_offensif);
    

	quadruplet q = {longueur_plateau, largeur_plateau, longueur_serpent, type_dia};

	return q;
}




int menu_fin(SDL_Surface *ecran)
{
    
	SDL_Surface *aux = NULL;
	SDL_Event event;

	if(TTF_Init() == -1)
        {perror("TTF_Init"); exit(1);}

	//Création des boutons :
	TTF_Font *police = NULL;
	int taille_tableau_boutons = 2;
	Bouton tableau_de_boutons[taille_tableau_boutons];


	char noms[taille_tableau_boutons][20];

	int x, y, z;

	x = (int) ((float) ecran->w* (0.3));
	y = (int) ((float) ecran->h* (0.5));
	z = (int) ((float) ecran->h* (0.04)) + (int) ((float) ecran->w* (0.04));

	strcpy(noms[0], "Menu");
	Bouton menu = creer_bouton(x,y,z,750,noms[0], 15, 85, 25, police, ecran, "Bouton.png");
	tableau_de_boutons[0] = menu;

	x = (int) ((float) ecran->w* (0.26));
	y = (int) ((float) ecran->h* (0.69));
	z = (int) ((float) ecran->h* (0.04)) + (int) ((float) ecran->w* (0.04));

	strcpy(noms[1], "Quitter");
	Bouton quitter = creer_bouton(x,y,z,800,noms[1], 15, 85, 25, police, ecran, "Bouton.png");
	tableau_de_boutons[1] = quitter;

	Bouton b;

	int res = 0;
	int conti = 1;
	int i;

	while (conti)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT : exit(1); break;
            case SDL_MOUSEBUTTONDOWN:

            	for (i = 0; i < taille_tableau_boutons; ++i)
            	{
            		b = tableau_de_boutons[i];
	            	if (egal_bouton(trouver_bouton(event, tableau_de_boutons, taille_tableau_boutons, ecran), b))
					{
						tableau_de_boutons[i] = creer_bouton(b.x,b.y,b.hauteur,b.largeur,noms[i], 22, 150, 30, police, ecran, "Bouton.png");
					}
				}

				break;
			case SDL_MOUSEBUTTONUP:

				if (egal_bouton(trouver_bouton(event, tableau_de_boutons, 
					taille_tableau_boutons, ecran), 
					menu))
				{
					res = 0;
					conti = 0;
				}

				if (egal_bouton(trouver_bouton(event, tableau_de_boutons, 
					taille_tableau_boutons, ecran), 
					quitter))
				{
					res = 1;
					conti = 0;
				}
				break;
        }
        bliter_les_boutons(tableau_de_boutons, taille_tableau_boutons, ecran, aux);
        SDL_Flip(ecran);
    }


    TTF_CloseFont(police);

    free_bouton(menu);
    free_bouton(quitter);
   

	return res;
}

