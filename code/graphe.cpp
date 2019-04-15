#include "graphe.h"
#include <fstream>

using namespace std;

void Graphe::addSommet(string lenom)
{
    if (!findSommet(lenom))
    {
        m_sommets.insert(make_pair(lenom, new Sommet(lenom)));
        m_ordre++;
    }
}

/// On ne peut pas crée d'arête entre des sommets qui ne sont pas dans le graphe
void Graphe::addArete(string leiddepart, string leidarriver, int poids, bool orienter)
{
    /// On verifie que les sommets existent dans le graphe
    assert(findSommet(leiddepart) && findSommet(leidarriver));

    m_aretes.insert(new Arete(m_sommets.find(leiddepart)->second, m_sommets.find(leidarriver)->second, poids));
    ///On ajoute l'arete au graphe, elle est defini par l'id de depart, l'id d'arriver et son poids

    m_sommets.find(leiddepart)->second->addVoisin(m_sommets.find(leidarriver)->second);
    /// Grâce à l'arete et son orientation, on peut definir un voisin du Sommet
    /// Ici on considère l'orientation : le sommet d'arriver n'a pas pour voisin le sommet de depart
    /// A -> B | A voisin : B | B voisin : rien

    ///Si le graphe n'est pas orienté, on crée une arête identique dans le sens contraire
    if (!orienter)
    {
        m_aretes.insert(new Arete(m_sommets.find(leidarriver)->second, m_sommets.find(leiddepart)->second, poids));
        /// Comme le graphe n'est pas orienté, on va considerer que le sommet d'arriver à pour voisin le sommet de départ
        /// A -> B et A <- B donc A <-> B donc A voisin : B et B voisin : A

        m_sommets.find(leidarriver)->second->addVoisin(m_sommets.find(leiddepart)->second);

        /// Si on n'est pas orienter on a des doublons d'arête, on met donc à jours les degrés des sommets
    }

    /// A CODER :
    /// Ameliorer les degrés de Sommet, faire deg entrant + sortant
    m_taille++;
}

Graphe::Graphe(string nomFichier, bool orienter, bool pondere) : m_ordre(0), m_taille(0)
{
    ifstream fiche(nomFichier);
    ///Penser à lire le README pour plus d'info sur comment crée un fichier qui a les données du graphe

    /// On verifie que le fichier existe bien
    assert(fiche);

    /// On commence par construire les sommets
    int recipOrdre = 0;
    fiche >> recipOrdre;
    for (int i = 0; i < recipOrdre; i++)
    {
        string leid;
        fiche >> leid;
        addSommet(leid);
    }

    /// Puis on construit les aretes
    int recipTaille = 0;
    fiche >> recipTaille;
    for (int i = 0; i < recipTaille; i++)
    {
        string recipiddepart;
        string recipidarriver;
        fiche >> recipiddepart;
        fiche >> recipidarriver;
        if (!pondere)
        {
            addArete(recipiddepart, recipidarriver, 0, orienter);
        }
        else
        {
            /// Si le graphe est ponderé on a une valeur de poid en plus. cf le README
            int recipPoids = 0;
            fiche >> recipPoids;
            addArete(recipiddepart, recipidarriver, recipPoids, orienter);
        }
    }
}

void Graphe::afficherData() const
{
    cout << "Graphe :" << endl;
    cout << "Je suis d'ordre " << m_ordre << endl;
    cout << "Mes sommets :" << endl;

    for (auto &i : m_sommets)
    {
        i.second->afficherData();
    }

    cout << endl;
    cout << "Je suis de taille " << m_taille << endl;
    cout << "Mes arête :" << endl;

    for (auto &i : m_aretes)
    {
        i->afficherData();
    }
}

/// Rend la copie d'un Sommet du graphe
Sommet Graphe::getSommetid(std::string nomid)
{
    if (findSommet(nomid))
        throw runtime_error("Id de sommet non trouver : graphe.cpp getSommetid");

    /// On appelle le constructeur de copie
    return Sommet(*m_sommets.find(nomid)->second);
}

void Graphe::addSommet(Sommet leclone)
{
    m_sommets.insert(make_pair(leclone.getId(), new Sommet(leclone)));
    m_ordre++;
}

bool Graphe::findSommet(string nomatrouver)
{
    return (m_sommets.find(nomatrouver) != m_sommets.end());
}

Graphe Graphe::primMST(string nomPremier)
{
    assert(findSommet(nomPremier));
    /// Initialisation
    Graphe leprim;
    leprim.addSommet(nomPremier);

    /// Variable temp
    Arete reciparete;
    Sommet recipsommet;

    do
    {
        int poidsMin = 9999; /// On met un poids infini
        ///On parcours toutes les arêtes du graphe pour trouvé l'arete au poids minimum
        for (auto &i : m_aretes)
        {
            /// Il faut que l'arete aillent a un nouveau sommet et qu'elle ne raccorde pas deux sommets déjà existant
            /// Donc il faut que le depart ou l'arrivé ne soit pas dans l'arbre
            /// Mais pas tout les deux dans l'arbre ou hors de l'arbre
            /// On utilise donc XOR
            /// On a la validité des arêtes en checkant l'arbre avec des objets du graphe(cette phrase est important mais très tricky)
            if (leprim.findSommet(i->getdepart().getId()) ^ leprim.findSommet(i->getarriver().getId()))
            {
                if (poidsMin > i->getpoids()) /// On recup l'arete au poids minimum qui est valide
                {
                    /// Remarque : le > est arbitraire
                    /// La file de priorité se code dans ce if
                    reciparete = *i;
                    poidsMin = i->getpoids();
                }
            }
        }

        /// On indique le sommet manquant à l'arbre
        if (leprim.findSommet(reciparete.getarriver().getId()))
        {
            recipsommet = reciparete.getdepart();
        }
        else
        {
            recipsommet = reciparete.getarriver();
        }

        /// On ajoute tout ça dans l'arbre
        leprim.addSommet(recipsommet.getId());
        leprim.addArete(reciparete.getdepart().getId(), reciparete.getarriver().getId(), reciparete.getpoids(), false);
        /// Remarque : on ne peut pas rajouter une arête avant de rajouter le sommet
        /// Il faut que le sommet existe dans l'arbre

    } while (leprim.getOrdre() != m_ordre);
    /// Tant que l'arbre n'a pas le même degré que le graphe

    return leprim;
}

Graphe::~Graphe()
{
    ///Ca veut dire quoi dtor ?
    ///Ah ok, c'est destructor
}

void Graphe::removeSommet(string lenom, bool orienter)
{
    ///Si le sommet n'existe pas on essaye pas de l'effacer
    assert(m_sommets.find(lenom) != m_sommets.end());

    for (unsigned int i = 0; i < m_aretes.size() + 1; i++)
    {
        Arete *recip = NULL;

        for (auto &i : m_aretes)
        {
            /*
            if (i->getdepart().getId() == lenom)
            {
                cerr << "j'ai trouvé ";
                i->afficherData();
                removeArete(lenom, i->getarriver().getId(), orienter);
            }

            if (i->getarriver().getId() == lenom)
            {
                cerr << "j'ai aussi trouvé ";
                i->afficherData();
                removeArete(i->getdepart().getId(), lenom, orienter);
            }
            */
            if (i->getdepart().getId() == lenom || i->getarriver().getId() == lenom)
            {
                recip = i;
                break;
            }
        }
        if (recip != NULL)
            removeArete(recip->getdepart().getId(), recip->getarriver().getId(), orienter);
    }

    m_sommets.erase(lenom);

    m_ordre--;
}

void Graphe::removeArete(string depart, string arriver, bool orienter)
{
    /// Variable temp
    Arete *reciparete;

    /// On cherche dans toutes les aretes du graphe
    for (auto &i : m_aretes)
    {
        if (i->getdepart().getId() == depart && i->getarriver().getId() == arriver)
        {
            /// Si on trouve la bonne, on la met dans un coté et on sort de boucle
            reciparete = i;
            break;
        }
    }

    /// On supprime l'arete
    /// On blinde si on ne trouve pas l'arete
    if (reciparete == NULL)
        throw runtime_error("Arete non trouvé");
    else
    {
        m_aretes.erase(reciparete);
        m_sommets.find(depart)->second->erasevoisin(arriver);
    }

    /// Si le graphe est non orienter, il y a une arete qui va dans l'autre sens
    /// On la cherche et on l'ellimine aussi
    if (!orienter)
    {
        for (auto &i : m_aretes)
        {
            if (i->getdepart().getId() == arriver && i->getarriver().getId() == depart)
            {
                reciparete = i;
                break;
            }
        }

        if (reciparete == NULL)
            throw runtime_error("Arete non trouvé");
        else
        {
            m_aretes.erase(reciparete);
            m_sommets.find(arriver)->second->erasevoisin(depart);
        }
    }

    /// On n'oublie pas de mettre à jours la taille du graphe
    m_taille--;
}

Graphe Graphe::dijkstraSPT(string nomPremier)
{
    assert(findSommet(nomPremier));

    Graphe ledijkstra;

    /// IMPORTANT :
    /// On considère qu'un sommet est marquée (qu'on a trouvé son plus court chemin) si il est dans le graphe ledijkstra

    map<string, pair<string, int>> distancechemins;
    /// Distance entre le depart et le sommet

    for (auto &i : m_sommets)
    {
        distancechemins.insert(make_pair(i.second->getId(), make_pair(" ", 9999)));
    }
    /// On ajoute tout les chemins au ensemble d'information

    distancechemins.find(nomPremier)->second.second = 0;
    /// Le sommet de depart a une distance nulle à lui-même

    string nomdumoment = nomPremier;
    /// Nom du sommet selectionner

    do
    {
        for (auto &i : m_aretes)
        {
            if (i->getdepart().getId() == nomdumoment && !ledijkstra.findSommet(i->getarriver().getId()))
            {
                /// Si l'arete par de notre sommet
                /// Et i l'arete ne va pas dans un sommet deja validé par l'algorithme
                /// On ne va pas rechecker la distance pour un sommet qui a déjà un plus court chemin
                if (i->getpoids() + distancechemins.find(nomdumoment)->second.second < distancechemins.find(i->getarriver().getId())->second.second)
                {
                    /// Les sommets gardent toujours leur distance à l'origine
                    /// Si la distance à l'orgine + celle de la nouvelle arete est plus petite que la valeur precedente dans les données
                    /// Je vois pas trop comment traduire cette ligne, faut vraiment comprendre dijkstra
                    distancechemins.find(i->getarriver().getId())->second.first = nomdumoment;
                    distancechemins.find(i->getarriver().getId())->second.second = i->getpoids() + distancechemins.find(nomdumoment)->second.second;
                    /// On met à jours la distance au sommet de l'indice parcouru
                }
            }
        }

        int poidrecip = 9999;
        /// On cherche la distance minimale non déjà validée

        for (auto &i : distancechemins)
        {
            if (i.second.second < poidrecip && !ledijkstra.findSommet(i.first))
            {
                /// Si la distance est minimale est non marquée
                nomdumoment = i.first;
                poidrecip = i.second.second;
            }
        }

        ///nomdumoment devient le sommet de refference et on le marque
        ledijkstra.addSommet(nomdumoment);

    } while (ledijkstra.getOrdre() != m_ordre);

    for (auto &i : distancechemins)
    {
        cout << i.first << " : " << i.second.first << " | " << i.second.second << endl;
    }

    ///Code à faire :
    ///Mettre à jours les arêtes du graphe grâce au plus court chemin

    return ledijkstra;
}

///Graphisme
void Graphe::dessinerGraphe()
{

    Svgfile svg;

    svg.addGrid();
    for (auto &s : m_aretes)
        s->dessiner(svg);
    for (auto &s : m_sommets)
        (s.second)->dessiner(svg);
}