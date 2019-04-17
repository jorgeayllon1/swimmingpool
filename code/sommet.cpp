#include "sommet.h"
#include <random>

using namespace std;

void Sommet::afficherData() const
{
    cout << "Mon id est " << m_id << endl
         << "Je suis de degré " << m_degre << endl
         << "Je suis en "
         << "( " << m_coordx << " , " << m_coordy << " )\n"
         << "Je vois:\n";

    if (m_voisins.size())
    {
        for (auto &i : m_voisins)
        {
            cout << "\t" << i->getId() << endl;
        }
    }
    else
    {
        cout << "\trien" << endl;
    }
}

///Attention, cette fonction ne crée pas d'arête entre les deux sommets
/// TRES IMPORTANT ! : Lors de la recherche dans m_voisins
/// Il faut checker le string associer au sommet et non le sommet lui-même
/// Attention : Gros risque de mauvaise manipulation de Sommet
void Sommet::addVoisin(Sommet *levoisin)
{
    bool trouve = false;
    
    for (auto &i : m_voisins)
    {
        if (i->getId() == levoisin->getId())
        {
            trouve = true;
            break;
        }
    }

    if (!trouve)
    {
        m_voisins.push_back(levoisin);
        sort(m_voisins.begin(),m_voisins.end());
        m_degre++;
    }
    else throw runtime_error("Error tu ajoutes un voisin qui n'existe pas\n");

}

Sommet::Sommet(Sommet const &copie) : m_id(copie.m_id), m_valeurrelative(copie.m_valeurrelative),
                                      m_voisins(copie.m_voisins), m_degre(copie.m_degre), m_coordx(copie.m_coordx), m_coordy(copie.m_coordy)
{
    /// La ligne m_voisins(copie.m_voisins) est très puissante
    /// Au lieu de réorienter les pointeurs
    ///elle crée d'elle-même des copies du contenu du vector
    /// Vive la stl mdr
}

void Sommet::erasevoisin(int lenom)
{
    /// Variable temp
    Sommet *recip = NULL;

    /// On cherche le voisin a enlever
    /// On evite de faire find car on prefere passer par les string des sommets
    /// Plutot que d'utiliser les pointeurs
    /// C'est plus securisé pour la memoire
    for (auto &i : m_voisins)
    {
        if (i->getId() == lenom)
        {
            recip = i;
            break;
        }
    }
    if (recip)
    {
        m_voisins.erase(m_voisins.begin() + recip->m_id);
        m_degre--;
    }
}

void Sommet::dessiner(Svgfile &svg)
{
    svg.addDisk(m_coordx, m_coordy, 5, "black");
}

bool Sommet::findVoisin(int lenom) const
{
    for (auto &i : m_voisins)
    {
        if (i->getId() == lenom)
            return true;
    }
    return false;
}

std::unordered_map<int, int> Sommet::parcoursDFS() const
{

    std::unordered_map<int, int> l_pred; ///ensemble des prédécesseur de this

    std::unordered_set<int> l_dec; ///ensemble des sommets decouverts

    std::stack<const Sommet *> pile; ///pile nécessaire au dfs

    pile.push(this); ///On empile le premier sommet

    l_dec.insert(this->m_id); ///il est decouvert

    ///Tant que la pile n'est pas vide
    do
    {
        Sommet *tampon = new Sommet(*pile.top()); ///On crée une copie du sommet que l'on va traité

        pile.pop(); ///Dépiler le prochain sommet

        for (auto s : tampon->m_voisins)
        { ///Pour chaque successeur s

            std::unordered_set<int>::const_iterator it = l_dec.find(s->m_id);
            if (it == l_dec.end())
            { ///Si il n'est pas decouvert

                l_dec.insert(s->m_id); ///Empiler s

                l_pred.insert(make_pair(s->m_id, tampon->m_id)); ///Noter que s est le prédécesseur de s

                pile.push(s);
            }
        }
    } while (!pile.empty());

    return l_pred; ///on renvoie l'ensembles de predeceur de this
}