// Copyright 2023 Cbravor@fi.uba.ar

#include "server_map.h"

#include <algorithm>
#include <fstream>


// Constructor de la clase StateGame
Map::Map():
        parsing(),
        posiciones_pared(),
        posiciones_inicial_gusanos()

{}
void Map::cargar_datos_de_mapas_recibidos(const std::string& nombre_archivo) {
    posiciones_pared = parsing.obtener_datos_mapa(nombre_archivo, 'X');
    posiciones_inicial_gusanos = parsing.obtener_datos_mapa(nombre_archivo, 'G');
}

std::uint8_t Map::validar_mapa(const std::string& nombreMapa, int& pos_x, int& pos_y) {
    auto it = posiciones_inicial_gusanos.find(nombreMapa);


    // Verificar si la clave se encontró.
    if (it != posiciones_inicial_gusanos.end()) {

        estadoCargaMapa = MAPA_CARGADO;
        if (!it->second.empty()) {
            pos_x = it->second[0].first;
            pos_y = it->second[0].second;
        }

        return MAPA_CARGADO;

    } else {
        estadoCargaMapa = MAPA_NO_HALLADO;
        return MAPA_NO_HALLADO;
    }
}


void Map::cargar_nombre_del_mapa(const std::string& nombreMapa) {
    nombre_mapa_partida_actual = nombreMapa;
}

bool Map::verificar_posicion_valida(const int& posicion_x, const int& posicion_y) {

    // Establecer la clave para buscar en el mapa (usando nombre_archivo en tu ejemplo).


    // Verificar si la clave se encuentra en el mapa.
    auto it = posiciones_pared.find(nombre_mapa_partida_actual);

    if (it != posiciones_pared.end()) {
        // La clave se encontró en el mapa, ahora verificamos si (posicion_x, posicion_y) está en el
        // vector.
        const std::vector<std::pair<int, int>>& vectorDePares = it->second;
        std::pair<int, int> parBuscado =
                std::make_pair(static_cast<int>(posicion_x), static_cast<int>(posicion_y));

        if (std::find(vectorDePares.begin(), vectorDePares.end(), parBuscado) !=
            vectorDePares.end()) {

            return false;
        } else {

            return true;
        }
    } else {
        // La clave no se encontró en el mapa, lo que podría indicar un error o una posición válida
        // por defecto.

        return true;  // Retorna true por defecto, pero puedes manejar esto de acuerdo a tu lógica.
    }
}
