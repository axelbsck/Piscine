#ifndef UTILE_H_INCLUDED
#define UTILE_H_INCLUDED

#include <string>
#include <random>
#include <ctime>
#include <iostream>
#include <cstdio>

namespace utile
{

/// L'appel de cette fonction redirige les
/// donn�es du fichier dont le nom est pass�
/// en param�tre vers std::cin
/// On "simule" les frappes clavier ce qui
/// permet de tester sans avoir � retaper
/// � chaque fois les m�me donn�es
/// temporisation : nombre de milliseconde entre chaque frappe clavier
/// couleur : colorisation (WINDOWS seulement https://ss64.com/nt/color.html
///                         pr�fixer par 0x, exemple 0x1a vert sur fond bleu)
void startAutoCin(std::string fileName, size_t temporisation=0, short couleur=0);

/// Cette fonction doit �tre appel�e pour
/// terminer la saisie automatique et retrouver
/// un comportement normal (saisir au clavier)
void stopAutoCin();

/// Vide tampon clavier
void videCin();

/// Cette fonction retourne un entier al�atoire dans [min...max]
int alea(int min, int max);

/// Cette fonction retourne un r�el al�atoire dans [min...max[
double dalea(double min, double max);

/// Cette fonction retourne un entier al�atoire dans [min...max]
int alea2(int min, int max, std::mt19937& randGen);

/// Cette fonction retourne un r�el al�atoire dans [min...max[
double dalea2(double min, double max, std::mt19937& randGen);

/// Le code qui suit est sp�cifique aux plateformes Windows
/// et ne concerne ni macOS ni les Linux
#ifdef _WIN32
void accentsPourWindows();
#endif // _WIN32

}


#endif // UTIL_H_INCLUDED

