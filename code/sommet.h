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
  Sommet() : m_id(0), m_valeurrelative(0), m_degre(0), m_coordx(0), m_coordy(0){};
  Sommet(int nom, int lacoordx, int lacoordy) : m_id(nom), m_valeurrelative(0),
                                                        m_degre(0), m_coordx(lacoordx), m_coordy(lacoordy){};
  Sommet(Sommet const &copie);
  ~Sommet(){};
  void afficherData() const;
  int getId() const { return m_id; };
  void addVoisin(Sommet *levoisin);
  void setvaleurrelative(int val) { m_valeurrelative = val; };
  int getvaleurrelative() const { return m_valeurrelative; };
  void erasevoisin(int lenom);
  void dessiner(Svgfile &svg);
  void draw(BITMAP *);
  int getcoordx() const { return m_coordx; };
  int getcoordy() const { return m_coordy; };

private:
  int m_id;
  int m_valeurrelative; /// Poids temp pour Prim algo
  /// J'ai mis unordered_set au lieu de vector car on a pas besoin de classer les voisins
  /// On a un meilleur accé au valeur grâce à unordered_set
  std::vector<Sommet *> m_voisins;
  ///On va dire qu'un sommet a des voisins
  ///Au lieu de dire que des sommets sont liés par des aretes
  ///rip, c'est ce que je voulais faire à la base
  ///Inchallah j'ameliore le code après
  int m_degre;
  int m_coordx;
  int m_coordy;
};

#endif
