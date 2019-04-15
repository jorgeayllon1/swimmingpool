#include "graphe.h"
#define orienter false

using namespace std;

int main()
{
	Graphe espace("info3.txt", orienter, true);
	Graphe arbre = espace.dijkstraSPT("A");
	return 0;
}
