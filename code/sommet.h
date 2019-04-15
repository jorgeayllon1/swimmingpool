#ifndef SOMMET_H
#define SOMMET_H
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <unordered_set>
#include "svgfile.h"
#include "graphique.h"

class Sommet : public Graphique
{
public:
  Sommet() : m_id(""), m_valeurrelative(0), m_degre(0), m_x(rand() % 500), m_y(rand() % 500){};
  Sommet(std::string nom) : m_id(nom), m_valeurrelative(0), m_degre(0), m_x(rand() % 500), m_y(rand() % 500){};
  Sommet(Sommet const &copie);
  ~Sommet(){};
  void afficherData() const;
  std::string getId() const
  {
    return m_id;
  };
  int getX() const
  {
    return m_x;
  };
  int getY() const
  {
    return m_y;
  };
  void addVoisin(Sommet *levoisin);
  void setvaleurrelative(int val)
  {
    m_valeurrelative = val;
  };
  int getvaleurrelative() const
  {
    return m_valeurrelative;
  };
  void erasevoisin(std::string lenom);
  void dessiner(Svgfile &svg);

private:
  std::string m_id;
  int m_valeurrelative; /// Poids temp pour Prim algo
  /// J'ai mis unordered_set au lieu de vector car on a pas besoin de classer les voisins
  /// On a un meilleur accé au valeur grâce à unordered_set
  std::unordered_set<Sommet *> m_voisins;
  ///On va dire qu'un sommet a des voisins
  ///Au lieu de dire que des sommets sont liés par des aretes
  ///rip, c'est ce que je voulais faire à la base
  ///Inchallah j'ameliore le code après
  int m_degre;
  int m_x;
  int m_y;
};

#endif
