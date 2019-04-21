/// Déclaration de la classe Graphe

#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <cassert>
#include <list>
#include <map>
#include "sommet.h"
#include "arete.h"
#include "graphique.h"
#include "fonctionsutiles.h"

class Graphe : public Graphique
{
public:
  /****Constructeurs & Destructeurs****/
  Graphe() : m_ordre(0), m_taille(0){};
  Graphe(std::string nom_graphe, std::string nom_poids_graphe);
  virtual ~Graphe();

  /**** Déclaration des méthodes de Gestion graphe ****/
  void addSommet(int id_sommet,int coordx, int coordy);
  void addSommet(Sommet clone_sommet);
  void addArete(int id_arete, int sommet_1, int sommet_2, float poids_1, float poids_2, float poids_3);
  bool findSommet(int id_sommet);
  bool findArete(int id_arete);
  void afficherData() const;
  int indicesommet(int id_sommet) const;
  int indiceareteid(int id_arete) const;

  /****  Déclaration des méthodes de récupération des données ****/
  int getOrdre() const { return m_ordre; };
  int getTaille() const { return m_taille; };
  int getAreteid(int sommet_1,int sommet_2);
  std::pair<float,float> DonnePoids();

  /****Algorithme de théorie des graphes****/
  vector<pair<float, float>> Pareto(std::vector<std::pair<float, float>> &total, std::vector<std::pair<float, float>> *nonPareto,vector<vector<bool>> G);
  Graphe dijkstraSPT(int id_premier_sommet, int critere_poids);
  float dijkstraSPT(int id_premier_sommet, int critere_poids , bool affichage);
  Graphe primMST(int id_premier_sommet, int critere_poids_1, int critere_poids_2);
  int welshpowel();

  /***Solution admissibles des graphes***/
  bool test_connexite();
  Graphe Conversion(std::vector<bool> Binaire);
  vector<vector<bool>> calcul_sousgraphes_admissibles(vector<pair<float, float>> *total, bool cycle);
  bool check();
  int Temps_Parcours();

  /***Graphisme***/
  void dessinerGraphe(); // dessin du graphe en SVG
  void drawGraphe(BITMAP *arbo);    // dessin du graphe en allegro
  void drawSousGraphe(BITMAP *arborescence);

private:
  std::vector<Sommet *> m_sommets;
  std::vector<Arete *> m_aretes;
  int m_ordre;
  int m_taille;
};
#endif
