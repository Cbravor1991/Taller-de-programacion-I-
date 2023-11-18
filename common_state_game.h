// Copyright 2023 Cbravor@fi.uba.ar

#ifndef StateGame_H
#define StateGame_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "common_liberror.h"
#include "server_game.h"

class StateGame {

public:
    StateGame();

    /*
     * Imprime la posición actual del juego en las coordenadas especificadas en la salida estándar.
     * pos_x   La coordenada X de la posición actual del juego.
     * pos_y   La coordenada Y de la posición actual del juego.
     */
    void imprimir_posicion_actual(const std::uint32_t& pos_x, const std::uint32_t& pos_y);

    /*
     * Imprime un mensaje que indica un fallo en la salida estándar.
     */

    void imprimir_falla();
};


#endif
