#include "graphe.h"
#include <random>
#include "time.h"
#include <windows.h>
using namespace std;

int main()
{
	srand(time(NULL));
	vector<pair<float,float>> total;
	Graphe espace("manhattan.txt", "manhattan_weights_0.txt");
	espace.dessinerGraphe();
	//espace = espace.dijkstraSPT(3);
	espace.afficherData();
	vector<vector<bool>> G = espace.calcul_sousgraphes_admissibles(&total);

//	for(int i=0;i<G.size();i++)
//    {
      espace.Conversion(G[0]).dessinerGraphe();
espace.Pareto(total);


//       Sleep(3000);
//
//    }

	return 0;
}
