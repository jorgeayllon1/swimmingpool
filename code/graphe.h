#ifndef GRAPHE_H
#define GRAPHE_H
#include <iostream>
#include <string>
#include "sommet.h"
#include "arete.h"
#include <cassert>
#include "graphique.h"
#include <algorithm>
#include <sstream>
#include <math.h>
///Pour dijkstra
#include <map>

class Graphe : public Graphique
{
public:
  Graphe() : m_ordre(0), m_taille(0){};
  Graphe(std::string nom_graphe,std::string nom_poids_graphe);
  void afficherData() const;
  void addSommet(int lenom, int coordx, int coordy);
  void addSommet(Sommet leclone);
  void addArete(int lenom,int leiddepart,int leidarriver, float poids1, float poids2, float poids3);
  void removeSommet(int lenom, bool orienter); ///Pas fini
  void removeArete(int depart, int arriver, bool orienter);
  int getOrdre() { return m_ordre; };
  Sommet getSommetid(int nomid);
  Graphe dijkstraSPT(int nompremier);
  /// tuple utilisable ??
  /// Peut être list<tuple>
  Graphe primMST(int nomPremier);
  bool findSommet(int nomatrouver);
  std::vector<std::vector<bool>> calcul_sousgraphes_admissibles(std::vector<std::pair<float,float>> *total);
  bool test_connexite();
  Graphe Conversion(std::vector<bool> Binaire);
  void Pareto(std::vector<std::pair<float,float>> &total);
  std::pair<float,float> DonnePoids();
  ~Graphe();

  //graphisme
  void dessinerGraphe();

private:
  std::vector<Sommet *> m_sommets;
  std::vector<Arete *> m_aretes;
  int m_ordre;
  int m_taille;
};

#endif
