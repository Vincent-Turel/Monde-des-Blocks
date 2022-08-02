#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <stddef.h>
#include "struct.h"
#include "curses.h"

#define COMMAND_LINE_MAX 80

/**
 * Contient les prototypes des fonctions de manipulations des cubes ainsi que des fonctions supplémentaires pour
 * éviter au maximum les redondances et surtout améliorer considérablement la lisibilité du code
**/

void menu(World* world);

void initialize_monde(World * world);

Cube* initialize_cube();

void creer_cube(World* world);

void detruire_cube(World* world);

void prendre_cube(World* world, int numero_cube);

void poser_cube_sur_table(World* world);

void poser_cube_sur_cube(World* world, int numero_cube);

void draw_robot();

void draw_table();

void draw_cube(Cube* cube, int position, int hauteur);

void draw_cube_robot(World* world, Cube* cube);

void draw_robot_avec_cube();

void clear_robot();

void clear_cube(int position, int hauteur);

void clear_window();

#endif

