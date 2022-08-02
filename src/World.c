#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "struct.h"
#include "World.h"
#include "pile.h"
#include "curses.h"

/****************************************************************************************************************************************************/
/** Le menu récupère et interprète les lignes de commandes en redirigeant vers les fonctions appropriées **/

void menu(World* world)
{
    char commande[COMMAND_LINE_MAX];
    move(1,12);
    box(stdscr, ACS_VLINE, ACS_HLINE);
    wgetnstr(stdscr, commande,COMMAND_LINE_MAX);
    clear_window();

     if (strcmp(commande, "creer") == 0 || strcmp(commande, "creer un cube") == 0){
        if (world->cube_robot == NULL){
            mvwvline(stdscr, 28, 2, ACS_RARROW, 1);
            mvwaddstr(stdscr, 28,4,"C'est fait.");
            creer_cube(world);
        }
        else {
            mvwvline(stdscr, 28, 2, ACS_RARROW, 1);
            mvwaddstr(stdscr, 28,4,"Ce n'est pas possible.");
        }
     }

     else if ((strcmp(commande, "detruire") == 0) || strcmp(commande, "detruire le cube") == 0){
         if (world->cube_robot != NULL){
             mvwvline(stdscr, 28, 2, ACS_RARROW, 1);
             mvwaddstr(stdscr, 28,4,"C'est fait.");
             detruire_cube(world);
         }
         else {
             mvwvline(stdscr, 28, 2, ACS_RARROW, 1);
             mvwaddstr(stdscr, 28,4,"Ce n'est pas possible.");
         }
     }

    else if (strcmp(commande, "poser le cube sur la table") == 0 || strcmp(commande, "poser sur la table") == 0){
        if (world->cube_robot != NULL){
            poser_cube_sur_table(world);
        }
        else {
            mvwvline(stdscr, 28, 2, ACS_RARROW, 1);
            mvwaddstr(stdscr, 28, 4, "Ce n'est pas possible.");
        }
    }

     else if ((memcmp(commande, "prendre le cube", strlen("prendre le cube")) == 0) && (strlen(commande) <= strlen("prendre le cube 12"))){
         if (world->cube_robot == NULL){
             if (strlen(commande) == strlen("prendre le cube 1")){
                 prendre_cube(world, atoi(&commande[16]));
             }
             else {
                 prendre_cube(world, (commande[16] - 48)*10 + (commande[17]-48));
             }
         }
         else {
             mvwvline(stdscr, 28, 2, ACS_RARROW, 1);
             mvwaddstr(stdscr, 28,4,"Ce n'est pas possible.");
         }
     }

     else if (memcmp(commande, "prendre", strlen("prendre")) == 0 && (strlen(commande) <= strlen("prendre 12"))){
         if (world->cube_robot == NULL){
             if (strlen(commande) == strlen("prendre 1")){
                 prendre_cube(world, atoi(&commande[8]));
             }
             else {
                 prendre_cube(world, (commande[8] - 48)*10 + (commande[9]-48));
             }
         }
         else {
             mvwvline(stdscr, 28, 2, ACS_RARROW, 1);
             mvwaddstr(stdscr, 28,4,"Ce n'est pas possible.");
         }
     }

    else if (memcmp(commande, "poser le cube sur le cube", strlen("poser le cube sur le cube")) == 0 && (strlen(commande) <= strlen("poser le cube sur le cube 12"))){
         if (world->cube_robot != NULL){
             if (strlen(commande) == strlen("poser le cube sur le cube 1")){
                 poser_cube_sur_cube(world,  atoi(&commande[25]));
             }
             else {
                 poser_cube_sur_cube(world, (commande[25] - 48)*10 + (commande[26]-48));
             }
         }
         else {
             mvwvline(stdscr, 28, 2, ACS_RARROW, 1);
             mvwaddstr(stdscr, 28, 3, "Ce n'est pas possible.");
         }
    }

     else if (memcmp(commande, "poser sur le cube", strlen("poser sur le cube")) == 0 && (strlen(commande) <= strlen("poser sur le cube 12"))){
         if (world->cube_robot != NULL){
             if (strlen(commande) == strlen("poser sur le cube 1")){
                 poser_cube_sur_cube(world,  atoi(&commande[18]));
             }
             else {
                 poser_cube_sur_cube(world, (commande[18] - 48)*10 + (commande[19]-48));
             }
         }
         else {
             mvwvline(stdscr, 28, 2, ACS_RARROW, 1);
             mvwaddstr(stdscr, 28, 3, "Ce n'est pas possible.");
         }
     }

    else{
        mvwvline(stdscr, 28, 2, ACS_RARROW, 1);
        mvwaddstr(stdscr, 28,4,"Ce n'est pas une commande valide.");
    }
}

/****************************************************************************************************************************************************/
/** Fonctions principales de gestion du monde et des cubes **/

void initialize_monde(World* world)
{
    for (int i=0; i<10;i++){
        world->pile[i] = initialiser_pile();
        world->pile[i]->colonne = i + 1;
    }
    for (int j=0; j<30;j++){
        world->cube[j] = initialize_cube();

    }
    world->cube_robot=NULL;
    initscr();
    draw_robot(stdscr);
    draw_table(stdscr);
    world->cube[1]->numero = 1;
    world->cube[2]->numero = 2;
    world->cube[3]->numero = 3;
    world->cube[4]->numero = 4;
    empiler(world->pile[0], world->cube[1]);
    empiler(world->pile[1], world->cube[2]);
    empiler(world->pile[3], world->cube[3]);
    empiler(world->pile[3], world->cube[4]);
    afficherPile(world->pile[0]);
    afficherPile(world->pile[1]);
    afficherPile(world->pile[3]);
    mvwaddstr(stdscr, 1, 1, "Commande : ");
}

Cube* initialize_cube()
{
    Cube* cube = malloc(sizeof(*cube));
    cube->numero = 0;
}

void creer_cube(World* world)
{
    int i = 1;
    while(world->cube[i]->numero != 0){
        i++;
    }
    world->cube[i]->numero=i;
    world->cube_robot = world->cube[i];
    draw_cube_robot(world, world->cube[i]);
    world->cube_robot=world->cube[i];
    draw_robot_avec_cube();

}

void detruire_cube(World* world)
{
    world->cube_robot=NULL;
    clear_robot();
    draw_robot();
}

void prendre_cube(World* world, int numero_cube) {

    for (int i = 0; i < 10; i++) {
        if (world->pile[i]->premier != NULL) {
            if (numero_cube == sommet(world->pile[i])->numero) {
                mvwvline(stdscr, 28, 2, ACS_RARROW, 1);
                mvwaddstr(stdscr, 28, 4, "C'est fait.");
                draw_cube_robot(world, sommet(world->pile[i]));
                world->cube_robot=sommet(world->pile[i]);
                draw_robot_avec_cube();
                clearPile(world->pile[i]);
                depiler(world->pile[i]);
            }
        }
    }
    if (world->cube_robot == NULL) {
        mvwvline(stdscr, 28, 2, ACS_RARROW, 1);
        mvwaddstr(stdscr, 28, 4, "Ce n'est pas possible.");
    }
}

void poser_cube_sur_table(World* world) {
    for(int i=0;i<10;i++) {
        if (world->pile[i]->premier == NULL) {
            mvwvline(stdscr, 28, 2, ACS_RARROW, 1);
            mvwaddstr(stdscr, 28,4,"C'est fait.");
            empiler(world->pile[i],world->cube_robot);
            world->cube_robot=NULL;
            clear_robot();
            draw_robot();
            afficherPile(world->pile[i]);
            break;
        }
    }
    if (world->cube_robot != NULL) {
        mvwvline(stdscr, 28, 2, ACS_RARROW, 1);
        mvwaddstr(stdscr, 28, 4, "Ce n'est pas possible.");
    }
}

void poser_cube_sur_cube(World* world, int numero_cube)
{
    int i=0;
    int plein = 0;
    while(world->cube_robot != NULL  && i<=10 && plein == 0) {
        while (world->pile[i]->premier == NULL) {
            i++;
        }
        if (sommet(world->pile[i])->numero == numero_cube) {
            if (world->pile[i]->nbElement <  8) {
                empiler(world->pile[i], world->cube_robot);
                world->cube_robot = NULL;
                clear_robot();
                draw_robot();
                afficherPile(world->pile[i]);
                mvwvline(stdscr, 28, 2, ACS_RARROW, 1);
                mvwaddstr(stdscr, 28, 4, "C'est fait.");
            }
            else {
                plein = 1;
                mvwvline(stdscr, 28, 2, ACS_RARROW, 1);
                mvwaddstr(stdscr, 28,4," Ce n'est pas possible.");
            }
        }
        i++;
    }
    if (world->cube_robot != NULL){
        mvwvline(stdscr, 28, 2, ACS_RARROW, 1);
        mvwaddstr(stdscr, 28,4," Ce n'est pas possible.");
    }
}

/****************************************************************************************************************************************************/
/** Fonctions secondaires de gestion de l'affichage **/

void draw_robot()
{
    mvwvline(stdscr, 18, 5, '/', 1);
    mvwvline(stdscr, 17, 6, '/', 1);
    mvwvline(stdscr, 16, 7, '/', 1);
    mvwvline(stdscr, 14, 9, '/', 1);
    mvwvline(stdscr, 17, 9, '\\', 1);
    mvwhline(stdscr, 17, 10, '_', 1);
    mvwhline(stdscr, 13, 10, '_', 1);
    mvwvline(stdscr, 15, 8, ACS_VLINE, 2);
    mvwvline(stdscr, 19, 5, ACS_VLINE, 7);
    mvwhline(stdscr, 25, 4, ACS_HLINE, 3);
    mvwvline(stdscr, 25, 5, ACS_BTEE, 1);
}

void draw_table()
{
    mvwhline(stdscr, 26, 1, ACS_HLINE,70);
    mvwvline(stdscr, 26,6,ACS_BSSS,1);
    mvwvline(stdscr, 27,6,ACS_VLINE,1);
    mvwvline(stdscr, 26,66,ACS_BSSS,1);
    mvwvline(stdscr, 27,66,ACS_VLINE,1);
}

void draw_cube(Cube* cube, int position, int hauteur)
{
    int x = (5 * position) + 12;
    int y = (-3 * hauteur) + 27;

    if (cube->numero<=9) {
        mvwvline(stdscr, y, x, (chtype)(cube->numero+48), 1);
    }
    else {
        int dizaine = cube->numero/10;
        int unite = cube->numero%10;
        mvwvline(stdscr, y, x-1, (chtype)(dizaine+48), 1);
        mvwvline(stdscr, y, x, (chtype)(unite+48), 1);
    }

    mvwhline(stdscr, y+1, x + 1, ACS_LRCORNER, 1);
    mvwvline(stdscr, y, x + 1, ACS_VLINE, 1);
    mvwhline(stdscr, y-1, x + 1, ACS_URCORNER, 1);

    mvwvline(stdscr, y+1, x - 2, ACS_LLCORNER, 1);
    mvwvline(stdscr, y, x - 2, ACS_VLINE, 1);
    mvwhline(stdscr, y-1, x - 2, ACS_ULCORNER, 1);

    mvwhline(stdscr, y+1, x - 1, ACS_HLINE, 2);
    mvwhline(stdscr, y-1, x - 1, ACS_HLINE, 2);
}

void draw_cube_robot(World* world, Cube* cube){
    int x = 11;
    int y = 15;

    if (cube->numero<=9) {
        mvwvline(stdscr, y, x, (chtype)(cube->numero+48), 1);
    }
    else {
        int dizaine = cube->numero/10;
        int unite = cube->numero%10;
        mvwvline(stdscr, y, x-1, (chtype)(dizaine+48), 1);
        mvwvline(stdscr, y, x, (chtype)(unite+48), 1);
    }

    mvwhline(stdscr, y+1, x + 1, ACS_LRCORNER, 1);
    mvwvline(stdscr, y, x + 1, ACS_VLINE, 1);
    mvwhline(stdscr, y-1, x + 1, ACS_URCORNER, 1);

    mvwvline(stdscr, y+1, x - 2, ACS_LLCORNER, 1);
    mvwvline(stdscr, y, x - 2, ACS_VLINE, 1);
    mvwhline(stdscr, y-1, x - 2, ACS_ULCORNER, 1);

    mvwhline(stdscr, y+1, x - 1, ACS_HLINE, 2);
    mvwhline(stdscr, y-1, x - 1, ACS_HLINE, 2);
}

void draw_robot_avec_cube(){
    int x = 11;
    int y = 15;

    mvwhline(stdscr, y+2,x-3,ACS_LLCORNER,1);
    mvwhline(stdscr, y+2,x-2,ACS_HLINE,3);

    mvwhline(stdscr, y-2,x-3,ACS_ULCORNER,1);
    mvwhline(stdscr, y-1,x-3,ACS_VLINE,1);
    mvwhline(stdscr, y-2,x-2,ACS_HLINE,3);
}

void clear_robot(){
    int x = 11;
    int y = 15;

    mvwvline(stdscr, y, x-1, ' ', 1);
    mvwvline(stdscr, y, x, ' ', 1);

    mvwhline(stdscr, y+1, x + 1, ' ', 1);
    mvwvline(stdscr, y, x + 1, ' ', 1);
    mvwhline(stdscr, y-1, x + 1, ' ', 1);

    mvwvline(stdscr, y+1, x - 2, ' ', 1);
    mvwvline(stdscr, y, x - 2, ' ', 1);
    mvwhline(stdscr, y-1, x - 2, ' ', 1);

    mvwhline(stdscr, y+1, x - 1, ' ', 2);
    mvwhline(stdscr, y-1, x - 1, ' ', 2);

    mvwhline(stdscr, y+2,x-3,' ',1);
    mvwhline(stdscr, y+2,x-2,' ',3);

    mvwhline(stdscr, y-2,x-3,' ',1);
    mvwhline(stdscr, y-1,x-3,' ',1);
    mvwhline(stdscr, y-2,x-2,' ',3);
}

void clear_cube(int position, int hauteur)
{
    int x = (5 * position) + 12;
    int y = (-3 * hauteur) + 27;

    mvwvline(stdscr, y, x-1, ' ', 1);
    mvwvline(stdscr, y, x, ' ', 1);

    mvwhline(stdscr, y+1, x + 1, ' ', 1);
    mvwvline(stdscr, y, x + 1, ' ', 1);
    mvwhline(stdscr, y-1, x + 1, ' ', 1);

    mvwvline(stdscr, y+1, x - 2, ' ', 1);
    mvwvline(stdscr, y, x - 2, ' ', 1);
    mvwhline(stdscr, y-1, x - 2, ' ', 1);

    mvwhline(stdscr, y+1, x - 1, ' ', 2);
    mvwhline(stdscr, y-1, x - 1, ' ', 2);
}

void clear_window(){
    mvwhline(stdscr,28,1,' ',50);
    mvwhline(stdscr,1,11,' ',80);
}