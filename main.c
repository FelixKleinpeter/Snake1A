
#include "snake.h"
#include "shlanga.h"
#include "min-max.h"
#include "bonus.h"
#include "menu.h"
#include "file.h"



void fin_de_partie(int type_de_fin_de_partie, SDL_Surface* ecran, int p, Mix_Music* musique)
{
    TTF_Font *police = NULL;
    SDL_Color couleur = {15, 85, 25};
    SDL_Surface* texte = NULL;
    SDL_Rect position_texte;
    position_texte.y = 120;
    position_texte.x = 4*p;

    
    police = TTF_OpenFont("Super Mario Bros..ttf", 5*p);

    char tex[20];

    if (type_de_fin_de_partie)
    {
        sprintf(tex, "Victoire");
        musique = Mix_LoadMUS("V.mp3");
    }


    else{
        sprintf(tex, "Defaite");
        musique = Mix_LoadMUS("D.mp3");
        }
    Mix_PlayMusic(musique, -1);
    texte = TTF_RenderText_Blended(police, tex, couleur);
    SDL_BlitSurface(texte, NULL, ecran, &position_texte);
    SDL_Flip(ecran);

    TTF_CloseFont(police);

    TTF_Quit();
}

couple jeu(SDL_Surface *ecran, tabl_obj tab, Mix_Music *musique)
{
    if(Mix_PlayMusic(musique, -1) == -1 )
    {
        perror("lecture");
    }
    ecran = SDL_SetVideoMode(1000, 625, 32, SDL_HWSURFACE);

    quadruplet q = menu(ecran);

    int n=q.x, p=q.y, type_dia = q.k;
    int longueur_serpents = q.z;
    ecran = SDL_SetVideoMode(p*30, n*30, 32, SDL_HWSURFACE);

    matrix M = create_terrain(n,p);

    triplet t = {1,1,11};
    serpent s1 = NULL;
    s1 = cons(s1, t);
    t.x = 1; t.y = 2; t.z = 4;
    s1 = cons(s1, t);
    
    
    serpent s2 = NULL;
    t.x = n-2; t.y = p-2; t.z = 25;
    s2 = cons(s2, t);
    t.x = n-2; t.y = p-3; t.z = 19;
    s2 = cons(s2, t);

    
    couple queue_aux;
    SDL_Rect pos;
    pos.x = pos.y = 0;

    int taille = 5;

    int compt = 0;
    int compt2=0;
    int r=0,r2=0,r3=0,p2=0;

    int_tab tab_temp;
    tab_temp.tabl = malloc(taille*sizeof(int*));
    tab_temp.taille = taille;
    int i2;
    for (i2=0 ; i2<taille ; i2++)
    {
        tab_temp.tabl[i2]=0;
    }

    SDL_Event event;
    int temps_actuel = 0;
    int temps_precedent = 0;
    int direc = 3;
    int nouvdirec = 3;
    int direc2 = 1;
    int nouvdirec2 = 3;



    extern int FPS;
    extern int continuer;
    extern int entier_fin_partie;
    extern int inverse;

    continuer = 1;
    FPS = 150;
    entier_fin_partie = 0;
    inverse = 0;

    serpent aux = NULL;

    file f = creer_file_vide(10);

    int a_joue = 0;

    int taille_des_serpents = 0;


    Mix_AllocateChannels(2);
    Mix_Chunk *son=NULL;

    while (continuer)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT : continuer = 0; break;
            case SDL_KEYUP:

            switch (event.key.keysym.sym)
            {
                case SDLK_UP: 
                if (inverse%2 == 0)
                    nouvdirec = 4; 
                else
                    nouvdirec = 2; 
                break;
                case SDLK_DOWN: 
                if (inverse%2 == 0)
                    nouvdirec = 2; 
                else
                    nouvdirec = 4; 
                break;
                case SDLK_RIGHT: 
                if (inverse%2 == 0)
                    nouvdirec = 3; 
                else
                    nouvdirec = 1; 
                break;
                case SDLK_LEFT: 
                if (inverse%2 == 0)
                    nouvdirec = 1; 
                else
                    nouvdirec = 3; 
                break;



                case SDLK_a:continuer = 0; break;
                default : break;
            }

            
            
            break;
            default : break;
        }

        if (nouvdirec != direc && !(a_joue))
        {
            a_joue = 1;
            ajout(&f, nouvdirec);
        }
  
        temps_actuel = SDL_GetTicks();
        if (temps_actuel - temps_precedent >= FPS)
        {
            if (taille_des_serpents < longueur_serpents-1)
            {
                t.x = 1; t.y = 1; t.z = 11;
                s1 = reverse(s1);
                s1 = cons(s1, t);
                s1 = reverse(s1);
                t.x = n-2; t.y = p-2; t.z = 25;
                s2 = reverse(s2);
                s2 = cons(s2, t);
                s2 = reverse(s2);
                taille_des_serpents++;
            }
            if (taille_des_serpents == longueur_serpents-1)
            {
                t.x = 1; t.y = 1; t.z = 8;
                s1 = reverse(s1);
                s1 = cons(s1, t);
                s1 = reverse(s1);
                t.x = n-2; t.y = p-2; t.z = 23;
                s2 = reverse(s2);
                s2 = cons(s2, t);
                s2 = reverse(s2);
                taille_des_serpents+=30;
            }




            if (a_joue)
                nouvdirec = retrait(&f);
            a_joue = 0;

            
            if ((nouvdirec+1)%4+1 == direc)
            {
                nouvdirec = direc;
            }

            temps_precedent = temps_actuel;

            r+=1;r2++;r3++; p2++;

            if (tab_temp.tabl[0] == 0 && p2>3)
            {
                compt++;
                genere_bonus(M,compt,30);
                tab_temp.tabl[0] = compt;
            }

            if (tab_temp.tabl[1] == 0 && p2>3)
            {
                compt2++;
                genere_bonus(M,compt2,31);
                tab_temp.tabl[1] = compt2;
            }

            if(tab_temp.tabl[2]==0 && r>70)
            {
                genere_bonus(M,1,32);
                tab_temp.tabl[2]=1;
                r = 0;
            }

            if(tab_temp.tabl[3] ==0 && r2 > 70)
            {
                genere_bonus(M,1,33);
                tab_temp.tabl[3]=1;
                r2=0;
            }

            if(tab_temp.tabl[4]==0 && r3 > 100)
            {
                genere_bonus(M,1,34);
                tab_temp.tabl[4]=1;
                r3 = 0;
            }


            //nouvdirec = coup_a_jouer(s1, s2, M, 2, 0);


            
            if(test(s1, nouvdirec, M))
            {

                //Serpent 1

                aux = s1;

                queue_aux = queue_serpent(s1);
                M.mat[queue_aux.x][queue_aux.y] = 0;
                s1 = nouveau_serpent(s1, direc, nouvdirec);


                queue_aux = queue_serpent(s1);
                M.mat[queue_aux.x][queue_aux.y] = 0;
                s1 = collision_bonus(M,s1,aux,&tab_temp,son);

    
                direc = nouvdirec;
    
                M = pose_serpent(s1, M);


                //Serpent 2
                queue_aux = queue_serpent(s2);
                M.mat[queue_aux.x][queue_aux.y] = 0;
                if (type_dia == 1)
                    nouvdirec2 = direc_random(s2,M,ecran);
                else if (type_dia == 0)
                    nouvdirec2 = coup_a_jouer(s2,s1,M,NOMBRE_DE_COUPS, 0);
                else
                    nouvdirec2 = coup_a_jouer(s2,s1,M,NOMBRE_DE_COUPS, 1);
    
                aux = s2;
                s2 = nouveau_serpent_2(s2, direc2, nouvdirec2);
    
                queue_aux = queue_serpent(s2);
                M.mat[queue_aux.x][queue_aux.y] = 0;
                s2 = collision_bonus(M,s2,aux,&tab_temp,son);
                direc2 = nouvdirec2;
                M = pose_serpent(s2, M);

                
                blit(M, ecran, tab);
                
                pos.x = 25; pos.y = 20;
                SDL_BlitSurface(tab.obj[35], NULL, ecran, &pos);
                pos.x = 30*(p-2)+5; pos.y = 30*(n-2);
                SDL_BlitSurface(tab.obj[36], NULL, ecran, &pos);
                SDL_Flip(ecran);
            }
            else
            {
                entier_fin_partie = 0;
                continuer = 0;
            }
        }
    }
    couple c;
    c.x = entier_fin_partie;
    c.y = p;
    return c;
}



int main()
{
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        {perror("SDL_INIT_VIDEO"); exit(1);}  
    if(TTF_Init() == -1)
        {perror("TTF_Init"); exit(1);}

    if(chdir("Images")==-1)
    {perror("Error chdir");exit(1);}
    SDL_WM_SetCaption("Snake vs Schlanga", NULL);

    SDL_WM_SetIcon(IMG_Load("Icone.png"), NULL);
    srand(time(NULL));




    SDL_Surface *ecran = NULL;
    
    ecran = SDL_SetVideoMode(1000, 625, 32, SDL_HWSURFACE);

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) 
    {
       printf("%s", Mix_GetError());
    }
    Mix_VolumeMusic(MIX_MAX_VOLUME); 
    Mix_Music *musique; //Création d'un pointeur de type Mix_Music
    musique = Mix_LoadMUS("musique.mp3"); //Chargement de la musique
    if(Mix_PlayMusic(musique, -1) == -1 )
    {
        perror("lecture");
    }

    

    tabl_obj tab;
    tab.taille = 37;
  
    tab.obj = malloc(tab.taille*sizeof(SDL_Surface*));
    tab.obj[0]=IMG_Load("Herbe.png");       tab.obj[1]=IMG_Load("bord.png");       
    tab.obj[2] = IMG_Load("Tete_h1.png");       tab.obj[3] = IMG_Load("Tete_b1.png");       
    tab.obj[4]=IMG_Load("Tete_d1.png");     tab.obj[5]=IMG_Load("Tete_g1.png");    
    tab.obj[6] = IMG_Load("Queue_h1.png");     tab.obj[7] = IMG_Load("Queue_b1.png");      
    tab.obj[8]=IMG_Load("Queue_d1.png");     tab.obj[9]= IMG_Load("Queue_g1.png");       
    tab.obj[10] = IMG_Load("Verti1.png");     tab.obj[11] = IMG_Load("Horiz1.png");     
    tab.obj[12]= IMG_Load("Coude_1.png");       tab.obj[13]= IMG_Load("Coude_2.png");      
    tab.obj[14] = IMG_Load("Coude_3.png");     tab.obj[15] = IMG_Load("Coude_4.png");
    tab.obj[16] = IMG_Load("Tete_h2.png");    tab.obj[17] = IMG_Load("Tete_b2.png");
    tab.obj[18]=IMG_Load("Tete_d2.png");           tab.obj[19]=IMG_Load("Tete_g2.png");       
    tab.obj[20] = IMG_Load("Queue_h2.png");     tab.obj[21] = IMG_Load("Queue_b2.png");
    tab.obj[22]= IMG_Load("Queue_d2.png");          tab.obj[23]=IMG_Load("Queue_g2.png");
    tab.obj[24] = IMG_Load("Verti2.png");       tab.obj[25] = IMG_Load("Horiz2.png");
    tab.obj[26]= IMG_Load("Coude_1s2.png");          tab.obj[27]=IMG_Load("Coude_2s2.png");       
    tab.obj[28] = IMG_Load("Coude_3s2.png");        tab.obj[29] = IMG_Load("Coude_4s2.png");
    tab.obj[30] = IMG_Load("Pomme.png");            tab.obj[31]=IMG_Load("Radioactive.png");
    tab.obj[32] = IMG_Load("Horloge.png");            tab.obj[33] = IMG_Load("Horloge2.png");     
    tab.obj[34] = IMG_Load("Inverse.png");          tab.obj[35] = IMG_Load("egg.png");
    tab.obj[36] = IMG_Load("egg2.png");

    int entier_fin_partie;
    int p;
    couple c;

    
    do
    {
        c = jeu(ecran, tab, musique);
        entier_fin_partie = c.x;
        p = c.y;
        fin_de_partie(entier_fin_partie,ecran, p,musique);

    } while (menu_fin(ecran) == 0);

    
    int i;
    for (i = 0; i < 33; ++i)
    {
       SDL_FreeSurface(tab.obj[i]);
    }



    SDL_Quit();

  	return 0;
}

