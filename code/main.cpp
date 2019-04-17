#include "graphe.h"
#include <random>
#include "time.h"
using namespace std;

int main()
{
	srand(time(NULL));
	Graphe espace("files/manhattan.txt", "files/manhattan_weights_0.txt");
	espace = espace.primMST(12);
	espace = espace.dijkstraSPT(8);

	return 0;
}
