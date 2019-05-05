#ifndef ARETE_H

#define ARETE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#include "svgfile.h"
#include "sommet.h"

class Arete//class arete
{
public:
    Arete(int name, int s1, int s2, float p1,float p2, std::string c, int num, int etat,int etatd);//constructeur
    void afficher() const;//afficher en console
    int GetS1();//getters
    int GetS2();
    int GetName();
    std::string GetColor();
    std::string SetColor(std::string couleur);
    float GetP1();
    float SetP1(float p1);
    float GetP2();
    float SetP2(float p2);
    int GetNum();
    int SetNum(int num);
    int GetEtat();
    int SetEtat(int etat);
    int GetEtatd();
    int SetEtatd(int etatd);
    virtual ~Arete();//destructeur
    void dessinerArete(Svgfile& svgout, std::vector<Sommet*>som);//dessin
    void dessinerAreteP1(Svgfile& svgout, std::vector<Sommet*>som);//dessine les poids 1
    void dessinerAreteP2(Svgfile& svgout, std::vector<Sommet*>som);//dessine les poids 2

protected:
    int m_name;                // numero arete
    int m_sommet1;             // sommet de départ
    int m_sommet2;             // sommet d'arrive
    float m_poids1;            // poids 1
    float m_poids2;            // poids 2
    std::string m_c = "black"; // couleur (important pour svgfile)
    int m_num; //etat pour prim
    int m_etat; //etat pour pareto
    int m_etatd; //etat pour dijkstra

};
void remplirAretes(std::vector<Arete*>& monTableau,std::string f1,std::string f2);//rempli aretes
void afficherAretes(std::vector<Arete*>& monTableau);//affiche arete
std::vector<Arete*> trierAretesPoids1(std::vector<Arete*> monTableau);//trie
std::vector<Arete*> trierAretesPoids2(std::vector<Arete*> monTableau);//tri
float Poids1_Total(std::vector<Arete*> monTableau);//somme des poids1
float Poids2_Total(std::vector<Arete*> monTableau);//somme des poids2

#endif // ARETE_H
