#include "graphe.h"
#include "graphique.h"
#include "svgfile.h"


using namespace std;



Graphique::Graphique()
{
}

Graphique::~Graphique()
{
}

int Graphique::menuInterne(BITMAP *page)
{
        BITMAP *primbouton = load_bitmap("image/prim.bmp", NULL);
        BITMAP *clearbouton = load_bitmap("image/clear.bmp", NULL);
        BITMAP *biobj = load_bitmap("image/biobj.bmp", NULL);
        BITMAP *distance = load_bitmap("image/dstance.bmp", NULL);
        BITMAP *fichier = load_bitmap("image/fichier.bmp", NULL);
    if (!primbouton || !clearbouton || !biobj || !distance || !fichier)
    {
        allegro_message("pas pu trouver/charger mon_image.bmp");
        allegro_exit(); exit(EXIT_FAILURE);
    }

    int startX = 700;
    int finX = startX + 100;
    int startY = SCREEN_H/2 + 100;
    int finY = startY + 50;
    int CHOIX =6;
    int couleurBouton = makecol(119, 140, 163);


//    rectfill(page, startX,startY, finX, startY + 50, couleurBouton);
//    rect(page, startX,startY, finX, startY + 50, makecol(0,0,0));

//    rectfill(page, startX,startY+50, finX, startY + 100,couleurBouton);
//    rect(page, startX,startY+50, finX, startY + 100, makecol(0,0,0));
//
//    rectfill(page, startX,startY+100, finX, startY + 150,couleurBouton);
//    rect(page, startX,startY+100, finX, startY + 150, makecol(0,0,0));
//
//    rectfill(page, startX,startY+150, finX, startY + 200, couleurBouton);
//    rect(page, startX,startY+150, finX, startY + 200, makecol(0,0,0));
//
//    rectfill(page, startX,startY+200, finX, startY + 250, couleurBouton);
//    rect(page, startX,startY+200, finX, startY + 250, makecol(0,0,0));


    blit(primbouton,page,0,0, startX,startY ,100,50);
    rect(page, startX,startY, finX, startY + 50, makecol(0,0,0));

    blit(biobj,page,0,0, startX,startY+50 ,100,50);
    rect(page, startX,startY+50, finX, startY + 100, makecol(0,0,0));

    blit(distance,page,0,0, startX,startY+100 ,100,50);
    rect(page, startX,startY+100, finX, startY + 150, makecol(0,0,0));

    blit(clearbouton,page,0,0, startX,startY+150 ,100,50);
    rect(page, startX,startY+150, finX, startY + 200, makecol(0,0,0));

    blit(fichier,page,0,0, startX,startY+200 ,100,50);
    rect(page, startX,startY+200, finX, startY + 250, makecol(0,0,0));



    rectfill(page, startX+100,startY+75, finX+30, startY + 125, couleurBouton);
    rect(page, startX+100,startY+75, finX+30, startY + 125, makecol(0,0,0));

    rectfill(page, startX-30,startY+75, startX, startY + 125, couleurBouton);
    rect(page, startX-30,startY+75, startX, startY + 125, makecol(0,0,0));




    for(int i=1;i<=CHOIX;i++)
    {

    if(mouse_x  > startX && mouse_x  < finX && mouse_y < (startY + 50*i) && mouse_y > startY&& mouse_b & 1) // gauche : dessiner en rouge)
        return i;
    }

    if(mouse_x  > startX +100 && mouse_x  < finX+30 && mouse_y > (startY + 75) && mouse_y < startY +125&& mouse_b & 1) // gauche : dessiner en rouge)
        return 6;
    if(mouse_x  > startX -30 && mouse_x  < startX && mouse_y > (startY + 75) && mouse_y < startY +125&& mouse_b & 1) // gauche : dessiner en rouge)
        return 6;


    return 0;


}


void Graphique::drawNuage(BITMAP *arbo,vector<pair<float,float>> &pareto,vector<pair<float,float>> &nonPareto)
{

    int longGraph = 200;
    int originX = 11;
    int origineY = SCREEN_H/2 -20;
//    int origineY = SCREEN_H-100;
//    int originX = 0;
//    int longGraph = 400;
    sort(nonPareto.begin(), nonPareto.end(), sortbyCout2);
    double Xmax = nonPareto[0].second;
    sort(nonPareto.begin(), nonPareto.end(), sortbyCout1);
    double Ymax = nonPareto[0].first;

    rect(arbo, 0,0, arbo->w-10, arbo->h-10, makecol(0,0,0));
    //double coef = 1/(100/sqrt(pow(Xmax-originX,2)+pow((origineY)+Ymax,2)));
    double coef = (1750/sqrt(pow(Xmax-(originX+longGraph),2)+pow((origineY)+Ymax,2)));
    cout << "le coef est :" <<coef<<endl;
    //void floodfill(BITMAP *bmp, int x, int y, int color);

    line(arbo,originX,origineY,originX ,  origineY-longGraph, makecol(0,0,0)); /// ligne vertical
    line(arbo,originX , origineY,originX+longGraph , origineY, makecol(0,0,0)); /// ligne Horizontal

    textprintf_centre_ex(arbo,font,  originX +27 ,  origineY-longGraph ,   makecol(10, 61, 98),-1,"cout 1");
    textprintf_centre_ex(arbo,font,  originX+longGraph , origineY +5 ,   makecol(10, 61, 98),-1,"cout 2");


for(auto &p : nonPareto)
    circlefill(arbo, p.first*coef  ,origineY-p.second*coef  , 2, makecol(235, 47, 6));
for(auto &p : pareto)
    circlefill(arbo,coef*p.first, origineY-p.second*coef, 2, makecol(120, 224, 143));




//    if(mouse_x  == p.first*coef && mouse_y == origineY-p.second*coef && mouse_b & 1) // gauche : dessiner en rouge)
//        return i;


}


void Graphique::refresh(int couleurFond, BITMAP *fond,BITMAP * supportCourbe,BITMAP * supportGraphe, BITMAP *GrapheGeneral)
{
     clear_bitmap(fond);
    clear_bitmap(GrapheGeneral);
    clear_bitmap(supportGraphe);
    clear_bitmap(supportCourbe);

    rectfill(supportCourbe, 0,0, supportCourbe->w, supportCourbe->h, couleurFond);
    rectfill(supportGraphe, 0,0, supportGraphe->w, supportGraphe->h, couleurFond);
    rectfill(GrapheGeneral, 0,0, GrapheGeneral->w, GrapheGeneral->h, couleurFond);

    drawGraphe(GrapheGeneral);
    rectfill(fond, 0,0, SCREEN_W, SCREEN_H, couleurFond);
    rectfill(supportCourbe, 0,0, supportCourbe->w, supportCourbe->h, couleurFond);

    blit(GrapheGeneral,fond,50,50,0,0,GrapheGeneral->w,GrapheGeneral->h);
}


void Graphique::dessinerPareto(BITMAP * page,std::vector<pair<float,float>> &pareto )
{






}
//int Graphique::fairePrim()
//{
//    bool continu = true;
//    while(continu = true)
//    {
//        (this.primMST(0,1,0)).drawGraphe(supportGraphe);
//         (this.primMST(0,0,1)).drawGraphe(supportCourbe);
//    }
//
//    return
//}
