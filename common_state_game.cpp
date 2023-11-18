// Copyright 2023 Cbravor@fi.uba.ar

#include "common_state_game.h"

#include <algorithm>
#include <fstream>


// Constructor de la clase StateGame
StateGame::StateGame() {}
void StateGame::imprimir_posicion_actual(const std::uint32_t& pos_x, const std::uint32_t& pos_y) {


    std::cout << pos_x << " " << pos_y << "\n";
}

void StateGame::imprimir_falla() { std::cout << "Fallo"; }
