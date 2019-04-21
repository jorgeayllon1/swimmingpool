/// Méthode de la classe

#include "graphe.h"
#include <fstream>
#include <allegro.h>
#include <sstream>
#include <bitset>

/// Méthode permettant d'ajouter un sommet au graphe
void Graphe::addSommet(int id_sommet,int coordx, int coordy)
{
    if (!findSommet(id_sommet))
    {
        m_sommets.push_back(new Sommet(id_sommet, coordx, coordy)); // ajout du sommet au vecteur
        m_ordre++;  // incrémente le nombre de sommet
    }
    else
        cerr << "ERROR, sommet trouvé\n";
}

/// renvoi la position du sommet dans le vecteur sommet
int Graphe::indicesommet(int id_sommet) const
{
    for (unsigned int i = 0; i < m_sommets.size(); i++)
    {
        if (id_sommet == m_sommets[i]->getId())
            return i;
    }

    throw runtime_error("sommet non trouvé");
    return 0;
}

/// renvoi la position de l'arete dans le vecteur arete
int Graphe::indiceareteid(int id_arete) const
{
    for (unsigned int i = 0; i < m_aretes.size(); i++)
    {
        if (id_arete == m_aretes[i]->getnom())
            return i;
    }
    throw runtime_error("arete non trouvé");
    return 0;
}

/// renvoi l'id de l'arête
int Graphe::getAreteid(int sommet_1,int sommet_2)
{
    for (auto &i : m_aretes)
    {
        if ((i->getdepart().getId() == sommet_1 && i->getarriver().getId() == sommet_2) ||
            (i->getarriver().getId() == sommet_1 && i->getdepart().getId() == sommet_2))
            return i->getnom();
    }
    throw runtime_error("error, arete non trouve");
    return 0;
}


/// ajoute une arete dans le graphe
void Graphe::addArete(int id_arete, int sommet_1, int sommet_2, float poids1, float poids2, float poids3)
{
    /// On verifie que les sommets existent dans le graphe
    assert(findSommet(sommet_1) && findSommet(sommet_2));

    ///On ajoute l'arete au graphe, elle est definie par l'id du sommet 1, l'id du sommet 2 et son poids
    m_aretes.push_back(new Arete(id_arete, m_sommets[indicesommet(sommet_1)], m_sommets[indicesommet(sommet_2)], poids1, poids2, poids3));

    /// on ajoute les nouveaux voisins du sommet pour lequel on a ajouté une arete
    m_sommets[indicesommet(sommet_1)]->addVoisin(m_sommets[indicesommet(sommet_2)]);
    m_sommets[indicesommet(sommet_2)]->addVoisin(m_sommets[indicesommet(sommet_1)]);

    m_taille++; /// on incrémente le nombre d'arete du graphe
}

/// Constructeur du graphe
Graphe::Graphe(string nom_graphe, string nom_poids_graphe) : m_ordre(0), m_taille(0)
{
    ifstream fichier(nom_graphe);     /// lecture des fichiers
    ifstream fichier_poids(nom_poids_graphe);

    /// On verifie que le fichier existe bien
    assert(fichier);
    assert(fichier_poids);

    /// On commence par construire les sommets
    int Ordre = 0;
    fichier >> Ordre;
    for (int i = 0; i < Ordre; i++)
    {
        int id_sommet;
        int coordx;
        int coordy;

        /// Chaque sommet est defini par son id et ses coordonnées
        fichier >> id_sommet;
        fichier >> coordx;
        fichier >> coordy;
        addSommet(id_sommet, coordx, coordy);
    }

    /// Puis on construit les aretes
    int Taille = 0;
    int nb_poids = 0;
    int donneinutile;
    fichier >> Taille;

    fichier_poids >> donneinutile;  /// lecture du nombre d'arete
    fichier_poids >> nb_poids;  /// lecture du nombre de poids

    for (int i = 0; i < Taille; i++)
    {
        int sommet_1;
        int sommet_2;
        int id_arete;

        fichier >> id_arete;
        fichier >> sommet_1;
        fichier >> sommet_2;

        fichier_poids >> donneinutile;  /// lecture du numéro de l'arête

        float poids_1 = 0, poids_2 = 0, poids_3 = 0;

        fichier_poids >> poids_1;   /// lecture des poids
        fichier_poids >> poids_2;

        if (nb_poids == 3)      /// si présence d'un 3ème poids
             fichier_poids >> poids_3;

        addArete(id_arete, sommet_1, sommet_2, poids_1, poids_2, poids_3);
    }
}

/// affichage des données du graphe
void Graphe::afficherData() const
{
    std::cout << "Graphe :" <<  std::endl;
    std::cout << "Je suis d'ordre : " << m_ordre <<  std::endl;
    std::cout << "Mes sommets : " <<  std::endl;

    for (auto &i : m_sommets)
    {
        i->afficherData();
    }

    std::cout << std::endl;
    std::cout << "Je suis de taille : " << m_taille << std::endl;
    std::cout << "Mes arêtes :" << std::endl;

    for (auto &i : m_aretes)
    {
        i->afficherData();
    }
}

/// ajoute un sommet en envoyant un sommet existant
void Graphe::addSommet(Sommet clone_sommet)
{
    m_sommets.push_back(new Sommet(clone_sommet));
    m_ordre++;
}

/// Cherche une arete dans le graphe à partir de son id
bool Graphe::findArete(int id_cherche)
{
    for (auto &i : m_aretes)
    {
        if (i->getnom() == id_cherche)
            return true;
    }
    return false;
}

/// Cherche un sommet dans le graphe à partir de son id
bool Graphe::findSommet(int id_cherche)
{
    for (auto &i : m_sommets)
    {
        if (i->getId() == id_cherche)
        {
            return true;
        }
    }
    return false;
}

/// Construit un graphe selon l'algorithme de Prim
Graphe Graphe::primMST(int id_sommet_depart, int poids_choisi, int autre_poids)
{
    assert(findSommet(id_sommet_depart));   /// vérifie si le sommet existe

    /// Initialisation
    Graphe GraphePrim;

    /// ajout du sommet de départ
    GraphePrim.addSommet(id_sommet_depart, m_sommets[id_sommet_depart]->getcoordx(), m_sommets[id_sommet_depart]->getcoordy());

    /// Variable temp
    Arete reciparete;
    Sommet recipsommet;

    do
    {
        float poidsMin = 9999; /// On met un poids infini

        ///On parcours toutes les arêtes du graphe pour trouver l'arete au poids minimum
        for (auto &i : m_aretes)
        {
            /// Il faut que l'arete ait un nouveau sommet et qu'elle ne raccorde pas deux sommets déjà existants
            /// Donc il faut que le depart ou l'arrivée ne soit pas dans l'arbre
            /// Mais pas tout les deux dans l'arbre ou hors de l'arbre
            /// On utilise donc XOR
            /// On a la validité des arêtes en checkant l'arbre avec des objets du graphe(cette phrase est important mais très tricky)
            if (GraphePrim.findSommet(i->getdepart().getId()) ^ GraphePrim.findSommet(i->getarriver().getId()))
            {
                if (poidsMin > i->getpoids(poids_choisi))
                {
                    reciparete = *i;
                    poidsMin = i->getpoids(poids_choisi);
                }
            }
        }

        /// On indique le sommet manquant à l'arbre
        if (GraphePrim.findSommet(reciparete.getarriver().getId()))
        {
            recipsommet = reciparete.getdepart();
        }
        else
        {
            recipsommet = reciparete.getarriver();
        }

        /// On ajoute tout ça dans l'arbre
        GraphePrim.addSommet(recipsommet.getId(), recipsommet.getcoordx(), recipsommet.getcoordy());
        GraphePrim.addArete(reciparete.getnom(), reciparete.getdepart().getId(), reciparete.getarriver().getId(), reciparete.getpoids(0), reciparete.getpoids(1), 0);
        /// Remarque : on ne peut pas ajouter une arête avant d'ajouter le sommet
        /// Il faut que le sommet existe dans l'arbre

    } while (GraphePrim.getOrdre() != m_ordre);

    /// Tant que l'arbre n'a pas le même degré que le graphe

    float coutotprim = 0;
    float coutotautre = 0;
    for (auto &i : GraphePrim.m_aretes)
    {
        coutotprim += i->getpoids(poids_choisi);
        coutotautre += i->getpoids(autre_poids);
    }

    return GraphePrim;
}

/// Algorithme Dijkstra qui renvoie un graphe
Graphe Graphe::dijkstraSPT(int id_sommet_depart, int poids_choisi)
{
    assert(findSommet(id_sommet_depart));   /// vérifie si le sommet existe

    Graphe Graphe_Dijkstra;  /// construit un graphe vide

    /// ajoute le sommet de départ
    Graphe_Dijkstra.addSommet(id_sommet_depart, m_sommets[indicesommet(id_sommet_depart)]->getcoordx(), m_sommets[indicesommet(id_sommet_depart)]->getcoordy());
    std::unordered_set<int> valide;  /// création du conteneur de stockage
    valide.insert(id_sommet_depart);    /// insertion du premier sommet

    /// IMPORTANT : On considère qu'un sommet est marqué c'est à dire qu'on a trouvé son plus court chemin,
    /// si il est dans Graphe_Dijkstra

    /// création d'une structure de stockage pour stocker les sommets et leur distance par rapport au sommet de départ et le précédent
    std::map<int, pair<int, float>> distancechemins;

    /// On initialise la structure pour tous les sommets
    for (auto &i : m_sommets)
    {
        distancechemins.insert(make_pair(i->getId(), make_pair(0, 99999)));
    }

    /// On ajoute tous les chemins au ensemble d'information
    distancechemins.find(id_sommet_depart)->second.second = 0;  /// Le sommet de depart a une distance nulle à lui-même
    distancechemins.find(id_sommet_depart)->second.first = id_sommet_depart;

    int id_sommet_en_cours = id_sommet_depart;

    do
    {
        int poids_en_cours = 9999;  /// initialisation au poids le plus fort

        for (auto &i : m_aretes)
        {
            if (i->getdepart().getId() == id_sommet_en_cours && !Graphe_Dijkstra.findSommet(i->getarriver().getId()))
            {
                /// Si l'arete par de notre sommet
                /// Et i l'arete ne va pas dans un sommet deja validé par l'algorithme
                /// On ne va pas rechecker la distance pour un sommet qui a déjà un plus court chemin
                if (i->getpoids(poids_choisi) + distancechemins.find(id_sommet_en_cours)->second.second < distancechemins.find(i->getarriver().getId())->second.second)
                {
                    /// Les sommets gardent toujours leur distance à l'origine
                    /// Si la distance à l'orgine + celle de la nouvelle arete est plus petite que la valeur precedente dans les données
                    /// Je vois pas trop comment traduire cette ligne, faut vraiment comprendre dijkstra
                    distancechemins.find(i->getarriver().getId())->second.first = id_sommet_en_cours;
                    distancechemins.find(i->getarriver().getId())->second.second = i->getpoids(poids_choisi) + distancechemins.find(id_sommet_en_cours)->second.second;
                    /// On met à jours la distance au sommet de l'indice parcouru
                }
            }

            else if (i->getarriver().getId() == id_sommet_en_cours && !Graphe_Dijkstra.findSommet(i->getdepart().getId()))
            {
                if (i->getpoids(poids_choisi) + distancechemins.find(id_sommet_en_cours)->second.second < distancechemins.find(i->getdepart().getId())->second.second)
                {
                    distancechemins.find(i->getdepart().getId())->second.first = id_sommet_en_cours;
                    distancechemins.find(i->getdepart().getId())->second.second = i->getpoids(poids_choisi) + distancechemins.find(id_sommet_en_cours)->second.second;
                }
            }
        }

        poids_en_cours = 99999;
        /// On cherche la distance minimale non déjà validée

        for (auto &i : distancechemins)
        {
            if (i.second.second < poids_en_cours && !Graphe_Dijkstra.findSommet(i.first))
            {
                /// Si la distance est minimale est non marquée
                id_sommet_en_cours = i.first;
                poids_en_cours = i.second.second;
            }
        }

        ///id_sommet_en_cours devient le sommet de refference et on le marque
        //Graphe_Dijkstra.afficherData();
        Graphe_Dijkstra.addSommet(id_sommet_en_cours, m_sommets[indicesommet(id_sommet_en_cours)]->getcoordx(), m_sommets[indicesommet(id_sommet_en_cours)]->getcoordy());
        int nomdelarete = getAreteid(id_sommet_en_cours, distancechemins.find(id_sommet_en_cours)->second.first);
        Graphe_Dijkstra.addArete(nomdelarete, id_sommet_en_cours, distancechemins.find(id_sommet_en_cours)->second.first, m_aretes[indiceareteid(nomdelarete)]->getpoids(0), m_aretes[indiceareteid(nomdelarete)]->getpoids(1), m_aretes[indiceareteid(nomdelarete)]->getpoids(2));
    } while (Graphe_Dijkstra.getOrdre() != m_ordre);

    /// On met à jours les arêtes
    /*
    cout << "Som : Pred | Dist\n";
    for (auto &i : distancechemins)
    {
        cout << i.first << " : " << i.second.first << " | " << i.second.second << endl;
    }*/

    vector<int> lespred;
    for (unsigned int i = 0; i < distancechemins.size(); i++)
    {
        lespred.push_back(0);
    }
    for (auto &i : distancechemins)
    {
        lespred[i.first] = i.second.first;
    }
    return Graphe_Dijkstra;
}


float Graphe::dijkstraSPT(int id_sommet_depart, int poids_choisi, bool affichage)
{
    assert(findSommet(id_sommet_depart));

    //Graphe Graphe_Dijkstra;
    //Graphe_Dijkstra.addSommet(nomPremier,getSommetid(nomPremier).getcoordx(),getSommetid(nomPremier).getcoordy());
    //Graphe_Dijkstra.addSommet(nomPremier, m_sommets[indicesommet(nomPremier)]->getcoordx(), m_sommets[indicesommet(nomPremier)]->getcoordy());
    unordered_set<int> valide;
    valide.insert(id_sommet_depart);

    /// IMPORTANT :
    /// On considère qu'un sommet est marquée (qu'on a trouvé son plus court chemin) si il est dans le graphe Graphe_Dijkstra

    map<int, pair<int, float>> distancechemins;
    /// Distance entre le depart et le sommet

    for (auto &i : m_sommets)
    {
        distancechemins.insert(make_pair(i->getId(), make_pair(0, 99999)));
    }
    /// On ajoute tout les chemins au ensemble d'information

    distancechemins.find(id_sommet_depart)->second.second = 0;
    distancechemins.find(id_sommet_depart)->second.first = id_sommet_depart;
    /// Le sommet de depart a une distance nulle à lui-même

    int id_sommet_en_cours = id_sommet_depart;
    /// Nom du sommet selectionner

    do
    {
        int poids_en_cours = 9999;

        for (auto &i : m_aretes)
        {

            if (i->getdepart().getId() == id_sommet_en_cours && valide.find(i->getarriver().getId()) == valide.end())
            {
                /// Si l'arete par de notre sommet
                /// Et i l'arete ne va pas dans un sommet deja validé par l'algorithme
                /// On ne va pas rechecker la distance pour un sommet qui a déjà un plus court chemin
                if (i->getpoids(poids_choisi) + distancechemins.find(id_sommet_en_cours)->second.second < distancechemins.find(i->getarriver().getId())->second.second)
                {
                    /// Les sommets gardent toujours leur distance à l'origine
                    /// Si la distance à l'orgine + celle de la nouvelle arete est plus petite que la valeur precedente dans les données
                    /// Je vois pas trop comment traduire cette ligne, faut vraiment comprendre dijkstra
                    distancechemins.find(i->getarriver().getId())->second.first = id_sommet_en_cours;
                    distancechemins.find(i->getarriver().getId())->second.second = i->getpoids(poids_choisi) + distancechemins.find(id_sommet_en_cours)->second.second;
                    /// On met à jours la distance au sommet de l'indice parcouru
                }
            }

            else if (i->getarriver().getId() == id_sommet_en_cours && valide.find(i->getdepart().getId()) == valide.end())
            {
                if (i->getpoids(poids_choisi) + distancechemins.find(id_sommet_en_cours)->second.second < distancechemins.find(i->getdepart().getId())->second.second)
                {
                    distancechemins.find(i->getdepart().getId())->second.first = id_sommet_en_cours;
                    distancechemins.find(i->getdepart().getId())->second.second = i->getpoids(poids_choisi) + distancechemins.find(id_sommet_en_cours)->second.second;
                }
            }
        }

        poids_en_cours = 99999; /// initialisation au poids le plus fort

        /// On cherche la distance minimale non déjà validée
        for (auto &i : distancechemins)
        {
            if (i.second.second < poids_en_cours && valide.find(i.first) == valide.end())
            {
                /// Si la distance est minimale est non marquée
                id_sommet_en_cours = i.first;
                poids_en_cours = i.second.second;
            }
        }

        ///id_sommet_en_cours devient le sommet de refference et on le marque
        //Graphe_Dijkstra.afficherData();
        //Graphe_Dijkstra.addSommet(id_sommet_en_cours, m_sommets[indicesommet(id_sommet_en_cours)]->getcoordx(), m_sommets[indicesommet(id_sommet_en_cours)]->getcoordy());
        //int nomdelarete = getAreteid(id_sommet_en_cours, distancechemins.find(id_sommet_en_cours)->second.first);
        //Graphe_Dijkstra.addArete(nomdelarete, id_sommet_en_cours, distancechemins.find(id_sommet_en_cours)->second.first, m_aretes[indiceareteid(nomdelarete)]->getpoids(0), m_aretes[indiceareteid(nomdelarete)]->getpoids(1), m_aretes[indiceareteid(nomdelarete)]->getpoids(2));
        valide.insert(id_sommet_en_cours);

    } while (valide.size() != unsigned(m_ordre));
/*
    cout << "Som : Pred | Dist\n";
    for (auto &i : distancechemins)
    {
        cout << i.first << " : " << i.second.first << " | " << i.second.second << endl;
    }
*/
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

    float lecoutot = 0;

    for (auto &i : distancechemins)
    {
        lecoutot += i.second.second;
    }
    return lecoutot;
}


/// algorithme de tri
bool sortbydegre(const Sommet *a, const Sommet *b)
{
    return (a->getdegre() > b->getdegre());
}

/// Théorème de Welshpowel
int Graphe::welshpowel()
{
    int nbdecoul = 0;

    list<Sommet *> laliste;
    int pluspetitecouleur = 1;
    Sommet *recipsommet;
    /// Attention, laliste controle le graphe generale
    /// Il a accé au pointeur
    for (auto &i : m_sommets)
    {
        laliste.push_back(i);
    }

    laliste.sort(sortbydegre);

    bool sommetnoncol = false;
    do
    {
        sommetnoncol = false;
        for (list<Sommet *>::iterator it = laliste.begin(); it != laliste.end(); ++it)
        {
            if ((*it)->getcouleur() == 0)
            {
                (*it)->setcouleur(pluspetitecouleur);
                recipsommet = (*it);
                break;
            }
        }

        for (list<Sommet *>::iterator it = find(laliste.begin(), laliste.end(), recipsommet); it != laliste.end(); ++it)
        {
            if (*it == recipsommet)
                continue;
            /// Si il est non colorié
            if ((*it)->getcouleur() == 0 && !(*it)->adjacentdejacolorier(pluspetitecouleur))
            {
                /// Si il est pas adjacent a un truc deja colorier
                (*it)->setcouleur(pluspetitecouleur);
            }
        }

        for (auto &i : laliste)
        {
            if (i->getcouleur() == 0)
            {
                sommetnoncol = true;
                pluspetitecouleur++;
                break;
            }
        }

    } while (sommetnoncol == true);

    nbdecoul = pluspetitecouleur;

    return nbdecoul;
}


/// Destructeur
Graphe::~Graphe()
{

    /// on appelle delete sur chaque element
    for (auto &i : m_aretes)
    {
        delete i;
    }
    m_aretes.clear();

    for (auto &i : m_sommets)
    {
        if (i)
            delete i;
    }
    m_sommets.clear();
    m_ordre = 0;
    m_taille = 0;
}

///CONNEXE
/// Déclaration de la méthode check de la classe Graph.
/// Cette méthode vérifie si chaque sommet a au moins un voisin
bool Graphe::check()
{
    for (auto &i : m_sommets)   /// on parcoure tous les sommets du graphe
    {
        if (i->getdegre() == 0)
            return false;
    }
    return true;
}

/// converti un binaire en graphe
Graphe Graphe::Conversion(std::vector<bool> Binaire)
{
    Graphe Tampon;
    for (int k = 0; k < m_ordre; k++)
    {
        Tampon.addSommet(k, m_sommets[k]->getcoordx(), m_sommets[k]->getcoordy());
    }
    for (auto &s : m_aretes)
    {

        if (Binaire[s->getnom()])
        {
            Tampon.addArete(s->getnom(), s->getdepart().getId(), s->getarriver().getId(), s->getpoids(0), s->getpoids(1), 0.0);
        }
    }
    return Tampon;
}

/// Récupère la somme des poids d'un graphe
pair<float, float> Graphe::DonnePoids()
{
    pair<float, float> total;
    for (auto &a : m_aretes)
    {
        (total.first) += a->getpoids(0);
        (total.second) += a->getpoids(1);
    }
    return total;
}


vector<pair<float, float>> Graphe::Pareto(vector<pair<float, float>> &total, std::vector<std::pair<float, float>> *nonPareto,std::vector<vector<bool>> G)
{

    //pair<float,float> limite = primMST(0,0,1);
    //cout << "litme :" << limite.first << "et" << limite.second << endl;
    //pair<float,float> limite = primMST(0,0,0).DonnePoids();
    nonPareto->clear();
    vector<pair<float, float>> pareto;
    vector<pair<float, float>> buffer = total;
    std::vector<vector<bool>> F;

    pareto.push_back(make_pair(0, 0));
    //bool test = true;
    sort(total.begin(), total.end(), sortbyCout1);

    float maxCout2 = 99999999;

    for (auto &l : total)
    {

        if (l.second < maxCout2)
        {
            if (l.first == pareto.back().first)
                pareto.pop_back();

            pareto.push_back(make_pair(l.first, l.second));
            maxCout2 = l.second;
        }
        else
            nonPareto->push_back(make_pair(l.first, l.second));
    }

    pareto.erase(pareto.begin());

    for(unsigned int i=0; i<buffer.size();i++)
    {
        for(unsigned int u=0; u<pareto.size();u++)
        {
           if(buffer[i]==pareto[u])
           {
//              vector<bool> alert;
//              for(int z=0; z < (G[i]).size();z++)
//              alert.push_back.(G([i][z]));
              F.push_back(G[i]);
           }
        }
    }

    G.clear();
    G = F;

    for (auto &l : pareto)
        cout << "pareto :" << l.first << "et" << l.second << endl;
    total.clear();

    return pareto;
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

void Graphe::drawSousGraphe(BITMAP *arborescence)
{
    for (auto &s : m_aretes)
        s->drawS(arborescence);
}

void Graphe::drawGraphe(BITMAP *arborescence)
{

    for (auto &s : m_aretes)
        s->draw(arborescence);
    for (auto &s : m_sommets)
        s->draw(arborescence);
}

/// Détermine tous les sous-graphes à partir d'un graphe d'origine et conserve les graphes admissibles pour Pareto
vector<vector<bool>> Graphe::calcul_sousgraphes_admissibles(vector<pair<float, float>> *total, bool cycle)
{
    unsigned int nb_cas = pow(2, m_taille); /// nb de cas possible de position des arêtes
    vector<vector<bool>> mes_sous_graphes;  /// création de structure de sous-graphes


    for (unsigned int i = 0; i < nb_cas; i++)
    {
        vector<bool> etat_des_aretes;    /// création d'un vecteur booléen contenant les états des arêtes (présente ou absente)
        std::bitset<16> conversion_binaire {i}; /// Converti en binaire l'index en cours

        /// Chargement des états arete dans la variable binaire
        for(int j = 0 ; j<m_taille;j++)
        {
            etat_des_aretes.push_back(conversion_binaire[conversion_binaire.size()+j]);
        }
        unsigned int nb_arretes = conversion_binaire.count();
        unsigned int nb_sommet = m_sommets.size();

        if ((nb_arretes == (nb_sommet - 1) && !(cycle)) || (nb_arretes >= (nb_sommet - 1) && cycle))
        {
            Graphe Tampon;
            for (int k = 0; k < m_ordre; k++)
            {
                Tampon.addSommet(k, m_sommets[k]->getcoordx(), m_sommets[k]->getcoordy());
            }
            float poids[3] = {0,0,0};

            for (auto &s : m_aretes)
            {
                if (etat_des_aretes[s->getnom()])
                {
                    poids[0] += s->getpoids(0);
                    if (!cycle)
                        poids[1] += s->getpoids(1);
                    Tampon.addArete(s->getnom(), s->getdepart().getId(), s->getarriver().getId(), s->getpoids(0), s->getpoids(1), 0.0);
                }
            }
            if (Tampon.check())
            {
                if (Tampon.test_connexite())
                {
                    if (cycle)
                    {
                        poids[1] = Tampon.Temps_Parcours();
                    }
                    mes_sous_graphes.push_back(etat_des_aretes);
                    total->push_back(make_pair(poids[0], poids[1]));
                }
            }
            (etat_des_aretes).erase(etat_des_aretes.begin(), etat_des_aretes.end());
        }
    }
    return mes_sous_graphes;
}

bool Graphe::test_connexite()
{
    std::unordered_set<int> cc;
    cc = m_sommets[0]->parcoursBFS();
    if (cc.size() == (unsigned)m_ordre)
        return true;
    else
        return false;
}

int Graphe::Temps_Parcours()
{
    int s = 0;
    for (int k = 0; k < m_ordre; k++)
    {
        s += dijkstraSPT(k, 1, false);
    }
    return s;
}
