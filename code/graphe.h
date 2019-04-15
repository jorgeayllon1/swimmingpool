#ifndef GRAPHE_H
#define GRAPHE_H
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include "sommet.h"
#include "arete.h"
#include <cassert>
///Pour dijkstra
#include <map>

class Graphe
{
public:
  Graphe() : m_ordre(0), m_taille(0){};
  Graphe(std::string nomFichier, bool orienter, bool pondere);
  void afficherData() const;
  void addSommet(std::string lenom);
  void addSommet(Sommet leclone);
  void addArete(std::string leiddepart, std::string leidarriver, int poids, bool orienter);
  void removeSommet(std::string lenom, bool orienter); ///Pas fini
  void removeArete(std::string depart, std::string arriver, bool orienter);
  int getOrdre() { return m_ordre; };
  Sommet getSommetid(std::string nomid);
  Graphe dijkstraSPT(std::string nompremier);
  /// tuple utilisable ??
  /// Peut être list<tuple>
  Graphe primMST(std::string nomPremier);
  bool findSommet(std::string nomatrouver);
  ~Graphe();

private:
  std::unordered_map<std::string, Sommet *> m_sommets;
  std::unordered_set<Arete *> m_aretes;
  int m_ordre;
  int m_taille;
};

#endif
