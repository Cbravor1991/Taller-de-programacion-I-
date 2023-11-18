// Copyright 2023 Cbravor@fi.uba.ar

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "common_liberror.h"
#include "server_map.h"

class Game {
private:
    std::string nombre_archivo;
    std::string nombre_mapa_partida_actual;
    Map map;


    std::uint8_t direccion = 0;
    std::uint8_t salto = 0;
    int pos_x = 0;
    int pos_y = 0;

    /*
     * Mueve el gusano hacia la izquierda en el juego, si la nueva posición es válida en el mapa.
     * Si la nueva posición es válida, actualiza la posición del gusano en el eje X.
     */

    void mover_gusano_izquierda();

    /*
     * Aplica la gravedad al gusano en el juego, haciendo que caiga hasta encontrar una columna
     * sólida en la posición actual. El procedimiento verifica la validez de la posición debajo del
     * gusano y ajusta la posición vertical.
     */
    void ejecutar_gravedad();

    /*
     * Ejecuta un movimiento vertical en el juego según el tipo de salto definido.
     *
     * Si el tipo de salto es 0, el gusano intenta moverse hacia arriba una posición.
     * Si el tipo de salto es 1, el gusano intenta realizar un salto de dos posiciones hacia arriba.
     *
     * retorna un true si el movimiento vertical es válido es decir sino se encontro con ninguna
     * pared y se realiza con éxito, false en caso contrario en ese caso no se realiza ninguna
     * accion el movimiento vertical se suspende.
     */
    bool ejecutar_movimiento_vertical();

    /*
     * Mueve el gusano hacia la derecha en el juego, si la nueva posición es válida en el mapa.
     * Si la nueva posición es válida, actualiza la posición del gusano en el eje X.
     */
    void mover_gusano_derecha();


public:
    /**
     * Constructor de la clase Game que inicializa una instancia del juego con un nombre de archivo
     * especificado.
     *
     * nombre_archivo: El nombre del archivo que contiene los datos de los escenarios.
     */
    explicit Game(const std::string& archivo);


    /*
     * Carga una dirección en el juego, utilizando el valor de dirección recibido como parámetro.
     *
     * direccion: El valor de dirección que se va a cargar en el juego.
     */

    void carga_de_direccion(const std::uint8_t& direccion);

    /*
     * Carga un tipo de salto en el juego, utilizando el valor de salto recibido como parámetro.
     *
     * saltoRecibido: El valor que representa el tipo de salto que se va a cargar en el juego.
     */
    void carga_tipo_de_salto(const std::uint8_t& saltoRecibido);

    /*
     * Ejecuta un movimiento horizontal del gusano en el juego, según la dirección actual.
     * Si la dirección es 01 (derecha), el gusano se mueve hacia la derecha.
     * Si la dirección es 00 (izquierda), el gusano se mueve hacia la izquierda.
     * Luego de ejecutar el movimiento, se aplica la gravedad.
     */
    void ejecutar_movimiento_horizontal();


    /*
     * Ejecuta un salto en el juego, primero realiza el movimiento vertical segun que tipo de salto
     *se haya ingresado por consola.
     * Si el salto es válido y el tipo de salto es 0 y la dirección es 1 (derecha), el gusano se
     * mueve hacia la derecha dos lugares y se ejecuta la gravedad. Si el salto es válido y el tipo
     *de saltos es 0 y la dirección es 0 (izquierda), el gusano se mueve hacia la izquierda dos
     *lugares y se ejecuta la gravedad. Si el salto no es valido se suspende el salto
     *
     * Si el salto es válido y el tipo de salto es 1 y la dirección es 0 (izquierda), el gusano se
     * mueve hacia la derecha y se aplica la gravedad. Si el salto es válido y el tipo de saltos es
     *1 y la dirección es 1 (derecha), el gusano se mueve hacia la izquierda y se aplica la
     *gravedad. Si el salto no es valido se suspende el salto
     */
    void ejecutar_salto();


    /**
     * Inicia una partida de juego cargando los datos de mapas recibidos desde un archivo
     * especificado.
     *
     * nombre_archivo El nombre del archivo que contiene los datos de mapas a cargar.
     */
    void iniciar_partida();

    /*
     * Busca el mapa ingresado por consola, pasa por parametros el nombre del mapa
     * y las pos_x, pos_y para que en caso de que el mapa exista se carguen en las mismas
     * las coordenadas iniciales del gusano.
     *
     *
     * nombre_mapa: El nombre del mapa que se desea buscar y validar.
     * retorna: Un valor de 8 bits que indica si el mapa es válido para la posición actual del
     * gusano. 1 si es válido, 0 si no es válido.
     */

    std::uint8_t buscar_mapa(const std::string& nombre_mapa);

    /*
     * Obtiene y devuelve la posición actual del gusano en el eje X en el juego.
     *
     * retorna La posición actual del gusano en el eje X.
     */

    int obtener_posicion_X();
    /*
     * Obtiene y devuelve la posición actual del gusano en el eje Y en el juego.
     *
     * retorna La posición actual del gusano en el eje y.
     */

    int obtener_posicion_Y();


    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
};

#endif
