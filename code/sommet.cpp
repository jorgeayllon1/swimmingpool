#include "sommet.h"
#include <random>
#include <queue>

using namespace std;

void Sommet::afficherData() const
{
    cout << "Mon id est " << m_id << endl
         << "Je suis de couleur : " << m_couleur << endl
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

Sommet::~Sommet()
{
    /*
    for (auto &i : m_voisins)
    {
        if (i)
            erasevoisin(i->getId());
    }*/
    m_voisins.clear();
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
        sort(m_voisins.begin(), m_voisins.end());
        m_degre++;
    }
    else
        throw runtime_error("Error tu ajoutes un voisin qui n'existe pas\n");
}

Sommet::Sommet(Sommet const &copie) : m_id(copie.m_id), m_couleur(copie.m_couleur),
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
    /*
    Sommet *recip = NULL;

    /// On cherche le voisin a enlever
    /// On evite de faire find car on prefere passer par les string des sommets
    /// Plutot que d'utiliser les pointeurs
    /// C'est plus securisé pour la memoire
    for (auto &i : m_voisins)
    {

        recip = i;
        break;
    }
    if (recip)
    {
        m_voisins.erase(m_voisins.begin() + recip->m_id);
        m_degre--;
    }
    */
    for (auto &i : m_voisins)
    {
        i = NULL;
    }
}
/*
std::unordered_map<int,int> Sommet::parcoursBFS() {

    std::unordered_map<int,int> l_pred;
    ///création d'un unordered_map pour stocker tout les sommmets , afin d'eviter de les redecouvrir par la suite
    std::unordered_map<int,Sommet*> sommets_decouverts;
    std::queue <Sommet*> file; ///création de la file de sommets
    file.push(this);///envoie du sommet de depart en debut de file

    while (file.size()!=0)///tant que la file n'est pas vide
    {       Sommet*S1 = file.front();///definition de sommet S1 comme etant le premier sommet de la file
           sommets_decouverts[S1->m_id]=file.front();///stockage de S1 dans sommets_decouverts

           ///Boucle for pour stocker les voisins
           for (unsigned int i = 0 ; i < S1->m_voisins.size();i++)
           {
                ///condition pour savoir si un sommet à déja été decouvert
                if(sommets_decouverts.find(S1->m_voisins[i]->m_id)== sommets_decouverts.end())
                {
                    file.push(S1->m_voisins[i]);///stockage du nouveau sommet decouvert dans la file
                    sommets_decouverts [S1->m_voisins[i]->m_id]= S1->m_voisins[i];///stockage du nouveau sommmet dans sommets_decouverts
                    l_pred[S1->m_voisins[i]->m_id]=S1->m_id;///stockage du nouveau sommet et de son predécesseur dans l_pred
                }
           }
           file.pop();///suppression du premier sommet de la file pour passer au suivant
    }
    return l_pred;///on retourne l'unordered_map l_pred
}
*/

void Sommet::dessiner(Svgfile &svg)
{
    svg.addDisk(m_coordx, m_coordy, 5, "black");
}

void Sommet::draw(BITMAP *arbo)
{
    FONT *myfont;

        int lacoul = 0;
    switch (m_couleur)
    {
    case 1:
        lacoul = makecol(241, 144, 102);
        break;
    case 2:
        lacoul = makecol(245, 205, 121);
        break;
    case 3:
        lacoul = makecol(84, 109, 229);
        break;
    case 4:
        lacoul = makecol(196, 69, 105);
        break;
    case 5:
        lacoul = makecol(248, 165, 194);
        break;
    case 6:
        lacoul = makecol(120, 111, 166);
        break;
    case 7:
        lacoul = makecol(247, 241, 227);
        break;
    default:
        lacoul = makecol(200, m_couleur*40, m_couleur*40);
        break;
    }

    myfont = load_font("image/fontComic16.pcx", NULL, NULL);
    if (!myfont)
    {
        allegro_message("prb allocation FONT myfont");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    string texte = NumberToString(m_id);
    const char *cstr = texte.c_str();
    //circle(arbo, m_coordx, m_coordy, 15, makecol(10, 61, 98));
    circlefill(arbo, m_coordx, m_coordy, 13, lacoul);
    textprintf_centre_ex(arbo, myfont, m_coordx, m_coordy - 12, makecol(10, 61, 98), -1, cstr);
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

std::unordered_set<int> Sommet::parcoursBFS()
{

    //std::unordered_map<int,int> l_pred;
    ///création d'un unordered_map pour stocker tout les sommmets , afin d'eviter de les redecouvrir par la suite
    std::unordered_map<int, Sommet *> sommets_decouverts;
    std::unordered_set<int> sommets;
    std::queue<Sommet *> file; ///création de la file de sommets
    file.push(this);           ///envoie du sommet de depart en debut de file

    while (file.size() != 0) ///tant que la file n'est pas vide
    {
        Sommet *S1 = file.front();                   ///definition de sommet S1 comme etant le premier sommet de la file
        sommets_decouverts[S1->m_id] = file.front(); ///stockage de S1 dans sommets_decouverts
        sommets.insert(S1->m_id);
        ///Boucle for pour stocker les voisins
        for (unsigned int i = 0; i < S1->m_voisins.size(); i++)
        {
            ///condition pour savoir si un sommet à déja été decouvert
            if (sommets_decouverts.find(S1->m_voisins[i]->m_id) == sommets_decouverts.end())
            {
                file.push(S1->m_voisins[i]);                                   ///stockage du nouveau sommet decouvert dans la file
                sommets_decouverts[S1->m_voisins[i]->m_id] = S1->m_voisins[i]; ///stockage du nouveau sommmet dans sommets_decouverts
                //l_pred[S1->m_voisins[i]->m_id]=S1->m_id;///stockage du nouveau sommet et de son predécesseur dans l_pred
            }
        }
        file.pop(); ///suppression du premier sommet de la file pour passer au suivant
    }
    //std::unordered_set<int> sommets = sommets_decouverts.first;
    return sommets; ///on retourne l'unordered_map l_pred
}

/// Welsh powel

bool Sommet::adjacentdejacolorier(int couleur)
{
    bool dejavoisinscolorier = false;
    for (auto &i : m_voisins)
    {
        if (i->getcouleur() == couleur)
        {
            dejavoisinscolorier = true;
            break;
        }
    }
    return dejavoisinscolorier;
}
