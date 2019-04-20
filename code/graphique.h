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
    int menuInterne(BITMAP *page);

protected:
    std::string m_color_sommet;
    std::string m_color_arrete;
};

#endif