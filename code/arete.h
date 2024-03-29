#ifndef ARETE_H
#define ARETE_H
#include "sommet.h"
#include <string>
#include "graphique.h"

class Arete : public Graphique
{
public:
  Arete();
  Arete(int lenom, Sommet *depart, Sommet *arriver, float lepoids1, float lepoids2, float lepoids3 = 0);
  Arete(Arete const &copie);
  int getnom() const { return m_nom; };
  Sommet getdepart() const { return *m_depart; };
  Sommet getarriver() const { return *m_arriver; };
  float getpoids(int i) const { return m_poids[i]; };
  ~Arete();
  void afficherData() const;
  void dessiner(Svgfile &svg);
  void draw(BITMAP *arbo);
  void drawS(BITMAP *arbo);

private:
  int m_nom;
  Sommet *m_depart;
  Sommet *m_arriver;
  float m_poids[4];
};

#endif