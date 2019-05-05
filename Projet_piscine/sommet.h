#ifndef SOMMET_H
#define SOMMET_H

#include "iostream"
#include <vector>
#include <fstream>

#include "svgfile.h"

/** \class Sommet sommet.h "inc/sommet.h" */
class Sommet //class sommet
{
public:
    Sommet(float x, float y, int id, int val, int etat);//constructeur
    virtual ~Sommet();//destructeur
    void dessinerSommet(Svgfile& svgout);//dessiner les sommets
    void afficher() const;//afficher en console
    ///getters et setters
    float GetX();
    float GetY();
    int GetId();
    int GetVal();
    int SetVal(int val);
    int GetEtat();
    int SetEtat(int etat);
private:
    int m_id; //id
    float m_x; //coordonnée en x
    float m_y; //coordonnée en y
    int m_val; //valeur pour prim
    int m_etat; //etat
};

void remplirSommets(std::vector<Sommet*>& monTableau,  std::string filename);//rempli les sommets
void afficherSommets(Svgfile& svgout, std::vector<Sommet*>& monTableau);//rempli les sommets



#endif // SOMMETS_H

