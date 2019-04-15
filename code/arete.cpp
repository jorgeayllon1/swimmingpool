#include "arete.h"

using namespace std;

Arete::Arete(Sommet *depart, Sommet *arriver, float lepoids1, float lepoids2, float lepoids3) : m_depart(depart), m_arriver(arriver),
                                                                                                m_poids1(lepoids1), m_poids2(lepoids2), m_poids3(lepoids3)
{
}

void Arete::afficherData() const
{
    cout << "De " << m_depart->getId() << " a " << m_arriver->getId() << " en ( "<<m_poids1 <<" , "<< m_poids2 <<" )"<< endl;
}

Arete::Arete(Arete const &copie) : m_depart(copie.m_depart), m_arriver(copie.m_arriver), m_poids1(copie.m_poids1)
{
}

Arete::~Arete()
{
    m_depart = NULL;
    m_arriver = NULL;
}