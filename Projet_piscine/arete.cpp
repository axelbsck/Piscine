#include "arete.h"

Arete::Arete(int name, int s1, int s2, float p1,float p2, std::string c, int num, int etat,int etatd) :
    m_name(name), m_sommet1(s1), m_sommet2(s2), m_poids1(p1), m_poids2(p2),m_c(c), m_num(num), m_etat(etat), m_etatd(etatd)
{}

///inspiré du tp 2
void remplirAretes(std::vector<Arete*>& monTableau,std::string f1,std::string f2)///remplissage des aretes
{
    ///variables
    int i;
    int taille,taille2,temp,nom,sommet_depart,sommet_arrive;//initialisation
    float poids1, poids2;
    std::ifstream ifs{f1};
    std::ifstream ifs2{f2};

    ///lecture des fichiers
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture ");
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    for( i = 0 ; i < taille ; i++)
    {
        ifs>>temp;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs>>temp;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs>>temp;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
    }
    ifs >> taille2;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    ifs2 >> temp >> temp;
    for(i=0 ; i < taille2 ; i++)
    {
        ifs>>nom;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs>>sommet_depart;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs>>sommet_arrive;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");


        ifs2>>temp;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs2>>poids1;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs2>>poids2;
        if(ifs.fail())
            throw std::runtime_error("Probleme lecture données sommet");

        monTableau.push_back(new Arete{nom,sommet_depart,sommet_arrive,poids1,poids2,"black", 0, 0, 0});///ajout des arêtes tableau
    }


}

std::vector<Arete*> trierAretesPoids1(std::vector<Arete*> monTableau) ///trie par poids 1
{
    std::vector<Arete*> monTableauTampon;
    std::vector<float> list_p;

    int i,j,k;

    for(i=0 ; i<monTableau.size() ; ++i)
    {
        list_p.push_back(monTableau[i]->GetP1());
    }

    std::sort(list_p.begin(), list_p.end());

    for(j=0 ; j<list_p.size() ; ++j)
    {
        for(k=0 ; k < monTableau.size() ; k++)
        {
            if(list_p[j] == monTableau[k]->GetP1() )
            {
                monTableauTampon.push_back(new Arete{monTableau[k]->GetName(),monTableau[k]->GetS1(),
                                                     monTableau[k]->GetS2(),monTableau[k]->GetP1(),
                                                     monTableau[k]->GetP2(),monTableau[k]->GetColor(), monTableau[k]->GetNum(), monTableau[k]->GetEtat(),monTableau[k]->GetEtatd()});//incrémentation
                monTableau.erase(monTableau.begin()+k);
            }
        }
    }

    return monTableauTampon;
}

std::vector<Arete*> trierAretesPoids2(std::vector<Arete*> monTableau)///tri par poids 2
{
    std::vector<Arete*> monTableauTampon;
    std::vector<float> list_p;

    int i,j,k;

    for(i=0 ; i<monTableau.size() ; ++i)
    {
        list_p.push_back(monTableau[i]->GetP2());
    }

    std::sort(list_p.begin(), list_p.end());

    for(j=0 ; j<list_p.size() ; ++j)
    {
        for(k=0 ; k < monTableau.size() ; k++)
        {
            if(list_p[j] == monTableau[k]->GetP2() )
            {
                monTableauTampon.push_back(new Arete{monTableau[k]->GetName(),monTableau[k]->GetS1(),
                                                     monTableau[k]->GetS2(),monTableau[k]->GetP1(),
                                                     monTableau[k]->GetP2(),monTableau[k]->GetColor(),monTableau[k]->GetNum(), monTableau[k]->GetEtat(), monTableau[k]->GetEtatd()});
                monTableau.erase(monTableau.begin()+k);
            }
        }
    }

    return monTableauTampon;
}


void Arete::afficher() const///affichage des aretes en console
{
    std::cout << "NOM:   " << m_name << "  S1:   " << m_sommet1 << "   S2:   " << m_sommet2 << "   P1:   " << m_poids1<< "   P2:   "<< m_poids2 << "   C:   "<< m_c << std::endl;
}


void afficherAretes(std::vector<Arete*>& monTableau)///affichage des aretes en svg
{
    for (size_t i=0 ; i< monTableau.size() ; i++)
    {
        monTableau[i]->afficher();//affiche chaque case du tableau
    }
}


///getters et setters
int Arete::GetS1()
{
    return m_sommet1;
}

int Arete::GetS2()
{
    return m_sommet2;
}

int Arete::GetName()
{
    return m_name;
}

std::string Arete::SetColor(std::string couleur)
{
    m_c = couleur;
    return m_c;
}

std::string Arete::GetColor()
{
    return m_c;
}

float Arete::SetP1(float p1)
{
    m_poids1 = p1;
    return m_poids1;
}


float Arete::GetP1()
{
    return m_poids1;
}

float Arete::GetP2()
{
    return m_poids2;
}

int Arete::GetNum()
{
    return m_num;
}

float Arete::SetP2(float p2)
{
    m_poids2 = p2;
    return m_poids2;
}

int Arete::SetNum(int num)
{
    m_num = num;
    return m_num;
}

int Arete::GetEtat()
{
    return m_etat;
}

int Arete::SetEtat(int etat)
{
    m_etat = etat;
    return m_etat;
}

int Arete::GetEtatd()
{
    return m_etatd;
}

int Arete::SetEtatd(int etatd)
{
    m_etatd = etatd;
    return m_etatd;
}

Arete::~Arete()//destructeur
{
    //dtor
}


void Arete::dessinerArete(Svgfile& svgout, std::vector<Sommet*>som)///dessin des aretes avec le numero
{
    float x1, y1, x2, y2;
    x1 = som[m_sommet1]->GetX();//on récupère les coordonnées de chaque sommet lié à l'arrête
    y1 = som[m_sommet1]->GetY();
    x2 = som[m_sommet2]->GetX();
    y2 = som[m_sommet2]->GetY();

    svgout.addLine(x1, y1, x2, y2, m_c);
    svgout.addText(((x1+x2)/2)+5, ((y1+y2)/2)+5, m_name, "blue");//dessin svg

}

void Arete::dessinerAreteP1(Svgfile& svgout, std::vector<Sommet*>som)///dessin des aretes avec le poids1
{
    float x1, y1, x2, y2;
    x1 = som[m_sommet1]->GetX();//on récupère les coordonnées de chaque sommet lié à l'arrête
    y1 = som[m_sommet1]->GetY();
    x2 = som[m_sommet2]->GetX();
    y2 = som[m_sommet2]->GetY();

    svgout.addLine(x1, y1, x2, y2, m_c);
    svgout.addText(((x1+x2)/2)+5, ((y1+y2)/2)+5, m_poids1, "blue");//dessin svg

}

void Arete::dessinerAreteP2(Svgfile& svgout, std::vector<Sommet*>som)///dessin des aretes avec le poids2
{
    float x1, y1, x2, y2;
    x1 = som[m_sommet1]->GetX();///on récupère les coordonnées du sommet associé
    y1 = som[m_sommet1]->GetY();
    x2 = som[m_sommet2]->GetX();
    y2 = som[m_sommet2]->GetY();

    svgout.addLine(x1, y1, x2, y2, m_c);
    svgout.addText(((x1+x2)/2)+5, ((y1+y2)/2)+5, m_poids2, "blue");

}

float Poids1_Total(std::vector<Arete*> monTableau)///donne le poids total des aretes utilisées
{
    int i;
    float p1_total=0;

    for(i=0 ; i<monTableau.size() ; i++)//parcours du tableau
    {
        if(monTableau[i]->GetEtat()== 1)//parcours
        {
            p1_total = p1_total + monTableau[i]->GetP1();//somme
        }
    }

    return p1_total;
}


float Poids2_Total(std::vector<Arete*> monTableau)///même chose pour le poids 2
{
    int i;
    float p2_total=0;

    for(i=0 ; i<monTableau.size() ; i++)//parcours du tableau
    {
        if(monTableau[i]->GetEtat()==1)//si l'état est à 1
        {
            p2_total = p2_total + monTableau[i]->GetP2();//somme
        }
    }

    return p2_total;//retourne le poids total
}






