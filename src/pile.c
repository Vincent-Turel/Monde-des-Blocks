#include <stdio.h>
#include <malloc.h>
#include "pile.h"
#include "World.h"

Pile* initialiser_pile()
{
    Pile* pile = malloc(sizeof(*pile));
    pile->premier = NULL;
    pile->nbElement = 0;
}

void empiler(Pile *pile, Cube* nvCube)
{
    Element *nouveau = malloc(sizeof(*nouveau));

    nouveau->cube = nvCube;
    nouveau->suivant = pile->premier;
    pile->premier = nouveau;
    pile->nbElement++;
}

void depiler(Pile *pile)
{
    Element *elementDepile = pile->premier;

    if (pile != NULL && pile->premier != NULL) {
        pile->premier = elementDepile->suivant;
        free(elementDepile);
        pile->nbElement--;
    }
}

void afficherPile(Pile* pile)
{
    int nombreDeCube = 0;
    Element* actuel = pile->premier;
    while (actuel != NULL)
    {
        nombreDeCube++;
        actuel = actuel->suivant;
    }
    actuel = pile->premier;
    while (actuel != NULL)
    {
        draw_cube(actuel->cube, pile->colonne, nombreDeCube);
        nombreDeCube--;
        actuel = actuel->suivant;
    }
}

void clearPile(Pile* pile)
{
    int nombreDeCube = 0;
    Element* actuel = pile->premier;
    while (actuel != NULL)
    {
        nombreDeCube++;
        actuel = actuel->suivant;
    }
    clear_cube(pile->colonne, nombreDeCube);
}

Cube* sommet(Pile* pile)
{
    return pile->premier->cube;
}
