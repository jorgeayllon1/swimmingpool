#include "graphe.h"
#include <random>
#include "time.h"
#define orienter false
using namespace std;

int main()
{
	srand(time(NULL));
	Graphe espace("manhattan.txt", "manhattan_weights_0.txt", orienter, true);
	//Graphe arbre = espace.dijkstraSPT("0");
	//Graphe arbrePrim = espace.primMST("0");

	espace.dessinerGraphe();

	return 0;
}
