#include <iostream>				// Pour les entr�es-sorties consoles
#include <string>				// Pour les cha�nes de caract�res
#include <vector>				// Pour les tableaux dynamiques
#include <limits>				// Pour utiliser les limites des flux
#include <thread>				// Pour les pauses
#include <chrono>				// dans le programme
#include <algorithm>			// Pour les algorithmes
#include <functional>			// Pour d�finir des lambdas
#include <fstream>
#include "Entree_securisee.hpp" // Pour inclure le fichier d'en-t�te "Entree_securisee.hpp"
#include "Gestion_des_tours.hpp"// --------------------------------- "Gestion_des_tours.hpp"
#include "Structure_entity.hpp" // --------------------------------- "Structure_entity.hpp"
#include "Fonction_combat.hpp"  // --------------------------------- "Fonction_combat.hpp"


// Initialisation des biblioth�ques

int main() // D�but du programme
{


	/******************************************************************************************************************/


	entity joueur
	{
		/*Nom du personnage*/					"Philippe",
		/*Points de vie du personnage*/		    100,
		/*Attaque du personnage*/				20,
		/*Vitesse du personnage*/				50,
		/*D�fense du personnage*/				5,
		/*Pr�cision du personnage*/				100,
		/*R�le du personnage*/                  "joueur",
		/*Points de vie du personnage*/		    100
	};

	joueur.liste_actions.push_back(joueur.aide);
	joueur.liste_actions.push_back(joueur.combattre);
	joueur.liste_actions.back().fonction_combat = [&](entity& self, entity& adversaire, int& niveau) -> bool { return combat(self, adversaire, niveau); };
	joueur.liste_actions.push_back(joueur.quitter);
	joueur.liste_actions.push_back(joueur.sauvegarder);
	joueur.liste_actions.push_back(joueur.charger);
	joueur.liste_actions.push_back(joueur.attaquer);
	joueur.liste_actions.push_back(joueur.defense);
	joueur.liste_actions.push_back(joueur.special);
	joueur.liste_actions.back().description = "Grenade : Inflige le double de d�g�ts mais a une pr�cision moindre (75%)";
	joueur.liste_actions.back().fonction_entite = [&](entity& adversaire) { joueur.assaut_renforce(adversaire); };
	// Ajout des diff�rentes actions

	entity ennemi_0
	{
		/*Nom du personnage*/			"Roger",
		/*Points de vie du personnage*/ 50,
		/*Attaque du personnage*/		15,
		/*Vitesse du personnage*/		100,
		/*D�fense du personnage*/		5,
		/*Pr�cision du personnage*/		95,
		/*R�le du personnage*/          "bot",
		/*PV initiaux du personnage*/   50
	};

	ennemi_0.liste_actions.push_back(ennemi_0.attaquer);
	ennemi_0.liste_actions.push_back(ennemi_0.defense);
	ennemi_0.liste_actions.push_back(ennemi_0.special);
	ennemi_0.liste_actions.back().description = "Furie : Roger s'�nerve et augmente son attaque";
	ennemi_0.liste_actions.back().fonction_entite =
		[&](entity& adversaire)
		{
			ennemi_0.ATT *= 2;
			std::cout << "Attaque augment�e : " << ennemi_0.ATT << std::endl;
			ennemi_0.special.avaible = false;
		};

	entity ennemi_1
	{
		/*Nom du personnage*/			"R�mi",
		/*Points de vie du personnage*/ 65,
		/*Attaque du personnage*/		15,
		/*Vitesse du personnage*/		30,
		/*D�fense du personnage*/		2,
		/*Pr�cision du personnage*/		100,
		/*R�le du personnage*/          "bot",
		/*PV initiaux du personnage*/   65
	};

	ennemi_1.liste_actions.push_back(ennemi_1.attaquer);
	ennemi_1.liste_actions.push_back(ennemi_1.defense);
	ennemi_1.liste_actions.push_back(ennemi_1.special);
	ennemi_1.liste_actions.back().description = "Prudence : R�mi reste sur ses gardes et augmente sa d�fense pour �viter tout pistolet accroch� � un buisson";
	ennemi_1.liste_actions.back().fonction_entite =
		[&](entity& adversaire)
		{
			ennemi_1.DEF *= 2;
			std::cout << "D�fense augment�e : " << ennemi_1.DEF << std::endl;
			ennemi_1.special.avaible = false;
		};

	entity ennemi_2
	{
		/*Nom du personnage*/			"Blackie",
		/*Points de vie du personnage*/ 80,
		/*Attaque du personnage*/		15,
		/*Vitesse du personnage*/		50,
		/*D�fense du personnage*/		5,
		/*Pr�cision du personnage*/		100,
		/*R�le du personnage*/          "bot",
		/*PV initiaux du personnage*/   80
	};

	ennemi_2.liste_actions.push_back(ennemi_2.attaquer);
	ennemi_2.liste_actions.push_back(ennemi_2.defense);
	ennemi_2.liste_actions.push_back(ennemi_2.special);
	ennemi_2.liste_actions.back().description = "Camouflage : Blackie se cache afin de baisser la pr�cision de l'adversaire.";
	ennemi_2.liste_actions.back().fonction_entite =
		[&](entity& adversaire)
		{
			adversaire.PRECISION /= 2;
			if (adversaire.PRECISION < 40)
			{
				adversaire.PRECISION = 40;
			}
			std::cout << "Pr�cision baiss�e : " << adversaire.PRECISION << std::endl;
			ennemi_2.special.avaible = false;
		};

	entity ennemi_3
	{
		/*Nom du personnage*/			"Bob",
		/*Points de vie du personnage*/ 75,
		/*Attaque du personnage*/		30,
		/*Vitesse du personnage*/		50,
		/*D�fense du personnage*/		4,
		/*Pr�cision du personnage*/		95,
		/*R�le du personnage*/          "bot",
		/*PV initiaux du personnage*/   95
	};

	ennemi_3.liste_actions.push_back(ennemi_3.attaquer);
	ennemi_3.liste_actions.push_back(ennemi_3.defense);
	ennemi_3.liste_actions.push_back(ennemi_3.special);
	ennemi_3.liste_actions.back().description = "Grouille-toi : Bob doit rapidement aller chercher Mike et augmente sa vitesse.";
	ennemi_3.liste_actions.back().fonction_entite =
		[&](entity& adversaire)
		{
			ennemi_3.SPEED *= 2;
			std::cout << "Vitesse augment�e : " << ennemi_3.SPEED << std::endl;
			ennemi_3.special.avaible = false;
		};

	entity ennemi_4
	{
		/*Nom du personnage*/			"Mike",
		/*Points de vie du personnage*/ 100,
		/*Attaque du personnage*/		25,
		/*Vitesse du personnage*/		50,
		/*D�fense du personnage*/		7,
		/*Pr�cision du personnage*/		100,
		/*R�le du personnage*/          "bot",
		/*PV initiaux du personnage*/   100
	};

	ennemi_4.liste_actions.push_back(ennemi_4.attaquer);
	ennemi_4.liste_actions.push_back(ennemi_4.defense);
	ennemi_4.liste_actions.push_back(ennemi_4.special);
	ennemi_4.liste_actions.back().description = "Provocation : PHILIPPE !!! VIENS ICI SALE ENCUL� !!!";
	ennemi_4.liste_actions.back().fonction_entite =
		[&](entity& adversaire)
		{
			ennemi_4.ATT += 5;
			ennemi_4.SPEED += 10;
			std::cout << "Attaque augment�e : " << ennemi_4.ATT << std::endl;
			std::cout << "Vitesse augment�e : " << ennemi_4.SPEED << std::endl;
			ennemi_4.special.avaible = false;
		};

	entity vide{};

	std::vector<entity> liste_ennemis{ ennemi_0, ennemi_1, ennemi_2, ennemi_3, ennemi_4, vide };
	// La liste des ennemis


	// Initialisation des joueurs
	/******************************************************************************************************************/


	std::chrono::milliseconds pause(500);


	// Initialisation des variables
	/******************************************************************************************************************/


	int niveau{ 0 };
	while (joueur.choix_actions_menu(joueur, liste_ennemis, niveau) != "quitter");
	{
		std::this_thread::sleep_for(pause);
	}

	// Initialisation de la boucle de jeu

	return 0;
}