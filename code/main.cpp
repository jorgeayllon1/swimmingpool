#include "graphe.h"
#include <random>
#include "time.h"
#include <allegro.h>
#include <time.h>
using namespace std;

#define NELEM 10
void initialisation()
{
    allegro_init();
    install_keyboard();

        set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,1000,800,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}


int main()
{
    srand(time(NULL));
	Graphe espace("files/cubetown.txt", "files/cubetown_weights_0.txt");
	//espace.dessinerGraphe();
	//espace = espace.dijkstraSPT(3);
    // BITMAP servant de buffer d'affichage
    initialisation();

    BITMAP *fond;
    fond=create_bitmap(SCREEN_W,SCREEN_H);
    rectfill(fond, 0,0, SCREEN_W, SCREEN_H, makecol(248, 194, 145));
    int posx,posy;    // coordonnées
    int tx,ty;        // taille (largeur et hauteur)
    tx=fond->w;
    ty=fond->h;
    posx=SCREEN_W/2-tx/2;
    posy=SCREEN_H/2-ty/2;


    espace.drawGraphe(fond);

    blit(fond,screen,0,0,posx,posy,tx,ty);


    // Boucle d'animation (pas d'interaction)
    while (!key[KEY_ESC])
    {

        // 1) EFFACER POSITIONs ACTUELLEs SUR LE BUFFER
        //    ON EFFACE TOUT LE BUFFER ! (c'est plus simple)
        //clear_bitmap(page);

         // 2) DETERMINER NOUVELLEs POSITIONs


        // 3) AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
        //    ON UTILISE page AU LIEU DE screen


        // 4) AFFICHAGE DU BUFFER MIS A JOUR A L'ECRAN
        //    le nouveau contenu graphique remplace l'ancien
        //    sans que l'ancien ait été effacé à l'écran (pas de clignotement)
       // blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        // 5) ON FAIT UNE PETITE PAUSE à chaque fois sinon ça va trop vite...
        rest(20);
    }

    return 0;
}
END_OF_MAIN();
