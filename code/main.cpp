#include "graphe.h"
#include <random>
#include "time.h"
using namespace std;

int main()
{
	srand(time(NULL));
	Graphe espace("files/broadway.txt", "files/broadway_weights_0.txt");
	int a = espace.welshpowel();
	return 0;
}
