#include "Structure_entity.hpp"
#include <cassert>

void entity::afficher_aide()
{
	std::chrono::milliseconds pause(500);
	for (auto& action_actuelle : liste_actions)
	{
		if (action_actuelle.avaible == true)
		{
			std::this_thread::sleep_for(pause);
			std::cout << action_actuelle.action_name << " : " << action_actuelle.description << std::endl;
		}
	}
}
// Affiche l'aide

bool entity::test_mort()
{
	return PV <= 0;
}
// Détermine si une entité est morte

void entity::message_mort()
{
	std::chrono::milliseconds pause(500);
	std::cout << "PV restants : " << PV << std::endl << std::endl;
	if (test_mort() == true)
	{
		std::this_thread::sleep_for(pause);
		std::cout << entity_name << " est mort." << std::endl;
		std::this_thread::sleep_for(pause);
	}
	else
	{
		std::this_thread::sleep_for(pause);
		std::cout << "Tour suivant !" << std::endl;
	}
}
// Permet d'afficher un message de mort en fonction du nom de l'entité

void entity::remise_a_zero_des_PV()
{
	std::chrono::milliseconds pause(500);
	if (test_mort() == true && PV < 0)
	{
		PV = 0;
	}
	message_mort();
	std::this_thread::sleep_for(pause);
}
// Remet les PV d'une entité à zéro si ils sont négatifs à l'aide de la fonction test_mort

void entity::fonction_mort()
{
	remise_a_zero_des_PV();
	std::cout << std::endl;
}
// Regroupe les fonctions de test_mort à message_mort et gère la mort d'une entité

void entity::assaut(entity& cible)
{
	std::chrono::milliseconds pause(500);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> facteur_aleatoire(1, 100);
	// Initialisation de l'aléatoire
	int Tentative{ 1 };
	int Dommages{ ATT - cible.DEF };
	if (Dommages <= 0)
	{
		Dommages = 1;
	}
	std::this_thread::sleep_for(pause);
	std::cout << entity_name << " attaque " << cible.entity_name << "." << std::endl;
	std::this_thread::sleep_for(pause);
	Tentative = facteur_aleatoire(gen);
	if (Tentative <= PRECISION)
	{
		std::cout << "Dégâts infligés : " << Dommages << std::endl;
		std::this_thread::sleep_for(pause);
		cible.PV -= Dommages;
	}
	else
	{
		std::cout << entity_name << " rate sa cible" << std::endl;
		std::this_thread::sleep_for(pause);
	}
}
// Permet à une entité d'attaquer une cible

void entity::assaut_renforce(entity& cible)
{
	std::chrono::milliseconds pause(500);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> facteur_aleatoire(1, 100);
	int Tentative{ 1 };
	int Dommages{ (ATT * 2) - cible.DEF };
	if (Dommages <= 0)
	{
		Dommages = 1;
	}
	std::this_thread::sleep_for(pause);
	std::cout << entity_name << " attaque " << cible.entity_name << "." << std::endl;
	std::this_thread::sleep_for(pause);
	Tentative = facteur_aleatoire(gen);
	if (Tentative <= PRECISION * 0.75)
	{
		std::cout << "Dégâts infligés : " << Dommages << std::endl;
		std::this_thread::sleep_for(pause);
		cible.PV -= Dommages;
	}
	else
	{
		std::cout << entity_name << " rate sa cible" << std::endl;
		std::this_thread::sleep_for(pause);
	}
}
// Permet à une entité d'attaquer une cible

std::string entity::choix_actions_menu(entity& joueur, std::vector<entity>& liste_ennemis, int& niveau)
{
	std::chrono::milliseconds pause(500);
	std::cout << "MENU PRINCIPAL" << std::endl << std::endl;
	std::this_thread::sleep_for(pause / 10);
	std::cout << "Niveau : " << niveau << std::endl << std::endl;
	std::this_thread::sleep_for(pause / 10);
	std::cout << "Sélectionne une action parmi les suivantes :" << std::endl;
	std::this_thread::sleep_for(pause / 10);
	std::cout << "combattre" << std::endl;
	std::this_thread::sleep_for(pause / 10);
	std::cout << "sauvegarder" << std::endl;
	std::this_thread::sleep_for(pause / 10);
	std::cout << "charger" << std::endl;
	std::this_thread::sleep_for(pause / 10);
	std::cout << "quitter" << std::endl;
	std::this_thread::sleep_for(pause / 10);
	std::cout << "aide" << std::endl;
	std::this_thread::sleep_for(pause);
	std::string choix{ "" };
	bool choix_correct{ false };
	action action_trouvee{ "default" };
	auto cherche_action
	{
		[&action_trouvee](std::string& choix, std::vector<action>& actions_d_entite) -> bool
		{
			bool trouve{ false };
			for (auto& action : actions_d_entite)
			{
				if (choix == action.action_name && action.avaible == true)
				{
					trouve = true;
					action_trouvee = action;
					break;
				}
			}
			return trouve;
		}
	};
	// Lambda cherchant une action
	auto execution_fonction
	{
		[&joueur, &liste_ennemis, &niveau, &action_trouvee, &choix]() -> void
		{
			std::chrono::milliseconds pause(500);
			if (choix == "combattre")
			{
				if (niveau > 4)
				{
					std::this_thread::sleep_for(pause);
					std::cout << "Tu as terminé le jeu, redémarre pour recommencer ou charge la sauvegarde." << std::endl;
					std::this_thread::sleep_for(pause);
					std::cout << std::endl;
				}
				else
				{
					std::this_thread::sleep_for(pause);
					action_trouvee.executer_fonction(joueur, liste_ennemis[niveau], niveau);
					std::this_thread::sleep_for(pause);
				}
			}
			else if (choix == "sauvegarder" || choix == "charger")
			{
				action_trouvee.executer_fonction(niveau);
			}
			else
			{
				action_trouvee.executer_fonction();
			}
		}
	};
	// Lambda exécutant la fonction
	entree_securisee(choix, cherche_action, execution_fonction, liste_actions);
	return choix;
}

std::string entity::comportement()
{
	std::string action_choisie{ "" };
	std::random_device choix_du_bot;
	std::mt19937 gen(choix_du_bot());
	std::uniform_int_distribution<int> facteur_aleatoire(1, 5);
	int choix{ facteur_aleatoire(gen) };
	if (PV <= PV_initiaux / 2 && PV >= PV_initiaux / 3)
	{
		action_choisie = "spécial";
	}
	else if (choix >= 1 && choix <= 4)
	{
		action_choisie = "attaquer";
	}
	else if (choix == 5)
	{
		action_choisie = "défense";
	}
	return action_choisie;
}
// IA du bot

void entity::choix_actions_combat(entity& cible)
{
	std::chrono::milliseconds pause(500);
	std::this_thread::sleep_for(pause);
	std::cout << "Sélectionne une action parmi les suivantes :" << std::endl;
	std::this_thread::sleep_for(pause / 10);
	std::cout << "attaquer" << std::endl;
	std::this_thread::sleep_for(pause / 10);
	std::cout << "spécial" << std::endl;
	std::this_thread::sleep_for(pause / 10);
	std::cout << "défense" << std::endl;
	std::this_thread::sleep_for(pause / 10);
	std::cout << "aide" << std::endl;
	std::this_thread::sleep_for(pause);
	std::string choix{ "" };
	bool choix_correct{ false };
	action action_trouvee{ "default" };
	auto cherche_action
	{
		[&action_trouvee](std::string& choix, std::vector<action>& actions_d_entite) -> bool
		{
			bool trouve{ false };
			for (auto& action : actions_d_entite)
			{
				if (choix == action.action_name && action.avaible == true)
				{
					trouve = true;
					action_trouvee = action;
					break;
				}
			}
			return trouve;
		}
	};
	auto execution_fonction
	{
		[&cible, &action_trouvee, &choix]() -> void
		{
			if (choix == "aide" || choix == "défense")
			{
				action_trouvee.executer_fonction();
			}
			else
			{
				action_trouvee.executer_fonction(cible);
			}
		}
	};
	entree_securisee(choix, cherche_action, execution_fonction, liste_actions);
}
// Permet à une entité de choisir une action en combat

void entity::fonction_a_moi_de_jouer(entity& cible)
{
	std::chrono::milliseconds pause(500);
	std::this_thread::sleep_for(pause);
	std::cout << "Au tour de " << entity_name << std::endl;
	if (Classe == "joueur")
	{
		std::this_thread::sleep_for(pause);
		choix_actions_combat(cible);
		std::this_thread::sleep_for(pause);
	}
	else if (Classe == "bot")
	{
		std::string action_choisie{ comportement() };
		for (auto& action : liste_actions)
		{
			if (action.action_name == action_choisie && action_choisie == "défense")
			{
				std::this_thread::sleep_for(pause);
				action.executer_fonction();
				std::this_thread::sleep_for(pause);
			}
			else if (action.action_name == action_choisie && action_choisie == "attaquer")
			{
				std::this_thread::sleep_for(pause);
				action.executer_fonction(cible);
				std::this_thread::sleep_for(pause);
			}
			else if (action.action_name == action_choisie && action_choisie == "spécial")
			{
				std::cout << action.description << std::endl;
				std::this_thread::sleep_for(pause);
				action.executer_fonction(cible);
				std::this_thread::sleep_for(pause);
			}
		}
	}
}
//  Gère le tour d'une entité