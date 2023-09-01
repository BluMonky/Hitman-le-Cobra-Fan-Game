#include "Fonction_combat.hpp"
#include "Cutscenes.hpp"

bool combat(entity& joueur, entity& ennemi, int& niveau)
{
	std::chrono::milliseconds pause(500);
	for (auto& action : joueur.liste_actions)
	{
		if (action.classe == "combat")
		{
			action.avaible = true;
		}
		else if (action.classe == "menu")
		{
			action.avaible = false;
		}
	}
	for (auto& action : ennemi.liste_actions)
	{
		if (action.classe == "combat")
		{
			action.avaible = true;
		}
		else if (action.classe == "menu")
		{
			action.avaible = false;
		}
	}
	// Boucles rendant les actions pour le combat disponibles et celles pour le menu principal indisponibles
	if (niveau == 0)
	{
		for (auto ligne : niveau_0)
		{
			std::this_thread::sleep_for(pause * 4);
			std::cout << ligne << std::endl;
		};
		std::cout << std::endl;
	}
	else if (niveau == 1)
	{
		for (auto ligne : niveau_1)
		{
			std::this_thread::sleep_for(pause * 4);
			std::cout << ligne << std::endl;
		};
		std::cout << std::endl;
	}
	else if (niveau == 2)
	{
		for (auto ligne : niveau_2)
		{
			std::this_thread::sleep_for(pause * 4);
			std::cout << ligne << std::endl;
		};
		std::cout << std::endl;
	}
	else if (niveau == 3)
	{
		for (auto ligne : niveau_3)
		{
			std::this_thread::sleep_for(pause * 4);
			std::cout << ligne << std::endl;
		};
		std::cout << std::endl;
	}
	else if (niveau == 4)
	{
		for (auto ligne : niveau_4)
		{
			std::this_thread::sleep_for(pause * 4);
			std::cout << ligne << std::endl;
		};
		std::cout << std::endl;
	}
	else
	{
		std::this_thread::sleep_for(pause * 4);
		std::cout << "Ceci est un bug." << std::endl;
		std::cout << std::endl;
		return false;
	}
	// Sert à afficher les cinématiques

	int tour{ 1 };
	entity copie_joueur = joueur;
	entity copie_ennemi = ennemi;
	bool joueur_a_deja_joue{ false };
	bool ennemi_a_deja_joue{ false };
	bool victoire{ false };
	bool fin_de_combat{ false };
	// Initialisation des variables pour le combat

	while (fin_de_combat == false)
	{
		if (ennemi_a_deja_joue == true)
		{
			joueur_a_deja_joue = true;
			ennemi_a_deja_joue = false;
			joueur.fonction_a_moi_de_jouer(ennemi);
			ennemi.fonction_mort();
			if (ennemi.test_mort() == true)
			{
				fin_de_combat = true;
				std::this_thread::sleep_for(pause);
				std::cout << joueur.entity_name << " a gagné !" << std::endl;
				++niveau;
				if (niveau > 4)
				{
					std::cout << std::endl;
					for (auto ligne : fin)
					{
						std::this_thread::sleep_for(pause * 4);
						std::cout << ligne << std::endl;
					};
				}
				continue;
			}
		}
		else if (joueur_a_deja_joue == true)
		{
			ennemi_a_deja_joue = true;
			joueur_a_deja_joue = false;
			ennemi.fonction_a_moi_de_jouer(joueur);
			joueur.fonction_mort();
			if (joueur.test_mort() == true)
			{
				fin_de_combat = true;
				std::this_thread::sleep_for(pause);
				std::cout << ennemi.entity_name << " a gagné !" << std::endl;
				continue;
			}
		}
		else
		{
			if (joueur.SPEED > ennemi.SPEED)
			{
				joueur_a_deja_joue = false;
				ennemi_a_deja_joue = true;
			}
			else if (joueur.SPEED < ennemi.SPEED)
			{
				joueur_a_deja_joue = true;
				ennemi_a_deja_joue = false;
			}
			else
			{
				joueur_a_deja_joue = false;
				ennemi_a_deja_joue = true;
			}
		}
		fonction_tours(tour);
	}
	// Boucle du combat

	joueur = copie_joueur;
	ennemi = copie_ennemi;
	// Remise des entités à leur état d'origine

	for (auto& action : joueur.liste_actions)
	{
		if (action.classe == "combat")
		{
			action.avaible = false;
		}
		else if (action.classe == "menu")
		{
			action.avaible = true;
		}
	}
	for (auto& action : ennemi.liste_actions)
	{
		if (action.classe == "combat")
		{
			action.avaible = false;
		}
		else if (action.classe == "menu")
		{
			action.avaible = true;
		}
	}
	// Boucles rendant les actions pour le menu principal disponibles et celles pour le combat indisponibles

	return victoire;
}