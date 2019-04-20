#include "graphe.h"
#include <random>
#include "time.h"
#include <allegro.h>
#include <time.h>
#include <bitset>
using namespace std;

int main()
{
    Graphe espace("files/manhattan.txt","files/manhattan_weights_0.txt");
    int nbdecoul = espace.welshpowel();
    cout<<nbdecoul<<endl;
    //Graphe autre = espace.dijkstraSPT(3,0,false).second;
    return 0;
}