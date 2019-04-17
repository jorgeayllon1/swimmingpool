#include "graphe.h"
#include <fstream>
#include <allegro.h>
#include <sstream>
using namespace std;



void pred(int sommetinit, int a, vector<int> lespred)
{
    if (lespred[a] == sommetinit)
    {
        /// Si on atteint le sommet de depart, on l'affiche et la fonction se termine
        cout << sommetinit << " ";
    }
    else
    {
        cout << lespred[a] << " ";
        ///On affiche le precedent du sommet
        pred(sommetinit, lespred[a], lespred);
        /// On appelle la fonction recursivement pour appeller le precedent du precedent
    }
}
/// Enlever et mettre dans algorithme.cpp
void Graphe::addSommet(int lenom, int coordx, int coordy)
{
    if (!findSommet(lenom))
    {
        //m_sommets.insert(make_pair(lenom, new Sommet(lenom, coordx, coordy)));
        m_sommets.push_back(new Sommet(lenom, coordx, coordy));
        m_ordre++;
    }
    else
        cerr << "ERROR, sommet trouvé\n";
}

/// On ne peut pas crée d'arête entre des sommets qui ne sont pas dans le graphe
void Graphe::addArete(int lenom, int leiddepart, int leidarriver, float poids1, float poids2, float poids3)
{
    /// On verifie que les sommets existent dans le graphe
    assert(findSommet(leiddepart) && findSommet(leidarriver));

    //m_aretes.insert(make_pair(lenom, new Arete(lenom, m_sommets.find(leiddepart)->second, m_sommets.find(leidarriver)->second, poids1, poids2, poids3)));
    m_aretes.push_back(new Arete(lenom, m_sommets[leiddepart], m_sommets[leidarriver], poids1, poids2, poids3));
    ///On ajoute l'arete au graphe, elle est defini par l'id de depart, l'id d'arriver et son poids

    m_sommets[leiddepart]->addVoisin(m_sommets[leidarriver]);
    m_sommets[leidarriver]->addVoisin(m_sommets[leiddepart]);
    /// Grâce à l'arete et son orientation, on peut definir un voisin du Sommet
    /// Ici on considère l'orientation : le sommet d'arriver n'a pas pour voisin le sommet de depart
    /// A -> B | A voisin : B | B voisin : rien

    ///Si le graphe n'est pas orienté, on crée une arête identique dans le sens contraire
    /*
    if (!orienter)
    {
        string putaindedoublons = "2";
        cerr << "je ne suis pas orienter ! \n";
        m_aretes.insert(make_pair(lenom + putaindedoublons, new Arete(lenom, m_sommets.find(leidarriver)->second, m_sommets.find(leiddepart)->second, poids1, poids2, poids3)));
        /// Comme le graphe n'est pas orienté, on va considerer que le sommet d'arriver à pour voisin le sommet de départ
        /// A -> B et A <- B donc A <-> B donc A voisin : B et B voisin : A

        m_sommets.find(leidarriver)->second->addVoisin(m_sommets.find(leiddepart)->second);

        /// Si on n'est pas orienter on a des doublons d'arête, on met donc à jours les degrés des sommets
    }
    */

    /// A CODER :
    /// Ameliorer les degrés de Sommet, faire deg entrant + sortant
    m_taille++;
}

Graphe::Graphe(string nom_graphe, string nom_poids_graphe) : m_ordre(0), m_taille(0)
{
    ifstream fiche(nom_graphe);
    ifstream fichepoids(nom_poids_graphe);
    ///Penser à lire le README pour plus d'info sur comment crée un fichier qui a les données du graphe

    /// On verifie que le fichier existe bien
    assert(fiche);
    assert(fichepoids);

    /// On commence par construire les sommets
    int recipOrdre = 0;
    fiche >> recipOrdre;
    for (int i = 0; i < recipOrdre; i++)
    {
        int leid;
        int lacoordx;
        int lacoordy;

        /// Chaque sommet est defini par son nom et ses coordonnées
        fiche >> leid;
        fiche >> lacoordx;
        fiche >> lacoordy;
        addSommet(leid, lacoordx, lacoordy);
    }

    /// Puis on construit les aretes
    int recipTaille = 0;
    int donneinutile;
    fiche >> recipTaille;

    fichepoids >> donneinutile;
    fichepoids >> donneinutile;
    /// La ligne du dessus lis la deuxième valeur du fichier poids
    /// Elle correspond au nombre de differents poids dans notre projet
    /// Pour ajouter un poids, il faut enlever la ligne de dessus et recoder la bonne interpretation
    /// De la ligne pour le code en dessous ( on recupère un poids en plus)

    for (int i = 0; i < recipTaille; i++)
    {
        int recipiddepart;
        int recipidarriver;
        int recipnom;

        fiche >> recipnom;
        fiche >> recipiddepart;
        fiche >> recipidarriver;

        fichepoids >> donneinutile;

        /// Si le graphe est ponderé on a une valeur de poid en plus. cf le README
        float recipPoids1 = 0, recipPoids2 = 0;
        ///int recipPoids3 = 0;
        fichepoids >> recipPoids1;
        fichepoids >> recipPoids2;

        ///fichepoids>>recipPoids3; /// C'est le poids3, mais le fichier ne le supporte pas
        /// Ligne mis exprès en commentaire, ne pas enlever

        addArete(recipnom, recipiddepart, recipidarriver, recipPoids1, recipPoids2, 0);
    }
}

void Graphe::afficherData() const
{
    cout << "Graphe :" << endl;
    cout << "Je suis d'ordre " << m_ordre << endl;
    cout << "Mes sommets :" << endl;

    for (auto &i : m_sommets)
    {
        i->afficherData();
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
Sommet Graphe::getSommetid(int nomid)
{
    if (findSommet(nomid))
        throw runtime_error("Id de sommet non trouver : graphe.cpp getSommetid");

    /// On appelle le constructeur de copie
    return Sommet(*m_sommets[nomid]);
}

void Graphe::addSommet(Sommet leclone)
{
    m_sommets.push_back(new Sommet(leclone));
    m_ordre++;
}

bool Graphe::findSommet(int nomatrouver)
{
    for(auto & i : m_sommets)
    {
        if(i->getId()==nomatrouver)
        {
            return true;
        }
    }
    return false;
}

Graphe Graphe::primMST(int nomPremier)
{
    assert(findSommet(nomPremier));
    /// Initialisation
    Graphe leprim;
    leprim.addSommet(nomPremier, m_sommets[nomPremier]->getcoordx(), m_sommets[nomPremier]->getcoordy());

    /// Variable temp
    Arete reciparete;
    Sommet recipsommet;

    do
    {
        float poidsMin = 9999; /// On met un poids infini
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
                if (poidsMin > i->getpoids1()) /// On recup l'arete au poids minimum qui est valide
                {
                    /// Remarque : le > est arbitraire
                    /// La file de priorité se code dans ce if
                    reciparete = *i;
                    poidsMin = i->getpoids1();
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
        leprim.addSommet(recipsommet.getId(), recipsommet.getcoordx(), recipsommet.getcoordy());
        leprim.addArete(reciparete.getnom(), reciparete.getdepart().getId(), reciparete.getarriver().getId(), reciparete.getpoids1(), reciparete.getpoids2(), 0);
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

void Graphe::removeSommet(int lenom, bool orienter)
{
    ///Si le sommet n'existe pas on essaye pas de l'effacer
    assert(findSommet(lenom));

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

    m_sommets.erase(m_sommets.begin() + lenom);

    m_ordre--;
}

void Graphe::removeArete(int depart, int arriver, bool orienter)
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
        ///m_aretes.erase(reciparete); Refaire cette ligne
        m_sommets[depart]->erasevoisin(arriver);
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
            ///m_aretes.erase(reciparete); Refaire cette ligne
            m_sommets[arriver]->erasevoisin(depart);
        }
    }

    /// On n'oublie pas de mettre à jours la taille du graphe
    m_taille--;
}

Graphe Graphe::dijkstraSPT(int nomPremier)
{
    assert(findSommet(nomPremier));

    Graphe ledijkstra;

    /// IMPORTANT :
    /// On considère qu'un sommet est marquée (qu'on a trouvé son plus court chemin) si il est dans le graphe ledijkstra

    map<int, pair<int, float>> distancechemins;
    /// Distance entre le depart et le sommet

    for (auto &i : m_sommets)
    {
        distancechemins.insert(make_pair(i->getId(), make_pair(0, 99999)));
    }
    /// On ajoute tout les chemins au ensemble d'information

    distancechemins.find(nomPremier)->second.second = 0;
    distancechemins.find(nomPremier)->second.first = nomPremier;
    /// Le sommet de depart a une distance nulle à lui-même

    int nomdumoment = nomPremier;
    /// Nom du sommet selectionner

    do
    {
        int poidrecip = 9999;
        for (auto &i : distancechemins)
        {
            if (i.second.second < poidrecip && !ledijkstra.findSommet(i.first))
            {
                /// Si la distance est minimale est non marquée
                nomdumoment = i.first;
                poidrecip = i.second.second;
            }
        }

        for (auto &i : m_aretes)
        {

            if (i->getdepart().getId() == nomdumoment && !ledijkstra.findSommet(i->getarriver().getId()))
            {
                /// Si l'arete par de notre sommet
                /// Et i l'arete ne va pas dans un sommet deja validé par l'algorithme
                /// On ne va pas rechecker la distance pour un sommet qui a déjà un plus court chemin
                if (i->getpoids1() + distancechemins.find(nomdumoment)->second.second < distancechemins.find(i->getarriver().getId())->second.second)
                {
                    /// Les sommets gardent toujours leur distance à l'origine
                    /// Si la distance à l'orgine + celle de la nouvelle arete est plus petite que la valeur precedente dans les données
                    /// Je vois pas trop comment traduire cette ligne, faut vraiment comprendre dijkstra
                    distancechemins.find(i->getarriver().getId())->second.first = nomdumoment;
                    distancechemins.find(i->getarriver().getId())->second.second = i->getpoids1() + distancechemins.find(nomdumoment)->second.second;
                    /// On met à jours la distance au sommet de l'indice parcouru
                }
            }

            else if (i->getarriver().getId() == nomdumoment && !ledijkstra.findSommet(i->getdepart().getId()))
            {
                if (i->getpoids1() + distancechemins.find(nomdumoment)->second.second < distancechemins.find(i->getdepart().getId())->second.second)
                {
                    distancechemins.find(i->getdepart().getId())->second.first = nomdumoment;
                    distancechemins.find(i->getdepart().getId())->second.second = i->getpoids1() + distancechemins.find(nomdumoment)->second.second;
                }
            }
        }

        poidrecip = 99999;
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
        //ledijkstra.afficherData();
        ledijkstra.addSommet(nomdumoment, m_sommets[nomdumoment]->getcoordx(), m_sommets[nomdumoment]->getcoordy());

    } while (ledijkstra.getOrdre() != m_ordre);

    cout << "Som : Pred | Dist\n";
    for (auto &i : distancechemins)
    {
        cout << i.first << " : " << i.second.first << " | " << i.second.second << endl;
    }

    /// On met à jours les arêtes

    vector<int> lespred;
    for (unsigned int i = 0; i < distancechemins.size(); i++)
    {
        lespred.push_back(0);
    }
    for (auto &i : distancechemins)
    {
        lespred[i.first] = i.second.first;
    }

    /*
    cerr << "LES PRED\n";
    for (unsigned int i = 0; i < lespred.size(); i++)
    {
        cout << i << " " << lespred[i] << endl;
    }*/

    cout << "Les chemins : \n";
    for (auto &i : distancechemins)
    {
        cout << i.first << " ";
        pred(nomPremier, i.first, lespred);
        cout << "en " << i.second.second << endl;
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
        s->dessiner(svg);
}

void Graphe::drawGraphe(BITMAP *arborescence)
{


    for (auto &s : m_aretes)
        s->draw(arborescence);
    for (auto &s : m_sommets)
        s->draw(arborescence);


}

