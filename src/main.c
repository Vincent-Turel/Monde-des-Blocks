#include "World.h"
#include "struct.h"

World mondeDesBlocs;

int main(int argc, char* argv[]){

    int fini = 0;

    initialize_monde(&mondeDesBlocs); /** Initialise le monde des blocs **/

    do {
        menu(&mondeDesBlocs); /** Lance le menu en boucle **/
    } while(! fini);
}








