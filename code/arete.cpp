#include "arete.h"

using namespace std;

Arete::Arete(Sommet *depart, Sommet *arriver, int lepoids) : m_depart(depart), m_arriver(arriver), m_poids(lepoids)
{
}

void Arete::afficherData() const
{
    cout << "De " << m_depart->getId() << " a " << m_arriver->getId() << " en " << m_poids << endl;
}

Arete::Arete(Arete const &copie) : m_depart(copie.m_depart), m_arriver(copie.m_arriver), m_poids(copie.m_poids)
{
}

Arete::~Arete()
{
    m_depart = NULL;
    m_arriver = NULL;
}

void Arete::dessiner(Svgfile &svg)
{
    svg.addLine(m_depart->getX(), m_depart->getY(), m_arriver->getX(), m_arriver->getY(), "red");
}