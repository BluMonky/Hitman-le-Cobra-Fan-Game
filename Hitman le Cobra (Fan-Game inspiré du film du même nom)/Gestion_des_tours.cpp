#include <iostream>
#include "Gestion_des_tours.hpp"

void compte_tours(int& tour_actuel)
{
	++tour_actuel; // tour_actuel + 1
}
// Compte les tours

void afficher_tours(int& tour)
{
	std::chrono::milliseconds pause(500);
	std::this_thread::sleep_for(pause);
	std::cout << "Tour actuel : " << tour << std::endl;
}
// Affiche le tour actuel

void fonction_tours(int& tour)
{
	afficher_tours(tour);
	compte_tours(tour);
}
// Regroupe les fonctions compte_tours et afficher_tours


// Initialisation des fonctions gérant un tour
/**********************************************************************************************************************/