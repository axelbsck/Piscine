#include "sommet.h"
/**
 * \file          sommet.cpp
 * \author        Miroslav
 * \version        1.0
 * \date       16 Avril 2019
 * \brief       Definit les sommets
 *
 * \details    Ce fichier definit les différentes fonctions de sommets
 */
Sommet::Sommet(float x, float y, int id, int val, int etat) : m_x(x), m_y(y), m_id(id), m_val(val),m_etat(etat)
{}

Sommet::~Sommet()
{
    //dtor
}

int Sommet::GetId()
{
    return m_id;
}

float Sommet::GetX()
{
   return m_x;
}

float Sommet::GetY()
{
    return m_y;
}

int Sommet::GetVal()
{
    return m_val;
}

int Sommet::SetVal(int val)
{
    m_val = val;
    return m_val;
}

int Sommet::GetEtat()
{
    return m_etat;
}

int Sommet::SetEtat(int etat)
{
    m_etat = etat;
    return m_etat;
}

/**
 * \brief       Dessine les sommets dans le fichier svg
 * \details    Grace à addDisk et addText on va pouvoir dessiner les sommets
 *              ainsi que leur numéro dans le fichier svg
 * \param    svgout
 */
void Sommet::dessinerSommet(Svgfile& svgout)
{
    svgout.addDisk(m_x, m_y, 20, "blue");
    svgout.addText(m_x, m_y,m_id,"white");
}

/**
 * \brief       Remplit les sommets dans le vecteur de sommets
 * \details    Lecture des informations contenues dans le fichier
 * \param    monTableau     vecteur de pointeurs de sommets
 * \param    filename       fichier qu'on veut lire
 */
void remplirSommets(std::vector<Sommet*>& monTableau, std::string filename)
{
    int i,taille,temp,id;//info à récupérer
    float x,y;
    std::ifstream ifs{filename};
    if (!ifs)//si le fichier n'éxiste pas
        throw std::runtime_error( "Impossible d'ouvrir en lecture ");
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    for (int i=0; i<taille; ++i){
        ifs>>id;
        if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>x;
        if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifs>>y;
        if(ifs.fail()) throw std::runtime_error("Probleme lecture données sommet");
        monTableau.push_back(new Sommet{x,y,id,1,0});
    }

}

/**
 * \brief       Affiche les sommets
 * \details     Affiche le numéro du sommet, son abscisse et son ordonnee sur console
 */
void Sommet::afficher() const//affichage
{
    std::cout << "L'IDENTIFIANT: "<< m_id << "L'ABSCISSE: " << m_x << " L'ORDONNEE: " << m_y << " VALEUR: " << m_val << std::endl;
}

/**
 * \brief       Affiche les sommets
 * \details     Affiche les sommets sur le fichier svg en parcourant monTableau
 * \param    monTableau     vecteur de pointeurs de sommets
 * \param    svgout       fichier Svg
 */
void afficherSommets(Svgfile& svgout, std::vector<Sommet*>& monTableau)//affichage des sommets en console
{
    for (size_t i=0 ; i< monTableau.size() ; i++)
    {
        monTableau[i]->afficher();
    }
}
