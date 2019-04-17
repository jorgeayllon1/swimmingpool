#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <allegro.h>
#include <sstream>

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
    ~Graphique();
    void dessiner(Svgfile &svg);

protected:
    std::string m_color_sommet;
    std::string m_color_arrete;
};

#endif
