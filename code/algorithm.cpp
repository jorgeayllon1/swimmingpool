#include <iostream>
#include <allegro.h>
#include "graphe.h"
#include <set>
#define INFINI 9999
#include "fonctionsutiles.h"



#define NELEM 10
void initialisation()
{
    allegro_init();
    install_keyboard();
    install_mouse();


        set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,1000,768,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

void troisDeuxUnPartez()
{
    srand(time(NULL));
	Graphe *espace = new Graphe ("files/broadway.txt", "files/broadway_weights_0.txt");
	std::vector<pair<float,float>> total;
	std::vector<pair<float,float>> pareto;
	std::vector<pair<float,float>> nonPareto;
    std::vector<vector<bool>> G ;
	 //bool cycle = false;


    ///fonction Graphe

	//espace.dessinerGraphe();
	//espace = espace.dijkstraSPT(3);
    initialisation();

    int couleurFond = makecol(223, 230, 233);

    ///BITMAP de fond -------------------------------
    BITMAP *fond;
    fond=create_bitmap(SCREEN_W,SCREEN_H);
    rectfill(fond, 0,0, SCREEN_W, SCREEN_H, couleurFond);
    int posx,posy;    // coordonn�es
    int tx,ty;        // taille (largeur et hauteur)
    tx=fond->w;
    ty=fond->h;
    posx=SCREEN_W/2-tx/2;
    posy=SCREEN_H/2-ty/2;
    ///-----------------------------------------------

    BITMAP *menuD;
    menuD=create_bitmap(SCREEN_W/2,SCREEN_H/2);
    rectfill(menuD, 0,0, menuD->w, menuD->h, couleurFond);

    BITMAP *accueil;
    accueil= load_bitmap("image/accueil.bmp", NULL);

    BITMAP *GrapheGeneral;
    GrapheGeneral=create_bitmap(SCREEN_W,SCREEN_H);
    rectfill(GrapheGeneral, 0,0, GrapheGeneral->w, GrapheGeneral->h, couleurFond);

    BITMAP *supportGraphe;
    supportGraphe=create_bitmap(SCREEN_W,SCREEN_H);
    rectfill(supportGraphe, 0,0, supportGraphe->w, supportGraphe->h,couleurFond);


    BITMAP *supportCourbe;
    supportCourbe=create_bitmap(SCREEN_W/2,SCREEN_H/2);
    rectfill(supportCourbe, 0,0, supportCourbe->w, supportCourbe->h, couleurFond);


    ///Dessin------------------------------------------


    show_mouse(screen);


    int choice=5;
    bool prim = true;

    // Boucle d'animation (pas d'interaction)
    while (!key[KEY_ESC])
    {



        // 1) EFFACER POSITIONs ACTUELLEs SUR LE BUFFER
        //    ON EFFACE TOUT LE BUFFER ! (c'est plus simple)


    switch(choice)
    {
    case 1:
     if(prim)
        {
            clear_bitmap(supportGraphe);
            rectfill(supportGraphe, 0,0, supportGraphe->w, supportGraphe->h, couleurFond);
            (espace->primMST(0,1,0)).drawGraphe(supportGraphe);
            choice = 0;
            prim = false;
        }
        else
            {
            Graphe *krukal;
            clear_bitmap(supportGraphe);
            rectfill(supportGraphe, 0,0, supportGraphe->w, supportGraphe->h, couleurFond);
            krukal = new Graphe(espace->primMST(0,0,1));
            krukal->welshpowel();
            krukal->drawGraphe(supportGraphe);
            choice = 0;
            prim = true;
            }
            rest(100);

        break;
    case 2:
    G = espace->calcul_sousgraphes_admissibles(&total, 0);
    choice =0;
    pareto = espace->Pareto(total,&nonPareto);
    espace->drawNuage(supportCourbe, pareto, nonPareto );
        break;
    case 3:
    G = espace->calcul_sousgraphes_admissibles(&total, 1);
    choice =0;
    pareto = espace->Pareto(total,&nonPareto);
    espace->drawNuage(supportCourbe, pareto, nonPareto );

        break;
    case 4:
    espace->refresh(couleurFond, fond, supportCourbe, supportGraphe, GrapheGeneral);
    choice = 0;
        break;
    case 5:
        blit(accueil,screen,0,0,0,0,accueil->w,accueil->h);
        std::string nomFichier;
        std::string poidsFichiers;

        cout << "Quel Ville voulez-vous ?" <<endl;
        std::cin >> nomFichier;
         cout << "Quel set de couts voulez-vous ?" <<endl;
        std::cin >> poidsFichiers;

        std::string fichiers1;
        std::string fichiers2;

//        nomFichier = "manhattan";
//        poidsFichiers="0";

        fichiers1 = "files/" +nomFichier+".txt";
        fichiers2 = "files/" +nomFichier+"_weights_"+poidsFichiers+".txt";


        delete(espace);
        espace = new Graphe (fichiers1, fichiers2);




        break;

        }

         clear_bitmap(fond);


    rectfill(fond, 0,0, SCREEN_W, SCREEN_H, couleurFond);

    espace->drawGraphe(GrapheGeneral);
    blit(GrapheGeneral,fond,50,50,0,0,GrapheGeneral->w,GrapheGeneral->h);
    blit(supportGraphe,fond,50,70,0,SCREEN_H/2,supportGraphe->w,supportGraphe->h);
    blit(supportCourbe,fond,0,0,SCREEN_W/2 ,0,supportCourbe->w,supportCourbe->h);
    //stretch_blit(supportCourbe, fond, 0, 0, supportCourbe->w, supportCourbe->h, SCREEN_W/2, 0, SCREEN_W/2, SCREEN_H/2);


    choice = espace->menuInterne(fond);
    blit(fond,screen,0,0,posx,posy,tx,ty);

    //afficherSousGraphe(espace);

         // 2) DETERMINER NOUVELLEs POSITIONs


        // 3) AFFICHAGE NOUVELLEs POSITIONs SUR LE BUFFER
        //    ON UTILISE page AU LIEU DE screen


        // 4) AFFICHAGE DU BUFFER MIS A JOUR A L'ECRAN
        //    le nouveau contenu graphique remplace l'ancien
        //    sans que l'ancien ait �t� effac� � l'�cran (pas de clignotement)
       // blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        // 5) ON FAIT UNE PETITE PAUSE � chaque fois sinon �a va trop vite...
        rest(20);
    }


}
/// j'essaye de crée une branche pareto
