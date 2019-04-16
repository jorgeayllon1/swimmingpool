#ifndef GRAPHE_H
#define GRAPHE_H
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "sommet.h"
#include "arete.h"
#include <cassert>
#include "graphique.h"
///Pour dijkstra
#include <map>

class Graphe : public Graphique
{
public:
  Graphe() : m_ordre(0), m_taille(0){};
  Graphe(std::string nom_graphe,std::string nom_poids_graphe, bool orienter, bool pondere);
  void afficherData() const;
  void addSommet(std::string lenom, int coordx, int coordy);
  void addSommet(Sommet leclone);
  void addArete(std::string lenom,std::string leiddepart, std::string leidarriver, float poids1, float poids2, float poids3, bool orienter);
  void removeSommet(std::string lenom, bool orienter); ///Pas fini
  void removeArete(std::string depart, std::string arriver, bool orienter);
  int getOrdre() { return m_ordre; };
  Sommet getSommetid(std::string nomid);
  Graphe dijkstraSPT(std::string nompremier);
  /// tuple utilisable ??
  /// Peut être list<tuple>
  Graphe primMST(std::string nomPremier);
  bool findSommet(std::string nomatrouver);
  std::vector<Graphe> calcul_sousgraphes_admissibles();
  bool test_connexite();
  ~Graphe();

  //graphisme
  void dessinerGraphe();

private:
  std::unordered_map<std::string, Sommet *> m_sommets;
  std::unordered_map<std::string,Arete *> m_aretes;
  int m_ordre;
  int m_taille;
};

#endif
