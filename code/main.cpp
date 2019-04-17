#include "graphe.h"
#include <random>
#include "time.h"
using namespace std;

int main()
{
	srand(time(NULL));
	Graphe espace("files/manhattan.txt", "files/manhattan_weights_0.txt");
	Graphe arbre = espace.primMST(3, 0);
	arbre.dessinerGraphe();
	Graphe autre = espace.dijkstraSPT(0, 1);

	return 0;
}
