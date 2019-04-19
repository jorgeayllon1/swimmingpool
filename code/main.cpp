#include "graphe.h"
#include <random>
#include "time.h"
#include <allegro.h>
#include <time.h>
#include <bitset>
using namespace std;

#define NELEM 10
void initialisation()
{
    allegro_init();
    install_keyboard();
    install_mouse();


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
	Graphe espace("files/manhattan.txt", "files/manhattan_weights_0.txt");
	vector<pair<float,float>> total;
	vector<pair<float,float>> pareto;
	vector<pair<float,float>> nonPareto;
	 vector<vector<bool>> G = espace.calcul_sousgraphes_admissibles(&total, 0);
	 //bool cycle = false;


    ///fonction Graphe

	//espace.dessinerGraphe();
	//espace = espace.dijkstraSPT(3);
    initialisation();

    ///BITMAP de fond -------------------------------
    BITMAP *fond;
    fond=create_bitmap(SCREEN_W,SCREEN_H);
    rectfill(fond, 0,0, SCREEN_W, SCREEN_H, makecol(248, 194, 145));
    int posx,posy;    // coordonnées
    int tx,ty;        // taille (largeur et hauteur)
    tx=fond->w;
    ty=fond->h;
    posx=SCREEN_W/2-tx/2;
    posy=SCREEN_H/2-ty/2;
    ///-----------------------------------------------

    BITMAP *menuD;
    menuD=create_bitmap(SCREEN_W/2,SCREEN_H/2);
    rectfill(menuD, 0,0, menuD->w, menuD->h, makecol(248, 194, 145));

    BITMAP *GrapheGeneral;
    GrapheGeneral=create_bitmap(SCREEN_W/2,SCREEN_H/2);
    rectfill(GrapheGeneral, 0,0, GrapheGeneral->w, GrapheGeneral->h, makecol(248, 194, 145));

    BITMAP *supportGraphe;
    supportGraphe=create_bitmap(SCREEN_W/2,SCREEN_H/2);
    rectfill(supportGraphe, 0,0, supportGraphe->w, supportGraphe->h, makecol(248, 194, 145));


    BITMAP *supportCourbe;
    supportCourbe=create_bitmap(SCREEN_W/2,SCREEN_H/2);
    rectfill(supportCourbe, 0,0, supportCourbe->w, supportCourbe->h, makecol(248, 194, 145));


    ///Dessin------------------------------------------



    espace.drawGraphe(GrapheGeneral);

    int choice;

    // Boucle d'animation (pas d'interaction)
    while (!key[KEY_ESC])
    {



        // 1) EFFACER POSITIONs ACTUELLEs SUR LE BUFFER
        //    ON EFFACE TOUT LE BUFFER ! (c'est plus simple)

    clear_bitmap(fond);
    show_mouse(screen);

    rectfill(fond, 0,0, SCREEN_W, SCREEN_H, makecol(248, 194, 145));

    blit(GrapheGeneral,fond,0,0,0,0,GrapheGeneral->w,GrapheGeneral->h);
    blit(supportGraphe,fond,0,0,0,SCREEN_H/2,supportGraphe->w,supportGraphe->h);
    blit(supportCourbe,fond,0,0,SCREEN_W/2 ,100,supportCourbe->w,supportCourbe->h);




    choice = espace.menuInterne(fond);
    switch(choice)
    {
    case 1:
    //espace.Conversion(G[2]).drawSousGraphe(supportGraphe);

        break;
    case 2:
    G = espace.calcul_sousgraphes_admissibles(&total, 0);
    choice =0;
    //pareto = espace.Pareto(total,&nonPareto);
    //espace.drawNuage(supportCourbe, pareto, nonPareto );
        break;
    case 3:
        (espace.primMST(0,1,0)).drawGraphe(supportGraphe);
        break;
    case 4:
    clear_bitmap(GrapheGeneral);
    clear_bitmap(supportGraphe);
    clear_bitmap(supportCourbe);

    rectfill(supportCourbe, 0,0, supportCourbe->w, supportCourbe->h, makecol(248, 194, 145));
    rectfill(supportGraphe, 0,0, supportGraphe->w, supportGraphe->h, makecol(248, 194, 145));
    rectfill(GrapheGeneral, 0,0, supportCourbe->w, supportCourbe->h, makecol(248, 194, 145));

    espace.drawGraphe(GrapheGeneral);
    rectfill(supportCourbe, 0,0, supportCourbe->w, supportCourbe->h, makecol(248, 194, 145));
    rectfill(fond, 0,0, SCREEN_W, SCREEN_H, makecol(248, 194, 145));
    blit(GrapheGeneral,fond,0,0,0,0,GrapheGeneral->w,GrapheGeneral->h);
    choice = espace.menuInterne(fond);
    choice = 0;
        break;

        }
    blit(fond,screen,0,0,posx,posy,tx,ty);

    //afficherSousGraphe(espace);

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
