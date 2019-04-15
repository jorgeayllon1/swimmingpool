#include "graphe.h"
#define orienter false

using namespace std;

int main()
{
	Graphe espace("files/broadway.txt", "files/broadway_weights_0.txt", orienter, true);
	espace.afficherData();
	///Graphe arbre = espace.dijkstraSPT("A");
	///Graphe autre = espace.primMST("A");
	return 0;
}