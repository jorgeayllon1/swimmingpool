#include "graphe.h"
#include "graphique.h"
#include "svgfile.h"

using namespace std;

Graphique::Graphique()
{
}

Graphique::~Graphique()
{
}

void Graphique::dessinerCourbe(Svgfile &svg)
{

    svg.addLine(700, 400, 700, 100, "black");
    svg.addLine(700, 400, 1000, 400, "black");
    svg.addText(650, 110, "cout1", "black");
    svg.addText(968, 420, "cout2", "black");

    for (int i = 0; i < 500; i++)
    {
        svg.addCross((rand() % 500) + 700, (rand() % 300) + 100, 5, "#576574");
    }
}