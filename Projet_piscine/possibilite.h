#ifndef POSSIBILITE_H

#define POSSIBILITE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#include "svgfile.h"
#include "possibilite.h"
#include "arete.h"
#include "sommet.h"

class Possibilite
{
public:
    Possibilite(int som, int pred, float poids, int etat);//constructeur
    void afficher() const;//affichage
    int GetSom();//getters
    int GetPred();
    float GetPoids();
    int GetEtat();
    int SetSom(int som);
    int SetPred(int pred);
    float SetPoids(float poids);
    int SetEtat(int etat);
    virtual ~Possibilite();//destructeur
    //void dijkstra(std::vector<Arete*>vecA, std::vector<Sommet*>vecS, int Sd, int Sa);

protected:
    int m_som;                // numero arete
    int m_pred;             // sommet de départ
    float m_poids;          //poids
    int m_etat;             // sommet d'arrive

};

std::vector<Possibilite*> trierPossibilitePoids(std::vector<Possibilite*> monTableau);//tri les possibilités
float dijkstra(std::vector<Arete*>vecA, int Sd, int Sa);//dijkstra

#endif // POSSIBILITE_H
