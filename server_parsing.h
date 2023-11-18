// Copyright 2023 Cbravor@fi.uba.ar

#ifndef Parsing_H
#define Parsing_H

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "common_liberror.h"


class Parsing {
private:
public:
    Parsing();

    /*
     * Lee un archivo de datos del mapa y obtiene información sobre las posiciones de un dato
     * buscado ('X' o 'G') en el mapa.
     *
     * nombre_archivo: El nombre del archivo que contiene los datos del mapa.
     * dato_buscado: El dato que se desea buscar en el mapa ('X' para paredes, 'G' para gusanos).
     * retorna: Un map que asocia el nombre del mapa con las posiciones del dato buscado en dicho
     * mapa. Cada entrada del mapa contiene un vector de pares (columna, fila) con las posiciones
     * encontradas.
     */
    std::map<std::string, std::vector<std::pair<int, int>>> obtener_datos_mapa(
            const std::string& nombre_archivo, const char& dato_buscado);
};


#endif
