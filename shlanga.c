#include "shlanga.h"


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

serpent decale_2(serpent s, triplet nouvtete, int nouvmaillon)
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
    t.z = 25;
    if ((s->tete.z == 24 && s->queue->tete.z == 20) || 
        (s->tete.z == 28 && s->queue->tete.z == 23) ||
        (s->tete.z == 29 && s->queue->tete.z == 22))
    {
        t.z = 20;
    }
    if ((s->tete.z == 24 && s->queue->tete.z == 21) || 
        (s->tete.z == 27 && s->queue->tete.z == 23) ||
        (s->tete.z == 26 && s->queue->tete.z == 22))
    {
        t.z = 21;
    }
    if ((s->tete.z == 25 && s->queue->tete.z == 22) || 
        (s->tete.z == 27 && s->queue->tete.z == 20) ||
        (s->tete.z == 28 && s->queue->tete.z == 21))
    {
        t.z = 22;
    }
    if ((s->tete.z == 25 && s->queue->tete.z == 23) || 
        (s->tete.z == 26 && s->queue->tete.z == 20) ||
        (s->tete.z == 29 && s->queue->tete.z == 21))
    {
        t.z = 23;
    }
    
    s2 = cons(s2, t);

    s2 = reverse(s2);

    return s2;
}
 
serpent nouveau_serpent_2(serpent s, int direc, int nouvdirec)
{
  triplet t;
  t.x = s->tete.x;
  t.y = s->tete.y;
  if (direc == 1)
  {
    if (nouvdirec == 1 || nouvdirec == 3)
    {
      t.y = s->tete.y - 1;
      t.z = 19;
      s = decale_2(s, t, 25);
    }
    if (nouvdirec == 2)
    {
      t.x = s->tete.x + 1;
      t.z = 17;
      s = decale_2(s, t, 27);
    }
    if (nouvdirec == 4)
    {
      t.x = s->tete.x - 1;
      t.z = 16;
      s = decale_2(s, t, 28);
    }
  }
  if (direc == 2)
  {
    if (nouvdirec == 2 || nouvdirec == 4)
    {
      t.x = s->tete.x + 1;
      t.z = 17;
      s = decale_2(s, t, 24);
    }
    if (nouvdirec == 1)
    {
      t.y = s->tete.y - 1;
      t.z = 19;
      s = decale_2(s, t, 29);
    }
    if (nouvdirec == 3)
    {
      t.y = s->tete.y + 1;
      t.z = 18;
      s = decale_2(s, t, 28);
    }
  }
  if (direc == 3)
  {
    if (nouvdirec == 1 || nouvdirec == 3)
    {
      t.y = s->tete.y + 1;
      t.z = 18;
      s = decale_2(s, t, 25);
    }
    if (nouvdirec == 2)
    {
      t.x = s->tete.x + 1;
      t.z = 17;
      s = decale_2(s, t, 26);
    }
    if (nouvdirec == 4)
    {
      t.x = s->tete.x - 1;
      t.z = 16;
      s = decale_2(s, t, 29);
    }
  }
  if (direc == 4)
  {
    if (nouvdirec == 2 || nouvdirec == 4)
    {
      t.x = s->tete.x - 1;
      t.z = 16;
      s = decale_2(s, t, 24);
    }
    if (nouvdirec == 1)
    {
      t.y = s->tete.y - 1;
      t.z = 19;
      s = decale_2(s, t, 26);
    }
    if (nouvdirec == 3)
    {
      t.y = s->tete.y + 1;
      t.z = 18;
      s = decale_2(s, t, 27);
    }
  }
  return s;
}


// 16 = serpent1_tête_haut
// 17 = serpent1_tête_bas
// 18 = serpent1 _tête_droite
// 19 = serpent1_tête_gauche
