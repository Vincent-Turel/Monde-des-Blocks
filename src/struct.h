#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED

/**  Contient toutes les structures nécessaires pour ce TP  **/

typedef struct {
    int numero;
} Cube;

typedef struct Element Element;
struct Element
{
    Cube* cube;
    Element *suivant;
};

typedef struct Pile Pile;
struct Pile
{
    int nbElement;
    int colonne;
    Element *premier;
};

typedef struct {
    Pile *pile[10];
    Cube *cube[30];
    Cube *cube_robot;
} World;

#endif