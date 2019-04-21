#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include "sommet.h"
#include "arete.h"
#include <cassert>
#include "graphique.h"
#include "fonctionsutiles.h"
#include <list>
///Pour dijkstra
#include <map>

class Graphe : public Graphique
{
public:
  /****Constructeurs & Destructeurs****/
  Graphe() : m_ordre(0), m_taille(0){};
  Graphe(std::string nom_graphe, std::string nom_poids_graphe);
  virtual ~Graphe();

  /****Gestion graphe****/
  void addSommet(int lenom, int coordx, int coordy);
  void addSommet(Sommet leclone);
  void addArete(int lenom, int depart, int arriver, float poids1, float poids2, float poids3);
  void removeSommet(int lenom, bool orienter); ///Pas fini
  void removeArete(int depart, int arriver, bool orienter);
  bool findSommet(int nomatrouver);
  bool findArete(int nomatrouver);
  void afficherData() const;
  int indicesommet(int nomsommet) const;
  int indiceareteid(int nomarete) const;

  /**** get ****/
  int getOrdre() const { return m_ordre; };
  int getTaille() { return m_taille; };
  int getAreteid(int depart, int arriver);
  std::pair<float, float> DonnePoids();

  /****Algorithme****/
  vector<pair<float, float>> Pareto(std::vector<std::pair<float, float>> &total, std::vector<std::pair<float, float>> *nonPareto);
  Graphe dijkstraSPT(int nompremier, int critere);
  float dijkstraSPT(int nompremier, int critere , bool affichage);
  Graphe primMST(int nomPremier, int critereprim, int autrecritere);
  int welshpowel();

  /***Solution admissibles***/
  bool test_connexite();
  Graphe Conversion(std::vector<bool> Binaire);
  vector<vector<bool>> calcul_sousgraphes_admissibles(vector<pair<float, float>> *total, bool cycle);
  bool check();
  int Temps_Parcours();

  /***graphisme***/
  void dessinerGraphe();
  void drawGraphe(BITMAP *arbo);
  void drawSousGraphe(BITMAP *arborescence);

private:
  std::vector<Sommet *> m_sommets;
  std::vector<Arete *> m_aretes;
  int m_ordre;
  int m_taille;
};
#endif
