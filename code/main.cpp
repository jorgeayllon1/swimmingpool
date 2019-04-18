#include "graphe.h"
#include <random>
#include "time.h"
using namespace std;

int main()
{
	srand(time(NULL));
	Graphe espace("files/manhattan.txt", "files/manhattan_weights_0.txt");

	pair<float, float> coordscout1 = espace.primMST(0, 0, 1);
	pair<float, float> coordscout2 = espace.primMST(0, 1, 0);

	/// Petite permutation pour avoir le bon x et y
	float recip = 0;
	recip=coordscout2.first;
	coordscout2.first=coordscout2.second;
	coordscout2.second=recip;

	cout << "la coordscout1 sont : " << coordscout1.first << " " << coordscout1.second << endl;
	cout << "la coordscout2 sont : " << coordscout2.first << " " << coordscout2.second << endl;

	return 0;
}
