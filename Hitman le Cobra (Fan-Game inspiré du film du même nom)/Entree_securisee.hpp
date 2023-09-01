#ifndef ENTREE_SECURISEE_HPP
#define ENTREE_SECURISEE_HPP
#include "Structure_entity.hpp"

// Initialistion de l'entr�e s�curis�e

template <typename Fonction_recherche, typename Fonction_exec, typename Tableau_actions> // Annonce du template
void entree_securisee(std::string& entree, Fonction_recherche& recherche, Fonction_exec& execution, Tableau_actions& liste_actions) // type_de_retour nom_de_la_fonction (argument)
{
	std::cout << "> ";
	while (!(std::cin >> entree) || recherche(entree, liste_actions) == false) // Tant que l'entr�e console est invalide
	{
		if (std::cin.eof()) // Si le flux d'entr�e est ferm�
		{
			throw std::runtime_error("Bo�te de commande ferm�e !");
		}
		else if (std::cin.fail()) // Si l'entr�e est invalide
		{
			std::cout << "Entr�e invalide" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Flux d'entr�e 
		}
		else // Si la commande entr�e n'existe pas
		{
			std::cout << "Commande invalide" << std::endl;
		}
		std::cout << "> ";
	}
	std::cout << std::endl;
	execution();
	std::cout << std::endl;
}
// Permet une entr�e s�curis�e pour chaque entr�e

#endif // ENTREE_SECURISEE_HPP