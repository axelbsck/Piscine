#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <vector>
#include "svgfile.h"
#include "sommet.h"
#include "arete.h"

class Graphe
{
    public:
        Graphe(std::vector<Arete*> arete, float poids1_total, float poids2_total);
        ~Graphe();
        std::vector<Arete*> GetArete();
        float GetPt1();
        float GetPt2();
        float SetPt2(float Poids2_Total);
        void dessinerGraphe(Svgfile& svgout, std::vector<Sommet*>Som, std::vector<Arete*>Ar);//dessin du graphe
        void prim1(Svgfile& svgout, std::vector<Sommet*>vecS,std::vector<Arete*>vecA);//prim1
        void prim2(Svgfile& svgout, std::vector<Sommet*>vecS,std::vector<Arete*>vecA);//prim2

    protected:
        std::vector<Arete*>m_arete;//tableau d'aretes
        float m_poids1Total;//poids1
        float m_poids2Total;//poids 2

};

std::vector<Graphe*> trierPoids1Total(std::vector<Graphe*>monTableau);//tri des poids tot
void AfficherGraphe(Svgfile& svgout, std::vector<Graphe*>g);//affiche le graphe
void AfficherGrapheTout(Svgfile& svgout, std::vector<Graphe*>g);//affiche tout le graphe
std::vector<Graphe*> Pareto_tri(std::vector<Graphe*> graphe_trier);//tri pour pareto
std::vector<Graphe*> Pareto(std::vector<Arete*> vecA, std::vector<Sommet*> vecS);//pareto partie 2
std::vector<Graphe*> Pareto2(std::vector<Arete*> vecA, std::vector<Sommet*> vecS);//pareto partie 3
std::vector<Graphe*> initialisation_Pareto(std::vector<Graphe*> graphe_trier);

#endif // GRAPHE_H

