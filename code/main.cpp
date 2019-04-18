#include "graphe.h"
#include <random>
#include "time.h"
using namespace std;

int main()
{
	srand(time(NULL));
	Graphe espace("files/manhattan.txt", "files/manhattan_weights_0.txt");
	int fin = espace.dijkstraSPT(12, 0);
	cout << "le cout total est " << fin << endl;

	return 0;
}
