#ifndef FONCTION_COMBAT_HPP
#define FONCTION_COMBAT_HPP

#include <thread>
#include <chrono>
#include "Structure_entity.hpp"
#include "Gestion_des_tours.hpp"

bool combat(entity& joueur, entity& ennemi, int& niveau); // Fonction g�rant un combat entre 2 entit�s

#endif // FONCTION_COMBAT_HPP