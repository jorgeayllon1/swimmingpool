#ifndef ARETE_H
#define ARETE_H
#include <iostream>
#include "sommet.h"
#include <string>

class Arete
{
public:
  Arete() : m_depart(NULL), m_arriver(NULL), m_poids1(0), m_poids2(0), m_poids3(0){};
  Arete(Sommet *depart, Sommet *arriver, float lepoids1, float lepoids2, float lepoids3 = 0);
  Arete(Arete const &copie);
  Sommet getdepart() const { return *m_depart; };
  Sommet getarriver() const { return *m_arriver; };
  float getpoids1() const { return m_poids1; };
  float getpoids2() const { return m_poids2; };
  ~Arete();

  void afficherData() const;

private:
  Sommet *m_depart;
  Sommet *m_arriver;
  float m_poids1;
  float m_poids2;
  float m_poids3;
};

#endif
