// Copyright 2023 Cbravor@fi.uba.ar

#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "common_liberror.h"
#include "server_parsing.h"

class Map {

private:
    Parsing parsing;
    std::map<std::string, std::vector<std::pair<int, int>>> posiciones_pared;
    std::map<std::string, std::vector<std::pair<int, int>>> posiciones_inicial_gusanos;
    std::string nombre_mapa_partida_actual;
    std::uint8_t estadoCargaMapa = 00;


    static const std::uint8_t MAPA_CARGADO = 00;
    static const std::uint8_t MAPA_NO_HALLADO = 01;

public:
    /**
     * Constructor de la clase Map que inicializa una instancia del mapa con estructuras de datos
     * vacías. Se utiliza para gestionar información sobre las posiciones de pared y las posiciones
     * iniciales de los gusanos,
     */
    Map();
    /*
     * Carga los datos de mapas recibidos desde un archivo especificado en las estructuras de
     * posiciones de pared y posiciones iniciales de gusanos del mapa.
     *
     * nombre_archivo: El nombre del archivo que contiene los datos de los mapas a cargar.
     */
    void cargar_datos_de_mapas_recibidos(const std::string& nombre_archivo);

    /*
     * Valida si un mapa con el nombre especificado existe y establece la posición inicial del
     * gusano si es encontrado.
     *
     * nombreMapa: El nombre del mapa que se desea validar.
     * pos_x: se carga la posición inicial en el eje X del gusano si se encuentra el mapa.
     * pos_y : se carga la posición inicial en el eje Y del gusano si se encuentra el mapa.
     * retorna un valor de 8 bits que indica el estado de carga del mapa: MAPA_CARGADO si se
     * encuentra, MAPA_NO_HALLADO si no se encuentra.
     */
    std::uint8_t validar_mapa(const std::string& nombreMapa, int& pos_x, int& pos_y);
    /*
     * Carga el nombre del mapa de la partida actual con el nombre especificado.
     *
     * nombreMapa: el nombre del mapa que se desea cargar para la partida actual.
     */

    void cargar_nombre_del_mapa(const std::string& nombreMapa);

    /*
     * Verifica si una posición (posicion_x, posicion_y) es válida en el mapa de la partida actual.
     *
     * posicion_x: La coordenada X de la posición que se desea verificar.
     * posicion_y: La coordenada Y de la posición que se desea verificar.
     * retorna true si la posición es válida y no corresponde a una pared, false si es una posición
     * de pared.
     */
    bool verificar_posicion_valida(const int& posicion_x, const int& posicion_y);
};


#endif
