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
       BITMAP *prim;
       prim =load_bitmap("image/prim.bmp",NULL);
    if (!prim)  {
        allegro_message("pas pu trouver/charger mon_image.bmp");
        allegro_exit(); exit(EXIT_FAILURE);
    }

    int startX = 700;
    int finX = startX + 100;
    int startY = SCREEN_H/2 + 100;
    int finY = startY + 50;
    int CHOIX =4;


    rectfill(page, startX,startY, finX, startY + 50, makecol(126, 255, 245));
    rect(page, startX,startY, finX, startY + 50, makecol(0,0,0));

    rectfill(page, startX,startY+50, finX, startY + 100, makecol(126, 255, 245));
    rect(page, startX,startY+50, finX, startY + 100, makecol(0,0,0));

    rectfill(page, startX,startY+100, finX, startY + 150, makecol(126, 255, 245));
    rect(page, startX,startY+100, finX, startY + 150, makecol(0,0,0));

    rectfill(page, startX,startY+150, finX, startY + 200, makecol(126, 255, 245));
    rect(page, startX,startY+150, finX, startY + 200, makecol(0,0,0));


    for(int i=1;i<=CHOIX;i++)
    {

    if(mouse_x  > startX && mouse_x  < finX && mouse_y < (startY + 50*i) && mouse_y > startY&& mouse_b & 1) // gauche : dessiner en rouge)
        return i;
    }


}


void Graphique::drawNuage(BITMAP *arbo,vector<pair<float,float>> &pareto,vector<pair<float,float>> &nonPareto)
{

    int longGraph = 300;
    int originX = 50;
    int origineY = SCREEN_H/2 - 100;
    rectfill(arbo, 0,0, arbo->w, arbo->h, makecol(248, 194, 145));
    int coef = 10;
    //void floodfill(BITMAP *bmp, int x, int y, int color);

    line(arbo,originX,origineY,originX ,  origineY-longGraph, makecol(0,0,0)); /// ligne vertical
    line(arbo,originX , origineY,originX+longGraph , origineY, makecol(0,0,0)); /// ligne Horizontal

    textprintf_centre_ex(arbo,font,  originX -25 ,  origineY-longGraph ,   makecol(10, 61, 98),-1,"cout 1");
    textprintf_centre_ex(arbo,font,  originX+longGraph , origineY +5 ,   makecol(10, 61, 98),-1,"cout 2");


for(auto &p : nonPareto)
    circlefill(arbo, p.first*coef  ,origineY-p.second*coef  , 2, makecol(235, 47, 6));
for(auto &p : pareto)
    circlefill(arbo,coef*p.first, origineY-p.second*coef, 2, makecol(120, 224, 143));



//    if(mouse_x  == p.first*coef && mouse_y == origineY-p.second*coef && mouse_b & 1) // gauche : dessiner en rouge)
//        return i;


}
