#ifndef STRUCTURE_ENTITY_HPP
#define STRUCTURE_ENTITY_HPP
#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>
#include <thread>
#include <chrono>
#include "Entree_securisee.hpp"

struct entity // Structure utilisée pour les personnages
{
	std::string entity_name; // Nom du personnage
	int PV;				     // PV du personnage
	int ATT;				 // Attaque du personnage
	int SPEED;				 // Vitesse du personnage (sert à déterminer l'ordre de passage)
	int DEF;			     // Défense du personnage (sert à réduire les dégâts infligés)
	int PRECISION;			 // Vitesse du personnage (probabilité que l'attaque touche)
	std::string Classe;      // Classe du personnage (joueur ou bot)
	int PV_initiaux;		 // PV max qui servent pour des tests

	struct action
	{
		std::string action_name; // Le nom
		std::string description; // Sa description
		bool avaible;            // Sa disponibilité

		std::function<void()> fonction_quelconque;
		void executer_fonction()
		{
			fonction_quelconque();
		}
		// Lambda servant pour les fonctions ne recevant aucun argument

		std::function<void(entity&)> fonction_entite;
		void executer_fonction(entity& entite)
		{
			fonction_entite(entite);
		}
		// Lambda servant pour les actions sur une entité (en combat)

		std::function<bool(entity&, entity&, int&)> fonction_combat;
		void executer_fonction(entity& self, entity& adversaire, int& niveau)
		{
			fonction_combat(self, adversaire, niveau);
		}
		// Lambda servant à déclencher un combat

		std::string classe;

		std::function<void(int&)> fonction_sauvegarde;
		void executer_fonction(int& niveau)
		{
			fonction_sauvegarde(niveau);
		}
		// Lambda servant à sauvegarder et charger la partie
	};
	// La structure d'une action

	std::vector<action> liste_actions; // Liste des action réalisables par une entité



	// Initialisation des variables
/*******************************************************************************************************************/

	void afficher_aide();          // Affiche les actions disponibles et leur description

	// Fonction servant à donner des informations à l'utilisateur
/*******************************************************************************************************************/

	bool test_mort();              // Teste la mort d'une entité

	void message_mort();           // Affiche un message si le joueur est mort

	void remise_a_zero_des_PV();   // Empêche les PV d'être négatifs

	void fonction_mort();          // Regroupe toutes les fonctions précédentes en une pour toutes les exécuter


	// Fonctions gérant la mort du personnage
/*******************************************************************************************************************/

	action aide
	{
		"aide",
		"Affiche la description de toutes les actions",
		true,
		[&]() { afficher_aide(); },
		nullptr,
		nullptr,
		"tout"
	};
	// Exécute afficher_aide

	void assaut(entity& cible);
	// Fonction gérant l'attaque sur une entité

	void assaut_renforce(entity& cible);
	// Fonction gérant le spécial de l'entité Philippe

	action attaquer
	{
		"attaquer",
		"Attaque l'adversaire",
		false,
		nullptr,
		[&](entity& entite) { assaut(entite); },
		nullptr,
		"combat"
	};
	// Structure gérant l'attaque de base des entités

	action charger
	{
		"charger",
		"Charger la sauvegarde",
		true,
		nullptr,
		nullptr,
		nullptr,
		"menu",
		[&](int& niveau)
		{
			std::ifstream sauvegarde { "fichier_save.txt" };
			std::string niveau_sauvegarde{ "" };
			sauvegarde >> niveau_sauvegarde;
			niveau = std::stoi(niveau_sauvegarde);
			std::cout << "Sauvegarde chargée avec succès !" << std::endl;
		}
	};
	// Structure gérant la recharge de la sauvegarde en lisant dans le fichier .txt de sauvegarde

	action combattre
	{
		"combattre",
		"Démarrer un combat",
		true,
		nullptr,
		nullptr,
		nullptr,
		"menu"
	};

	action defense
	{
		"défense",
		"Augmente la défense",
		false,
		[&]() { DEF += DEF; std::cout << "Défense augmentée : " << DEF << std::endl; },
		nullptr,
		nullptr,
		"combat"
	};
	// Structure servant à augmenter la défense d'une entité

	action quitter
	{
		"quitter",
		"Quitter le programme",
		true,
		[]() { std::cout << "Fermeture du programme" << std::endl; },
		nullptr,
		nullptr,
		"menu"
	};
	// Structure servant à quitter le programme en affichant un message avant la fermeture

	action sauvegarder
	{
		"sauvegarder",
		"Sauvegarder la progression",
		true,
		nullptr,
		nullptr,
		nullptr,
		"menu",
		[&](int& niveau)
		{
			std::ofstream sauvegarde { "fichier_save.txt" };
			std::string niveau_a_ecrire{ "" };
			niveau_a_ecrire = std::to_string(niveau);
			sauvegarde << niveau_a_ecrire;

			std::cout << "Partie sauvegardée avec succès !" << std::endl;
		}
	};
	// Structure gérant la recharge de la sauvegarde en écrivant dans le fichier .txt de sauvegarde

	action special
	{
		"spécial",
		"Permet d'utiliser la capacité spéciale du joueur",
		false,
		nullptr,
		nullptr,
		nullptr,
		"combat"
	};
	// Structure gérant le spécial d'une entité


	// Fonctions gérant les différentes actions d'une entité
/*******************************************************************************************************************/

	std::string choix_actions_menu(entity& joueur, std::vector<entity>& ennemi, int& niveau); // Fonction gérant le menu principal

	std::string comportement();																  // Fonction gérant l'IA des bots

	void choix_actions_combat(entity& cible);												  // Fonction gérant le menu dans un combat

	void fonction_a_moi_de_jouer(entity& cible);											  // Gère le tour d'un joueur


	// Fonctions gérant le tour d'une entité
/*******************************************************************************************************************/
};

#endif // STRUCTURE_ENTITY_HPP