#include "arete.h"
#include "graphe.h"
#include <fstream>

#include <sstream>

template <typename T>
std::string NumberToString(T Number)
{
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}

using namespace std;

Arete::Arete(string lenom, Sommet *depart, Sommet *arriver, float lepoids1, float lepoids2, float lepoids3) : m_nom(lenom), m_depart(depart), m_arriver(arriver),
                                                                                                              m_poids1(lepoids1), m_poids2(lepoids2), m_poids3(lepoids3)
{
}

void Arete::afficherData() const
{
    cout << "Je suis " << m_nom << " : De " << m_depart->getId() << " a " << m_arriver->getId() << " en ( " << m_poids1 << " , " << m_poids2 << " )" << endl;
}

Arete::Arete(Arete const &copie) : m_nom(copie.m_nom), m_depart(copie.m_depart), m_arriver(copie.m_arriver), m_poids1(copie.m_poids1)
{
}

Arete::~Arete()
{
    m_depart = NULL;
    m_arriver = NULL;
}

///Graphisme
void Arete::dessiner(Svgfile &svg)
{
    svg.addLine(m_depart->getcoordx(), m_depart->getcoordy(), m_arriver->getcoordx(), m_arriver->getcoordy(), "#e55039");

    string cout1 = NumberToString(m_poids1);
    string cout2 = NumberToString(m_poids2);
    string val = cout1 + ";" + cout2;
    if (m_poids3)
    {
        string cout3 = NumberToString(m_poids3);
        val = val + ";" + cout3;
    }
    svg.addText((m_depart->getcoordx() + m_arriver->getcoordx()) / 2 - 10, (m_depart->getcoordy() + m_arriver->getcoordy()) / 2 - 5, val, "#3c6382");
}

///Excel
void Arete::writeData(ofstream &outData)
{
    outData << m_nom << "   ; " << m_depart->getId() << "   ; " << m_arriver->getId() << "  ; " << m_poids1 << "    ;" << m_poids2 << " ;" << endl;
}
