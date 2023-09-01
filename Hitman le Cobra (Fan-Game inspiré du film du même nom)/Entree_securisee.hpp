#ifndef ENTREE_SECURISEE_HPP
#define ENTREE_SECURISEE_HPP
#include "Structure_entity.hpp"

// Initialistion de l'entrée sécurisée

template <typename Fonction_recherche, typename Fonction_exec, typename Tableau_actions> // Annonce du template
void entree_securisee(std::string& entree, Fonction_recherche& recherche, Fonction_exec& execution, Tableau_actions& liste_actions) // type_de_retour nom_de_la_fonction (argument)
{
	std::cout << "> ";
	while (!(std::cin >> entree) || recherche(entree, liste_actions) == false) // Tant que l'entrée console est invalide
	{
		if (std::cin.eof()) // Si le flux d'entrée est fermé
		{
			throw std::runtime_error("Boîte de commande fermée !");
		}
		else if (std::cin.fail()) // Si l'entrée est invalide
		{
			std::cout << "Entrée invalide" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Flux d'entrée 
		}
		else // Si la commande entrée n'existe pas
		{
			std::cout << "Commande invalide" << std::endl;
		}
		std::cout << "> ";
	}
	std::cout << std::endl;
	execution();
	std::cout << std::endl;
}
// Permet une entrée sécurisée pour chaque entrée

#endif // ENTREE_SECURISEE_HPP