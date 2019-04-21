#include "graphe.h"
#include <random>
#include "time.h"
#include <allegro.h>
#include <time.h>
#include <bitset>
using namespace std;

int main()
{
    Graphe espace("files/manhattan.txt", "files/manhattan_weights_0.txt");

    
    vector<pair<float, float>> total;
    vector<vector<bool>> hein = espace.calcul_sousgraphes_admissibles(&total, true);

    for (unsigned int i = 0; i < hein.size(); i++)
    {
        for (unsigned int j = 0; j < hein[i].size(); j++)
        {
            cout << hein[i][j] << " ";
        }
        cout << endl;
    }
    /*
    cout<<"avec le graphe\n";
    Graphe autre = espace.dijkstraSPT(3, 0);
    cout<<"sans le graphe\n";
    cout << espace.dijkstraSPT(3, 0, false) << endl;
    */

    return 0;
}