#include "arete.h"
#include "possibilite.h"
#include "sommet.h"

Possibilite::Possibilite(int som, int pred, float poids, int etat) :
    m_som(som), m_pred(pred), m_poids(poids), m_etat(etat)//constructeur
{}

///getters et setters
int Possibilite::GetSom()
{
    return m_som;
}

int Possibilite::GetPred()
{
    return m_pred;
}

float Possibilite::GetPoids()
{
    return m_poids;
}

int Possibilite::GetEtat()
{
    return m_etat;
}


int Possibilite::SetSom(int som)
{
    m_som = som;
    return m_som;
}

int Possibilite::SetPred(int pred)
{
    m_pred = pred;
    return m_pred;
}

float Possibilite::SetPoids(float poids)
{
    m_poids = poids;
    return m_poids;
}

int Possibilite::SetEtat(int etat)
{
    m_etat = etat;
    return m_etat;
}

Possibilite::~Possibilite()//destructeur
{
    //dtor
}


float dijkstra(std::vector<Arete*>vecA, int Sd, int Sa)///fonction dijkstra
{
    std::vector<Possibilite*> p; //tableau possibilite
    int j=Sd;
    int pds=0;
    int k=0; //valeur de d�part
    std::vector<Arete*>vecA2;
    //int n=0;

    //tableau de possibilite
    p.push_back(new Possibilite{j,0,0,1});

    for(int i=0; i<vecA.size(); i++)
    {
        vecA2.push_back(new Arete{vecA[i]->GetName(),vecA[i]->GetS1(),vecA[i]->GetS2(),vecA[i]->GetP1(),vecA[i]->GetP2(),vecA[i]->GetColor(),1, vecA[i]->GetEtat(), 0});
    }


    while(j != Sa)//tant qu'on est pas au sommet d'arriv�
    {


        for(int m=0; m<vecA2.size(); m++)//on d�couvre les aretes associ�es au sommet
        {
            if(/*vecA2[m]->GetEtat()==1 &&*/ vecA2[m]->GetEtatd()==0)
            {
                if(j == vecA2[m]->GetS1())//si sommet 1
                {
                    pds= p[k]->GetPoids() + vecA2[m]->GetP2();
                    p.push_back(new Possibilite{vecA2[m]->GetS2(), j, pds, 0});
                    vecA2[m]->SetEtatd(1);//on change l'�tat

                }
                if(j == vecA2[m]->GetS2())//si sommet 2
                {
                    pds= p[k]->GetPoids() + vecA2[m]->GetP2();
                    p.push_back(new Possibilite{vecA2[m]->GetS1(), j, pds, 0});
                    vecA2[m]->SetEtatd(1);
                }

            }

        }


        p = trierPossibilitePoids(p);//on trie les poids et on r�cup�re la meilleure option

        k=0;

        while(p[k]->GetEtat()==1)//on �vite de r�utiliser une option
        {
            k=k+1;
            //std::cout<<k<<std::endl;
        }

        j = p[k]->GetSom();
        p[k]->SetEtat(1);

        //n++;

    }

    return p[k]->GetPoids();


}


std::vector<Possibilite*> trierPossibilitePoids(std::vector<Possibilite*> monTableau)///fonction qui trie les possibilit�s par poids2
{
    std::vector<Possibilite*> monTableauTampon;//initialisation
    std::vector<float> list_p;

    int i,j,k;

    for(i=0 ; i<monTableau.size() ; ++i)
    {
        list_p.push_back(monTableau[i]->GetPoids());//cr�ation d'une nouvelle case
    }

    std::sort(list_p.begin(), list_p.end());

    for(j=0 ; j<list_p.size() ; ++j)
    {
        for(k=0 ; k < monTableau.size() ; k++)
        {
            if(list_p[j] == monTableau[k]->GetPoids())//si le poids concorde
            {
                monTableauTampon.push_back(new Possibilite{monTableau[k]->GetSom(),monTableau[k]->GetPred(),
                                           monTableau[k]->GetPoids(),monTableau[k]->GetEtat()});//tampon
                monTableau.erase(monTableau.begin()+k);//suppression
            }
        }
    }

    return monTableauTampon;//retourne le tableau tampon
}

