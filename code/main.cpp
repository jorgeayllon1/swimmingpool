#include "graphe.h"
#include <random>
#include "time.h"
using namespace std;

int main()
{
	srand(time(NULL));
	Graphe espace("files/cubetown.txt", "files/cubetown_weights_0.txt");
	espace.dessinerGraphe();
	espace = espace.dijkstraSPT("3");
	espace.dessinerGraphe();

	return 0;
}
