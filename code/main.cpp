#include "graphe.h"
#include <random>
#include "time.h"
#include <allegro.h>
#include <time.h>
#include <bitset>
using namespace std;

int main()
{
    Graphe espace("files/broadway.txt", "files/broadway_weights_0.txt");

    ///Graphe autre = espace.dijkstraSPT(0, 0, false).second;

    return 0;
}