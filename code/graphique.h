#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <allegro.h>
#include <sstream>
#include <vector>

using namespace std;

template <typename T>
  std::string NumberToString ( T Number )
  {
     std::ostringstream ss;
     ss << Number;
     return ss.str();
  }

class Graphique
{
public:
    Graphique();
    virtual ~Graphique();
    void dessiner(Svgfile &svg);
    void drawNuage(BITMAP *arbo,vector<pair<float,float>> &pareto,vector<pair<float,float>> &nonPareto);
    virtual int menuInterne(BITMAP *page);
    virtual void refresh(int couleurFond, BITMAP *fond,BITMAP * supportCourbe,BITMAP * supportGraphe, BITMAP *GrapheGeneral);
    virtual void drawGraphe(BITMAP *){}

protected:
    std::string m_color_sommet;
    std::string m_color_arrete;
};

#endif
