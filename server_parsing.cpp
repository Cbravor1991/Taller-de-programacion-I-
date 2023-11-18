// Copyright 2023 Cbravor@fi.uba.ar

#include "server_parsing.h"

#include <algorithm>
#include <fstream>

/*
 * Constructor de la clase Parsing que inicializa una instancia para procesar datos de mapas.
 */
Parsing::Parsing() {}

std::map<std::string, std::vector<std::pair<int, int>>> Parsing::obtener_datos_mapa(
        const std::string& nombre_archivo, const char& dato_buscado) {
    std::ifstream input(nombre_archivo);
    std::string linea;
    std::string nombre_mapa;
    std::vector<std::pair<int, int>> posiciones_dato_buscado;
    std::map<std::string, std::vector<std::pair<int, int>>> posiciones_datos;
    std::string::size_type ancho = 0;

    if (!input.is_open()) {
        exit(1);
    }


    int fila = 0;


    while (std::getline(input, linea)) {
        if (linea.empty()) {

            continue;
        }

        if (linea[0] == 'X') {

            for (std::string::size_type columna = 0; columna < ancho; ++columna) {
                if (linea[columna] == dato_buscado) {
                    posiciones_dato_buscado.emplace_back(columna,
                                                         fila - 1);  // Restamos 1 a la columna
                }
            }
        } else {

            if (!nombre_mapa.empty()) {

                posiciones_datos[nombre_mapa] = posiciones_dato_buscado;

                posiciones_dato_buscado.clear();
            }


            linea.erase(std::remove_if(linea.begin(), linea.end(), ::isspace), linea.end());
            nombre_mapa = linea.substr(2);
            ancho = std::stoi(linea.substr(0, 1));

            fila = 0;
        }

        ++fila;
    }


    if (!nombre_mapa.empty()) {
        posiciones_datos[nombre_mapa] = posiciones_dato_buscado;
        posiciones_dato_buscado.clear();
    }

    input.close();

    return posiciones_datos;
}
