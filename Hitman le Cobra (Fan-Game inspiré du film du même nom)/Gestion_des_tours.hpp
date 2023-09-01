#ifndef GESTION_DES_TOURS_HPP
#define GESTION_DES_TOURS_HPP
#include <thread>
#include <chrono>

void compte_tours(int& tour_actuel); // Ajoute un tour en combat

void afficher_tours(int& tour);      // Affiche le tour actuel

void fonction_tours(int& tour);      // Exécute les deux fonctions en une

#endif // GESTION_DES_TOURS_HPP