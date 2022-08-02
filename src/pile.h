#ifndef PILE_H_INCLUDED
#define PILE_H_INCLUDED

#include <stddef.h>
#include "struct.h"

/**  Contient les prototypes des fonctions de gestion des piles  **/

Pile *initialiser_pile();

void empiler(Pile *pile, Cube* nvCube);

void depiler(Pile *pile);

void afficherPile(Pile *pile);

void clearPile(Pile* pile);

Cube* sommet(Pile* pile);

#endif
