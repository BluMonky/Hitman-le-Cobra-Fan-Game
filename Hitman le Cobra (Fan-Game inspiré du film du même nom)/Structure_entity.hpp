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

struct entity // Structure utilis�e pour les personnages
{
	std::string entity_name; // Nom du personnage
	int PV;				     // PV du personnage
	int ATT;				 // Attaque du personnage
	int SPEED;				 // Vitesse du personnage (sert � d�terminer l'ordre de passage)
	int DEF;			     // D�fense du personnage (sert � r�duire les d�g�ts inflig�s)
	int PRECISION;			 // Vitesse du personnage (probabilit� que l'attaque touche)
	std::string Classe;      // Classe du personnage (joueur ou bot)
	int PV_initiaux;		 // PV max qui servent pour des tests

	struct action
	{
		std::string action_name; // Le nom
		std::string description; // Sa description
		bool avaible;            // Sa disponibilit�

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
		// Lambda servant pour les actions sur une entit� (en combat)

		std::function<bool(entity&, entity&, int&)> fonction_combat;
		void executer_fonction(entity& self, entity& adversaire, int& niveau)
		{
			fonction_combat(self, adversaire, niveau);
		}
		// Lambda servant � d�clencher un combat

		std::string classe;

		std::function<void(int&)> fonction_sauvegarde;
		void executer_fonction(int& niveau)
		{
			fonction_sauvegarde(niveau);
		}
		// Lambda servant � sauvegarder et charger la partie
	};
	// La structure d'une action

	std::vector<action> liste_actions; // Liste des action r�alisables par une entit�



	// Initialisation des variables
/*******************************************************************************************************************/

	void afficher_aide();          // Affiche les actions disponibles et leur description

	// Fonction servant � donner des informations � l'utilisateur
/*******************************************************************************************************************/

	bool test_mort();              // Teste la mort d'une entit�

	void message_mort();           // Affiche un message si le joueur est mort

	void remise_a_zero_des_PV();   // Emp�che les PV d'�tre n�gatifs

	void fonction_mort();          // Regroupe toutes les fonctions pr�c�dentes en une pour toutes les ex�cuter


	// Fonctions g�rant la mort du personnage
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
	// Ex�cute afficher_aide

	void assaut(entity& cible);
	// Fonction g�rant l'attaque sur une entit�

	void assaut_renforce(entity& cible);
	// Fonction g�rant le sp�cial de l'entit� Philippe

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
	// Structure g�rant l'attaque de base des entit�s

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
			std::cout << "Sauvegarde charg�e avec succ�s !" << std::endl;
		}
	};
	// Structure g�rant la recharge de la sauvegarde en lisant dans le fichier .txt de sauvegarde

	action combattre
	{
		"combattre",
		"D�marrer un combat",
		true,
		nullptr,
		nullptr,
		nullptr,
		"menu"
	};

	action defense
	{
		"d�fense",
		"Augmente la d�fense",
		false,
		[&]() { DEF += DEF; std::cout << "D�fense augment�e : " << DEF << std::endl; },
		nullptr,
		nullptr,
		"combat"
	};
	// Structure servant � augmenter la d�fense d'une entit�

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
	// Structure servant � quitter le programme en affichant un message avant la fermeture

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

			std::cout << "Partie sauvegard�e avec succ�s !" << std::endl;
		}
	};
	// Structure g�rant la recharge de la sauvegarde en �crivant dans le fichier .txt de sauvegarde

	action special
	{
		"sp�cial",
		"Permet d'utiliser la capacit� sp�ciale du joueur",
		false,
		nullptr,
		nullptr,
		nullptr,
		"combat"
	};
	// Structure g�rant le sp�cial d'une entit�


	// Fonctions g�rant les diff�rentes actions d'une entit�
/*******************************************************************************************************************/

	std::string choix_actions_menu(entity& joueur, std::vector<entity>& ennemi, int& niveau); // Fonction g�rant le menu principal

	std::string comportement();																  // Fonction g�rant l'IA des bots

	void choix_actions_combat(entity& cible);												  // Fonction g�rant le menu dans un combat

	void fonction_a_moi_de_jouer(entity& cible);											  // G�re le tour d'un joueur


	// Fonctions g�rant le tour d'une entit�
/*******************************************************************************************************************/
};

#endif // STRUCTURE_ENTITY_HPP