#ifndef ARETE_H
#define ARETE_H
#include <iostream>
#include "sommet.h"
#include <string>
#include "graphique.h"

class Arete : public Graphique
{
public:
  Arete() : m_depart(NULL), m_arriver(NULL), m_poids(0){};
  Arete(Sommet *depart, Sommet *arriver, int lepoids);
  Arete(Arete const &copie);
  Sommet getdepart() { return *m_depart; };
  Sommet getarriver() { return *m_arriver; };
  int getpoids() { return m_poids; };
  ~Arete();
  void afficherData() const;
  void dessiner(Svgfile &svg);

private:
  Sommet *m_depart;
  Sommet *m_arriver;
  int m_poids;
};

#endif
