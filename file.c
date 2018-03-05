
#include "file.h"

file creer_file_vide(int t)
{
	file f;
	f.curseur = 0;
	f.taille = 0;
	f.taille_totale = t;
	f.tab = malloc(f.taille_totale*sizeof(int));

	int i;
	for (i=0; i<f.taille_totale; i++)
		f.tab[i] = -1;
	return f;
}

void affiche_file(file f)
{
	int i, k = 1;
	printf("[");
	if (!(f.taille == 0))
	{
		if (f.taille == 1)
			printf("%d", f.tab[f.curseur]);
		else
		{
			for (i=f.curseur; i<f.taille_totale && f.tab[i] != -1; i++)
			{
				if (k)
					k = 0;
				else
					printf(", ");
				printf("%d", f.tab[i]);
			}
			for (i=0; i<f.taille-(f.taille_totale - f.curseur); i++)
			{
				printf(", %d", f.tab[i]);
			}
		}
	}
	printf("]\n");
}

int retrait(file* f)
{
	if (f->taille == 0)
		return -1;
	f->taille--;
	int a = f->tab[f->curseur];
	f->tab[f->curseur] = -1;
	if (f->curseur == f->taille_totale-1)
		f->curseur = 0;
	else
		f->curseur++;
	return a;
}

void affiche_struct(file f)
{
	int i;
	printf("%s\n", "Affichage de la structure :");
	for (i=0; i<f.taille_totale; i++)
		printf("%d ", f.tab[i]);
}

void detruit(file* f)
{
	free(f->tab);
}

void ajout(file* f, int elm)
{
	if (f->taille == f->taille_totale)
	{
		file g = creer_file_vide(f->taille_totale * 3);
		int i, k = 0;
		for (i=f->curseur; i<f->taille_totale; i++)
		{
			g.tab[k] = f->tab[i];
			k++;
		}
		for (i=0; i<f->curseur; i++)
		{
			g.tab[k] = f->tab[i];
			k++;
		}

		f->tab = malloc(f->taille_totale*3*sizeof(int));
		f->taille_totale*=3;

		for (i = 0; i<f->taille; i++)
			f->tab[i] = g.tab[i];
		for (i = f->taille; i<f->taille_totale;i++)
			f->tab[i] = -1;

		
		f->tab[f->taille] = elm;
		f->taille++;
		f->curseur = 0;
		
		detruit(&g);
	}
	else
	{
		if (f->taille == 0)
			f->curseur = 0;
		if (f->taille + f->curseur >= f->taille_totale)
			f->tab[f->taille+f->curseur-f->taille_totale] = elm;
		else
			f->tab[f->taille+f->curseur] = elm;
		f->taille++;
	}
}


/*
int main()
{
	file f = creer_file_vide(10);
	int k;
	int a;

	while (1)
	{
		if (scanf("%d", &k) == -1)
			exit(1);

		if (k%2 == 0)
			ajout(&f, k);
		else
		{
			a = retrait(&f);
			printf("Voilà l'élément : %d\n", a);
		}
			
		affiche(f);
		affiche_struct(f);
		printf("\n");
		printf("Taille : %d\n", f.taille);
		printf("Curseur : %d\n\n", f.curseur);
	}

	return 0;
}

*/