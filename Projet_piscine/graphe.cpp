#include "graphe.h"
#include "transformation.h"
#include "couleur.h"
#include "svgfile.h"
#include "utile.h"
#include "arete.h"
#include "sommet.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

Graphe::Graphe(std::vector<Arete*> arete, float poids1_total, float poids2_total) :
    m_arete(arete), m_poids1Total(poids1_total), m_poids2Total(poids2_total) ///constructeur
{

}

Graphe::~Graphe() ///destructeur
{

}

void Graphe::dessinerGraphe(Svgfile& svgout, std::vector<Sommet*>vecS, std::vector<Arete*>vecA)///dessine le graphe
{

    for(int t=0; t<vecA.size(); t++)//dessin des aretes
    {
        vecA[t]->dessinerArete(svgout, vecS);
    }

    for (int z=0 ; z<vecS.size() ; z++)//dessin des sommets
    {
        vecS[z]->dessinerSommet(svgout);
    }

}

void Graphe::prim1(Svgfile& svgout, std::vector<Sommet*>vecS,std::vector<Arete*>vecA)///fonction qui fait Prim pour le poids 1
{
    int compteur = 1;
    int couttot = 0;
    int i=0; //attention il s'agit du numéro du sommet et non de la case du tableau
    std::vector<Arete*>areteatrier;
    std::vector<Arete*>areteTrier;
    std::vector<Arete*>areteaffichage;
    int s1, s2;


    while(compteur<vecS.size())
    {
        vecS[i]->SetVal(0); //à condition que la case i corresponde au sommet i
        int k=0;

        for(unsigned int j=0; j<vecA.size(); j++)//recupère les bonnes arêtes
        {
            if(vecA[j]->GetNum() != 1)
            {
                if(vecA[j]->GetS1() == vecS[i]->GetId() || vecA[j]->GetS2() == vecS[i]->GetId())
                {
                    areteatrier.push_back(new Arete{vecA[j]->GetName(),vecA[j]->GetS1(),vecA[j]->GetS2(),vecA[j]->GetP1(),vecA[j]->GetP2(),vecA[j]->GetColor(),1, 0, 0});
                    vecA[j]->SetNum(1);//pour ne pas réutiliser l'arete
                }

                else
                {
                    //rien
                }
            }

        }
        ///étape comparer les arêtes du tableau d'arêtes découvertes

        areteTrier = trierAretesPoids1(areteatrier);


        ///couleur de la plus petite arête = vert (l'arête de la case 1)

        s1=areteTrier[k]->GetS1();
        s2=areteTrier[k]->GetS2();

        while(vecS[s1]->GetVal() == vecS[s2]->GetVal())
        {
            k=k+1;
            s1=areteTrier[k]->GetS1();
            s2=areteTrier[k]->GetS2();
        }


        areteTrier[k]->SetColor("green");

        //afficherAretes(areteTrier);

        areteaffichage.push_back(new Arete{areteTrier[k]->GetName(),areteTrier[k]->GetS1(),areteTrier[k]->GetS2(),areteTrier[k]->GetP1(),areteTrier[k]->GetP2(),areteTrier[k]->GetColor(), areteTrier[k]->GetNum(), areteTrier[k]->GetEtat(),areteTrier[k]->GetEtatd()});


        if(vecS[areteTrier[k]->GetS1()]->GetVal()==0)//evite de reprendre une arête déjà utilisée
        {
            i=areteTrier[k]->GetS2();

        }
        else if(vecS[areteTrier[k]->GetS1()]->GetVal()==1)
        {
            i=areteTrier[k]->GetS1();//nouvelle valeur de i

        }

        for(int e=0; e<vecA.size(); e++)
        {
            if(vecA[e]->GetName()==areteTrier[k]->GetName())
            {
                vecA.erase(vecA.begin()+e);//suppression du vecteur
            }
        }

        for(int e=0; e<areteatrier.size(); e++)
        {
            if(areteatrier[e]->GetName()==areteTrier[k]->GetName())//on récupère le nom de l'arete
            {
                areteatrier.erase(areteatrier.begin()+e);//supprime l'arete
            }
        }

        compteur = compteur + 1;//on augmente le compteur
        k=0;
        areteTrier.clear();//on supprime les valeurs du tableau
    }


///affichage console

    std::cout<<""<<std::endl;

    for(int i=0; i<areteaffichage.size(); i++) //tableau des étapes
    {
        std::cout<<"Etape   "<<i<<"   Arrete   "<<areteaffichage[i]->GetName()<<"   Sommet 1   "<<areteaffichage[i]->GetS1()<<"   Sommet 2   "<<areteaffichage[i]->GetS2()<< "   Poids 1   "<<areteaffichage[i]->GetP1()<<std::endl;
    }

///cout total

    std::cout<<""<<std::endl;

    for(int i=0; i<areteaffichage.size(); i++)
    {
        couttot = couttot + areteaffichage[i]->GetP1();//donne le cout total
    }
    std::cout<<"Le cout total est de "<<couttot<<std::endl;
    std::cout<<""<<std::endl;


///affichage svg

///aretes
    for(int t=0; t<areteaffichage.size(); t++)
    {
        areteaffichage[t]->dessinerAreteP1(svgout, vecS);//affichage des arêtes
    }

///sommets
    for (int z=0 ; z<vecS.size() ; z++)///affichage
    {
        vecS[z]->dessinerSommet(svgout);//affichage des sommets
    }
}



void Graphe::prim2(Svgfile& svgout, std::vector<Sommet*>vecS,std::vector<Arete*>vecA)
{
    int compteur = 1;
    int couttot = 0;
    int i=0; //attention il s'agit du numéro du sommet et non de la case du tableau
    std::vector<Arete*>areteatrier;
    std::vector<Arete*>areteTrier;
    std::vector<Arete*>areteaffichage;
    int s1, s2;


    while(compteur<vecS.size())
    {
        vecS[i]->SetVal(0); //à condition que la case i corresponde au sommet i
        int k=0;
        //std::cout<<i;

        for(unsigned int j=0; j<vecA.size(); j++)
        {
            if(vecA[j]->GetNum() != 1)
            {
                if(vecA[j]->GetS1() == vecS[i]->GetId() || vecA[j]->GetS2() == vecS[i]->GetId())
                {
                    areteatrier.push_back(new Arete{vecA[j]->GetName(),vecA[j]->GetS1(),vecA[j]->GetS2(),vecA[j]->GetP1(),vecA[j]->GetP2(),vecA[j]->GetColor(),1, 0, 0});
                    vecA[j]->SetNum(1);
                }

                else
                {
                    //rien
                }
            }

        }
        ///étape comparer les arêtes du tableau d'arêtes découvertes

        areteTrier = trierAretesPoids2(areteatrier);


        ///couleur de la plus petite arête = vert (l'arête de la case 1)

        s1=areteTrier[k]->GetS1();
        s2=areteTrier[k]->GetS2();

        while(vecS[s1]->GetVal() == vecS[s2]->GetVal())///faux
        {
            k=k+1;
            s1=areteTrier[k]->GetS1();
            s2=areteTrier[k]->GetS2();
        }


        //std::cout<<"la valeur de k est:"<<k;


        areteTrier[k]->SetColor("green");


        //std::cout  << "\n-- TRI EFFECTUE POUR POIDS 1 -- \n" ;
        //afficherAretes(areteTrier);

        areteaffichage.push_back(new Arete{areteTrier[k]->GetName(),areteTrier[k]->GetS1(),areteTrier[k]->GetS2(),areteTrier[k]->GetP1(),areteTrier[k]->GetP2(),areteTrier[k]->GetColor(), areteTrier[k]->GetNum(),areteTrier[k]->GetEtat(),areteTrier[k]->GetEtatd()});


        if(vecS[areteTrier[k]->GetS1()]->GetVal()==0)
        {
            i=areteTrier[k]->GetS2();

        }
        else if(vecS[areteTrier[k]->GetS1()]->GetVal()==1)
        {
            i=areteTrier[k]->GetS1();

        }

        for(int e=0; e<vecA.size(); e++)
        {
            if(vecA[e]->GetName()==areteTrier[k]->GetName())
            {
                vecA.erase(vecA.begin()+e);
            }
        }

        for(int e=0; e<areteatrier.size(); e++)
        {
            if(areteatrier[e]->GetName()==areteTrier[k]->GetName())
            {
                areteatrier.erase(areteatrier.begin()+e);//on supprime le tableau
            }
        }

        compteur = compteur + 1;//on incrémente de compteur
        k=0;
        areteTrier.clear();
    }

///affichage console

    std::cout<<""<<std::endl;

    for(int i=0; i<areteaffichage.size(); i++)
    {
        std::cout<<"Etape   "<<i<<"   Arrete   "<<areteaffichage[i]->GetName()<<"   Sommet 1   "<<areteaffichage[i]->GetS1()<<"   Sommet 2   "<<areteaffichage[i]->GetS2()<< "   Poids 2   "<<areteaffichage[i]->GetP2()<<std::endl;
    }
    std::cout<<""<<std::endl;
///cout total

    for(int i=0; i<areteaffichage.size(); i++)
    {
        couttot = couttot + areteaffichage[i]->GetP2();//cout tot
    }
    std::cout<<"le cout total est "<<couttot<<std::endl;//affichage console
    std::cout<<""<<std::endl;


///affichage

///Aretes
    for(int t=0; t<areteaffichage.size(); t++)
    {
        areteaffichage[t]->dessinerAreteP2(svgout, vecS);//affichage svg
    }

///Sommets
    for (int z=0 ; z<vecS.size() ; z++)
    {
        vecS[z]->dessinerSommet(svgout);//affichage svg
    }
}


std::vector<Graphe*> trierPoids1Total(std::vector<Graphe*> monTableau)
{
    std::vector<Graphe*> monTableauTampon;
    std::vector<int> list_p1;

    int pt1,pt2;
    int i,j,k,l;

    for(i=0 ; i<monTableau.size() ; ++i)
    {
        list_p1.push_back(monTableau[i]->GetPt1());//au ajoute une case au tableau
    }

    std::sort(list_p1.begin(), list_p1.end());//fonction de trie

    for(j=0 ; j<list_p1.size() ; ++j)
    {
        for(k=0 ; k < monTableau.size() ; k++)
        {
            if(list_p1[j] == monTableau[k]->GetPt1())
            {
                monTableauTampon.push_back(new Graphe{monTableau[k]->GetArete(),monTableau[k]->GetPt1(),monTableau[k]->GetPt2()});
                monTableau.erase(monTableau.begin()+k);
            }
        }
    }

    return monTableauTampon;
}

void AfficherGraphe(Svgfile& svgout, std::vector<Graphe*> g)///affiche que les graphe opti
{
    ///Axe
    svgout.addLine(100, 100, 100, 400, "black");
    svgout.addLine(100, 400, 400, 400, "black");
    svgout.addText(90, 90, "cout 2", "black");
    svgout.addText(410, 398, "cout 1", "black");

    for(int i=0 ; i < g.size(); i++)
    {

        ///affichage console
        std::cout << "graphe numero: " << i <<" \n" ;

        std::cout << "Poids total 1:  "  << g[i]->GetPt1() << " Poids total 2: "  << g[i]->GetPt2() << " \n" ;

        ///affichage svg
        svgout.addDisk(100+((g[i]->GetPt1())*4), 400-((g[i]->GetPt2())*4), 3, "green");

    }
}

void AfficherGrapheTout(Svgfile& svgout, std::vector<Graphe*> g) ///affiche tous les graphes acceptés
{
    svgout.addLine(100, 100, 100, 400, "black");
    svgout.addLine(100, 400, 400, 400, "black");
    svgout.addText(90, 90, "cout 2", "black");
    svgout.addText(410, 398, "cout 1", "black");

    for(int i=0 ; i < g.size(); i++)
    {
        svgout.addDisk(100+((g[i]->GetPt1())*4), 400-((g[i]->GetPt2())*4), 3, "red");

    }
}

std::vector<Graphe*> Pareto_tri(std::vector<Graphe*> graphe_trier)//fonction qui gère les égalités de poids
{

    std::vector<Graphe*> g;
    int p=0;

    g.push_back(new Graphe{graphe_trier[0]->GetArete(),graphe_trier[0]->GetPt1(),graphe_trier[0]->GetPt2()});

    for(int j = 1 ; j < graphe_trier.size() ; j++)
    {
        if(graphe_trier[p]->GetPt2() > graphe_trier[j]->GetPt2())
        {
            g.push_back(new Graphe{graphe_trier[j]->GetArete(),graphe_trier[j]->GetPt1(),graphe_trier[j]->GetPt2()});
            p=j;
        }
    }


    return g;
}

//--//

std::vector<Graphe*> Pareto(std::vector<Arete*> vecA, std::vector<Sommet*> vecS)///fonction pareto
{

    std::vector<int>       vec;
    std::vector<int>       vec1;//tableau tampon
    std::vector<int>       vec2;//tableau tampon

    std::vector<Graphe*> graphe;

    float pt1, pt2;

    int somme = 0;

    for(int i=0; i<vecA.size(); i++)//remplissage du tableau
    {
        vec.push_back(0);
        vec1.push_back(0);
    }

    for(int j = 0; j<vecA.size()-1; j++)
    {
        vec[j]=1;
        somme=0;

        for(int i=0; i<vec.size(); i++)
        {
            somme=somme+vec[i];
        }
        if(somme==vecS.size()-1  )
        {
            for(int k=0; k<vec.size(); k++)
            {
                vec1[k] = vec[k];
            }
            std::sort (vec1.begin(),vec1.end());

            do
            {

                for(int m = 0; m < vec1.size(); m++)
                {
                    vec2.push_back(vec1[m]);

                }

            }
            while ( std::next_permutation(vec1.begin(),vec1.end()));

        }

    }

    std::cout << "TAILLE V2 : "<< vec2.size() << " \n" ;

    while(vec2.size() != 0)   //// DEBUT BOUCLE POUR TABLEAU ////
    {
        int s1 =0;
        int s2 =0;
        int test =0;

        int val = 0;
        int somme_connexe = 0;
        std::vector<int> connexe;

        for(int b = 0 ; b < vecS.size() ; b++)
        {
            vecS[b]->SetEtat(0);
            connexe.push_back(b+1);
        }

        for(int i=0; i<vecA.size(); i++)
        {
            somme_connexe=0;
            vecA[i]->SetEtat(vec2[0]);
            vec2.erase(vec2.begin());

            if(vecA[i]->GetEtat()==1) ////
            {
                s1 = vecA[i]->GetS1();
                s2 = vecA[i]->GetS2();

                vecS[s1]->SetEtat(1);
                vecS[s2]->SetEtat(1);

                val = connexe[s1];
                connexe[s1] = connexe[s2];

                for(int e = 0 ; e < connexe.size(); e++)
                {
                    if(connexe[e] == val)
                    {
                        connexe[e] = connexe[s2];
                    }
                }

            }

            for(int t = 0 ; t < connexe.size() ; t++)
            {
                somme_connexe = somme_connexe + connexe[t];
            }


        }

        for( int z = 0 ; z < vecS.size(); z++)
        {
            test = test + vecS[z]->GetEtat();
        }

        if(test == vecS.size())
        {

            //std::cout << somme_connexe << "  =>  " << connexe.size()*connexe[0] << "\n\n" << "" ;

            if(somme_connexe == connexe.size()*connexe[0])
            {
                pt1 = Poids1_Total(vecA);
                pt2 = Poids2_Total(vecA);
                graphe.push_back(new Graphe{vecA,pt1,pt2});
            }
        }


    }

    return graphe;
}
//--//

std::vector<Arete*> Graphe::GetArete()
{
    return m_arete;
}

float Graphe::GetPt1()
{
    return m_poids1Total;
}


float Graphe::GetPt2()
{
    return m_poids2Total;
}

float Graphe::SetPt2(float poids2Total)
{
    m_poids2Total = poids2Total;
    return m_poids2Total;
}

///normalement utilisé pour la partie 2
std::vector<Graphe*> Pareto2(std::vector<Arete*> vecA, std::vector<Sommet*> vecS)/// fonction pareto
{

    std::vector<int>       vec;
    std::vector<int>       vec1;
    std::vector<int>       vec2;

    std::vector<Graphe*> graphe;

    float pt1, pt2;

    int somme = 0;

    for(int i=0; i<vecA.size(); i++)
    {
        vec.push_back(0);
        vec1.push_back(0);
    }

    for(int j = 0; j<vecA.size()-1; j++)
    {
        vec[j]=1;
        somme=0;

        for(int i=0; i<vec.size(); i++)
        {
            somme=somme+vec[i];
        }
        if(somme==vecS.size()-1  )
        {
            for(int k=0; k<vec.size(); k++)
            {
                vec1[k] = vec[k];
            }
            std::sort (vec1.begin(),vec1.end());

            do
            {

                for(int m = 0; m < vec1.size(); m++)
                {
                    vec2.push_back(vec1[m]);

                }

            }
            while ( std::next_permutation(vec1.begin(),vec1.end()));

        }

    }

    std::cout << "TAILLE V2 : "<< vec2.size() << " \n" ;

    int j=0;
    int e;

    while(j != vec2.size())   //// DEBUT BOUCLE POUR TABLEAU ////
    {
        int s1 =0;
        int s2 =0;
        int test =0;

        int val = 0;
        int somme_connexe = 0;
        std::vector<int> connexe;

        for(int b = 0 ; b < vecS.size() ; b++)
        {
            vecS[b]->SetEtat(0);
            connexe.push_back(b+1);
        }

        for(int i=0; i<vecA.size(); i++)
        {
            somme_connexe=0;
            e=vec2[j];
            vecA[i]->SetEtat(e);
            //vec2.erase(vec2.begin());

            if(vecA[i]->GetEtat()==1) //
            {
                s1 = vecA[i]->GetS1();
                s2 = vecA[i]->GetS2();

                vecS[s1]->SetEtat(1);
                vecS[s2]->SetEtat(1);

                val = connexe[s1];
                connexe[s1] = connexe[s2];

                for(int e = 0 ; e < connexe.size(); e++)
                {
                    if(connexe[e] == val)
                    {
                        connexe[e] = connexe[s2];
                    }
                }

            }

            for(int t = 0 ; t < connexe.size() ; t++)
            {
                somme_connexe = somme_connexe + connexe[t];
            }

            j++;
        }

        /*for(int g=0; g<vecA.size(); g++)
            {
                std::cout<<"nom "<<vecA[g]->GetName()<<" etat "<<vecA[g]->GetEtat()<<std::endl;
            }*/


        for( int z = 0 ; z < vecS.size(); z++)
        {
            test = test + vecS[z]->GetEtat();
        }

        if(test == vecS.size())
        {

            //std::cout << somme_connexe << "  =>  " << connexe.size()*connexe[0] << "\n\n" << "" ;

            if(somme_connexe == connexe.size()*connexe[0])
            {
                pt1 = Poids1_Total(vecA);
                pt2 = Poids2_Total(vecA);
                graphe.push_back(new Graphe{vecA,pt1,pt2});

            }

        }

    }



    return graphe;
}

std::vector<Graphe*> initialisation_Pareto(std::vector<Graphe*> graphe_trier)
{

    std::vector<Graphe*> pa;

float base = graphe_trier[0]->GetPt2()+1;

   for(int j =0 ; j < graphe_trier.size() ; j++)
    {
        for(int p = 1 ; p < graphe_trier.size() ; p++)
        {
            if(graphe_trier[j]->GetPt1() == graphe_trier[p]->GetPt1())
            {
                if(graphe_trier[j]->GetPt2() > graphe_trier[p]->GetPt2())
                {
                   graphe_trier[j]->SetPt2(base);
                }
                else if(graphe_trier[j]->GetPt2() < graphe_trier[p]->GetPt2())
               {
                   graphe_trier[p]->SetPt2(base);
                }
            }
        }
    }

    for(int a =0 ; a < graphe_trier.size() ; a++)
    {
        if(graphe_trier[a]->GetPt2() != base)
        {
            pa.push_back(new Graphe{graphe_trier[a]->GetArete(),graphe_trier[a]->GetPt1(),graphe_trier[a]->GetPt2()});
        }
    }

    return pa;

}


