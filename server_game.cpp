// Copyright 2023 Cbravor@fi.uba.ar

#include "server_game.h"

#include <algorithm>
#include <fstream>


// Constructor de la clase Game
Game::Game(const std::string& nombre_archivo): nombre_archivo(nombre_archivo), map() {}


void Game::iniciar_partida() { map.cargar_datos_de_mapas_recibidos(nombre_archivo); }

std::uint8_t Game::buscar_mapa(const std::string& nombre_mapa) {
    map.cargar_nombre_del_mapa(nombre_mapa);

    return (map.validar_mapa(nombre_mapa, pos_x, pos_y));
}

int Game::obtener_posicion_X() { return pos_x; }

int Game::obtener_posicion_Y() { return pos_y; }


void Game::carga_de_direccion(const std::uint8_t& direccionRecibida) {

    direccion = direccionRecibida;
}

void Game::carga_tipo_de_salto(const std::uint8_t& saltoRecibido) { salto = saltoRecibido; }

bool Game::ejecutar_movimiento_vertical() {
    // Dependiendo de la dirección del salto, aumentaremos o disminuiremos la posición vertical

    if (salto == 0) {


        int posiblePosicion = pos_y - 1;
        bool posicionValida = map.verificar_posicion_valida(pos_x, posiblePosicion);
        if (posicionValida == true) {
            pos_y = posiblePosicion;
            return true;
        } else {
            return false;
        }
    } else if (salto == 1) {
        // Saltar un lugar
        int posicionAntesDelSalto = pos_y;
        int posiblePosicion = pos_y - 1;
        bool posicionValida;
        posicionValida = map.verificar_posicion_valida(pos_x, posiblePosicion);
        if (posicionValida == true) {
            // Saltar el lugar
            pos_y = posiblePosicion;

            // Otro lugar
            posicionValida = map.verificar_posicion_valida(pos_x, pos_y - 1);
            if (posicionValida == false) {
                pos_y = posicionAntesDelSalto;
                return false;
            } else {
                pos_y = pos_y - 1;
                return true;
            }
        }
    }
    return false;
}


void Game::ejecutar_gravedad() {
    bool columna;
    // si verificar_posicion_valida es false entonces habra un columna sobre
    // la cual el gusano podra posarse
    columna = map.verificar_posicion_valida(pos_x, pos_y + 1);
    while (columna == true) {
        pos_y = pos_y + 1;
        columna = map.verificar_posicion_valida(pos_x, pos_y + 1);
    }
}


void Game::ejecutar_salto() {
    // verificar posicion a medida que mueve si hay una X no se mueve y debemos obtener su posicion

    bool saltoValido;
    if (salto == 0) {

        saltoValido = ejecutar_movimiento_vertical();
        if (saltoValido == true) {
            if (direccion == 1) {
                mover_gusano_derecha();
                mover_gusano_derecha();
                ejecutar_gravedad();
            } else if (direccion == 0) {
                mover_gusano_izquierda();
                mover_gusano_izquierda();
                ejecutar_gravedad();
            }
        }
    } else if (salto == 1) {
        saltoValido = ejecutar_movimiento_vertical();

        if (saltoValido == true) {
            if (direccion == 1) {
                mover_gusano_izquierda();
                ejecutar_gravedad();


            } else if (direccion == 0) {
                mover_gusano_derecha();
                ejecutar_gravedad();
            }
        }
    }
}

void Game::mover_gusano_derecha() {


    int posiblePosicion = pos_x + 1;
    bool posicionValida = map.verificar_posicion_valida(posiblePosicion, pos_y);
    if (posicionValida == true) {
        pos_x = posiblePosicion;
    }
}


void Game::mover_gusano_izquierda() {


    int posiblePosicion = pos_x - 1;

    bool posicionValida = map.verificar_posicion_valida(posiblePosicion, pos_y);
    if (posicionValida == true) {
        pos_x = posiblePosicion;
    }
}


void Game::ejecutar_movimiento_horizontal() {
    // depende para donde mire vamos a aumentar o disminuir un movimiento 01 derecha

    if (direccion == 1) {


        mover_gusano_derecha();
        ejecutar_gravedad();

    } else if (direccion == 00) {

        mover_gusano_izquierda();
        ejecutar_gravedad();
    }
}
