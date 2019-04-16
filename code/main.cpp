#include "graphe.h"
#include <random>
#include "time.h"
#define orienter false
using namespace std;

int main()
{
	srand(time(NULL));
	Graphe espace("manhattan.txt", "manhattan_weights_0.txt", orienter, true);
	Graphe arbre = espace.dijkstraSPT("0");
	//espace.dessinerGraphe();
	espace.afficherData();
    std::vector<Graphe>sous_graphes = espace.calcul_sousgraphes_admissibles();
	sous_graphes[14].dessinerGraphe();
	return 0;
}
