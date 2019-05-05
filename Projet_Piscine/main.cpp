#include "svgfile.h"
#include "utile.h"
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "sommet.h"
#include "arete.h"
#include "graphe.h"
#include "possibilite.h"

//void dessinerscene2(Svgfile& svgout);
//void prim(Svgfile& svgout, std::vector<Sommet*>som,std::vector<Arete*>vecA);

int main()
{


    int action;

    std::cout<<"\nBienvenue !!!\n"<<std::endl;
    do
    {
        std::cout<<"Que voulez vous faire ?\n"<<std::endl;
        std::cout<<"1_Afficher un graphe"<<std::endl;
        std::cout<<"2_Realiser Prim pour le poids 1 d'un graphe"<<std::endl;
        std::cout<<"3_Realiser Prim pour le poids 2 d'un graphe"<<std::endl;
        std::cout<<"4_Realiser Pareto pour un graphe"<<std::endl;
        std::cout<<"5_Partie 3"<<std::endl;
        std::cout<<"6_Quitter"<<std::endl;


        do
        {
            std::cout<<"Saisie : ";
            std::cin>>action;
        }
        while(action!=1 && action !=2 && action !=3 && action !=4 && action !=5 && action !=6);


        if(action==1)//donne le graphe
        {

            Svgfile svgout;
            svgout.addGrid();

            std::string fichier = "";
            std::string numero = "0";

            std::cout<<"Nom du fichier : ";
            std::cin>>fichier;
            std::cout<<""<<std::endl;
            std::cout<<"Numero du fichier : ";
            std::cin>>numero;

            std::string f1 = "files/" + fichier + ".txt" ;
            std::string f2 = "files/" + fichier + "_weights_" + numero + ".txt" ;


            std::vector<Sommet*> vecS;
            std::vector<Arete*>vecA;

            Graphe g(vecA, 0, 0);

            remplirSommets(vecS,f1);
            //afficherSommets(svgout, vecS);

            remplirAretes(vecA,f1,f2);
            //afficherAretes(vecA);
            g.dessinerGraphe(svgout, vecS, vecA);

        }

        else if(action==2)//donne prim poids 1
        {
            Svgfile svgout;
            svgout.addGrid();

            std::string fichier = "";
            std::string numero = "0";
            std::cout<<"Nom du fichier : ";
            std::cin>>fichier;
            std::cout<<""<<std::endl;
            std::cout<<"Numero du fichier : ";
            std::cin>>numero;


            std::string f1 = "files/" + fichier + ".txt" ;
            std::string f2 = "files/" + fichier + "_weights_" + numero + ".txt" ;


            std::vector<Sommet*> vecS;
            std::vector<Arete*>vecA;

            Graphe g(vecA, 0, 0);

            remplirSommets(vecS,f1);
            //afficherSommets(svgout, vecS);

            remplirAretes(vecA,f1,f2);
            //afficherAretes(vecA);
            g.prim1(svgout, vecS, vecA);
        }

        else if (action==3)//donne prim poids 2
        {
            Svgfile svgout;
            svgout.addGrid();

            std::string fichier = "";
            std::string numero = "0";
            std::cout<<"Nom du fichier : ";
            std::cin>>fichier;
            std::cout<<""<<std::endl;
            std::cout<<"Numero du fichier : ";
            std::cin>>numero;


            std::string f1 = "files/" + fichier + ".txt" ;
            std::string f2 = "files/" + fichier + "_weights_" + numero + ".txt" ;


            std::vector<Sommet*> vecS;
            std::vector<Arete*>vecA;

            Graphe g(vecA, 0, 0);

            remplirSommets(vecS,f1);
            //afficherSommets(svgout, vecS);

            remplirAretes(vecA,f1,f2);
            //afficherAretes(vecA);
            g.prim2(svgout, vecS, vecA);

        }



        else if(action==4)//pareto
        {
            Svgfile svgout;
            svgout.addGrid();

            std::string fichier = "";
            std::string numero = "0";
            std::cout<<"Nom du fichier : ";
            std::cin>>fichier;
            std::cout<<""<<std::endl;
            std::cout<<"Numero du fichier : ";
            std::cin>>numero;


            std::string f1 = "files/" + fichier + ".txt" ;
            std::string f2 = "files/" + fichier + "_weights_" + numero + ".txt" ;


            std::vector<Sommet*> vecS;

            std::vector<Arete*>    vecA;
            std::vector<Arete*>    vecA_trier_p1;
            std::vector<Arete*>    vecA_trier_p2;

            std::vector<Graphe*>   graphe;
            std::vector<Graphe*>   graphe_trier;
            std::vector<Graphe*>   graphe_pareto;
            std::vector<Graphe*>   graphe_pareto_2;


            std::vector<int>       vec;
            std::vector<int>       vec1;
            std::vector<int>       vec2;

            float pt1, pt2;

            // -----------------------   //

            remplirSommets(vecS,f1);
            remplirAretes(vecA,f1,f2);

            // ----------------------    //

            graphe = Pareto(vecA,vecS);
            graphe_trier = trierPoids1Total(graphe);
            graphe_pareto = Pareto_tri(graphe_trier);
            graphe_pareto_2 = initialisation_Pareto(graphe_pareto);



            AfficherGrapheTout(svgout, graphe);
            AfficherGraphe(svgout, graphe_pareto_2);

        }

        else if (action==5)//pareto partie 3
        {
            Svgfile svgout;
            svgout.addGrid();

            std::string fichier = "";
            std::string numero = "0";
            std::cout<<"Nom du fichier : ";
            std::cin>>fichier;
            std::cout<<""<<std::endl;
            std::cout<<"Numero du fichier : ";
            std::cin>>numero;
            std::cout<<""<<std::endl;
            int Pt=0;

            std::string f1 = "files/" + fichier + ".txt" ;
            std::string f2 = "files/" + fichier + "_weights_" + numero + ".txt" ;


            std::vector<Sommet*> vecS;
            std::vector<Arete*>vecA;
            std::vector<Arete*>vecu;


            //float pt1, pt2;

            // -----------------------   //

            remplirSommets(vecS,f1);
            remplirAretes(vecA,f1,f2);

            // ----------------------    //
            int sa;
            int sd;
            int poidsdij;

            std::cout<<"Sommet de depart : ";
            std::cin>>sa;
            std::cout<<""<<std::endl;
            std::cout<<"Numero d'arrive : ";
            std::cin>>sd;

            poidsdij = dijkstra(vecA, sa, sd);

            std::cout<<"Le plus cours chemin du sommet "<<sa<<" au sommet "<<sd<<" est de poids "<<poidsdij<<std::endl;
            std::cout<<""<<std::endl:

            // ----------------------  //

            ///pour la partie 3
            ///Il faut faire tourner la fonction Dijkstra pour tous les sommets et récupérer le nouveau poids total 2
            ///Un seul probleme : lors du remplissage du tableau graphe, les états des arêtes ne sont pas correctement attribués
            ///ci-dessous en commentaire, le code qui répond à la aprtie 3

            /*std::vector<Graphe*>   graphe;
            std::vector<Graphe*>   graphe_trier;
            std::vector<Graphe*>   g;

            std::vector<int>       vec;
            std::vector<int>       vec1;
            std::vector<int>       vec2;

            graphe = Pareto2(vecA,vecS);


            for(int x=0; x<graphe.size(); x++)
            {
               for(int i = 0; i<vecS.size(); i++)
               {
                   for(int j=0; j<vecS.size(); j++)
                   {
                       if(i != j)
                       {
                           Pt = Pt + dijkstra(graphe[x]->GetArete(), i, j);
                       }
                   }
               }

               graphe[x]->SetPt2(Pt);
               graphe_trier = trierPoids1Total(graphe);

            }

            std::cout << "  ----------      AVANT PARETO      ----------------------"<< "\n\n" ;

            std::cout<< " TAILLE GRAPHE TRIER: " << graphe_trier.size() << "\n";

            std::cout << "  ----------      PARETO :       ----------------------"<< "\n\n" ;

            g = Pareto_tri(graphe_trier);
            AfficherGrapheTout(svgout, g);
            AfficherGraphe(svgout, g);*/

        }
    }
    while(action!=6);

    return 0;
}

















