#include "graphe.h"
#include <random>
#include "time.h"
using namespace std;

int main()
{
	srand(time(NULL));
	Graphe espace("files/broadway.txt", "files/broadway_weights_0.txt");
	espace.dessinerGraphe();
	Graphe arbre = espace.dijkstraSPT("3");

	return 0;
}
