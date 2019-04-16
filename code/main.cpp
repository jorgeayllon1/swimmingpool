#include "graphe.h"
#include <random>
#include "time.h"
using namespace std;

int main()
{
	srand(time(NULL));
	Graphe espace("info1.txt", "info1_weights.txt");
	Graphe arbre = espace.dijkstraSPT("B");
	arbre.afficherData();
	arbre.dessinerGraphe();

	return 0;
}
