// "Copyright 2023 cbravor@fi.uba.ar

#ifndef CLIENT_H_
#define CLIENT_H_

#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "client_protocol.h"
#include "common_socket.h"
#include "common_state_game.h"


class Client {
private:
    std::uint32_t posicionXEndianess;
    std::uint32_t posicionYEndianess;
    std::map<std::string, uint8_t> acciones;
    std::map<std::string, uint16_t> tamanioMapa;
    std::map<std::string, uint8_t> direccionSeleccionada;
    std::map<std::string, uint8_t> saltoSeleccionado;
    std::string nombre_archivo;
    ClientProtocol clientProtocol;
    StateGame stateGame;
    static const bool MAPA_ENCONTRADO = true;
    static const bool MAPA_NO_ENCONTRADO = false;


    /*
     * Envía un mensaje de acción "select" al servidor con los comandos proporcionados por el
     * usuario.
     * El vector comandos contiene los comandos de la acción "select" ingresados por el usuario.
     * El vector debe contener dos elementos: el primer elemento es el comando
     * "select" y el segundo elemento el nombre del mapa.
     */
    void enviar_mensaje_accion_select(const std::vector<std::string>& comandos);

    /*
     * Envía un mensaje de acción "jump" o "dir" al servidor con los comandos proporcionados por el
     * usuario.
     *El vector comandos contiene los comandos de la acción "jump" o "dir" ingresados por el
     * usuario. El vector debe contener dos elementos: el primer elemento es el comando "jump" o
     * "dir" y el segundo elemento es la dirección(sea un movimiento a la izquierda o derecha o un
     * salto hacia delante o atras)  seleccionada.
     */
    void enviar_mensaje_accion_jump_o_dir(const std::vector<std::string>& comandos);
    /*
     * Envía un mensaje de acción "move" al servidor con el comando proporcionado por el usuario.
     * El vector comandos contiene los comandos de la acción "jump" o "dir" ingresados por el
     * usuario. El vector debe contener un solo elemento que es el comando "move".
     */
    void enviar_mensaje_accion_move(const std::vector<std::string>& comandos);


    /*
     * Recibe y procesa un mensaje relacionado con la acción "jump", "dir", o "move" del servidor,
     * actualizando las coordenadas de posición del cliente, el procedimiento espera recibir las
     * coordenadas X e Y en formato de 4 bytes cada una.
     */

    void recibir_mensaje_accion_jump_dir_move();

    /*
     * Recibe y procesa un mensaje relacionado con la acción "select" del servidor, actualizando las
     * coordenadas de posición que luego se imprimiran, si el mapa es encontrado.
     *
     * Si el mapa no es encontrado, se
     * devuelve false (MAPA_NO_ENCONTRADO), de lo contrario, se devuelve true (MAPA_ENCONTRADO).
     *
     */
    bool recibir_mensaje_accion_select();


public:
    /*
     * Constructor de la clase Client que inicializa una instancia del cliente y establece la
     * conexión con un servidor remoto utilizando el nombre del host y el nombre del servicio
     * proporcionados.
     *
     * hostname    El nombre del host al que se va a conectar el cliente.
     * servname    El nombre del servicio o puerto al que se va a conectar el cliente.
     */
    Client(const char* hostname, const char* servname);
    /*
     * Procesa comandos ingresados por el usuario desde la entrada estándar (stdin).
     * Dependiendo del comando recibido, este método realiza acciones específicas, envía y recibe
     * mensajes relacionados con el juego, y finalmente imprime el estado del juego en función de
     * las acciones realizadas. retorna 0 si la operación se realiza con éxito, 1 si no se puede
     * abrir la entrada estándar como un archivo.
     */

    int iniciar();


    /*
     * Deshabilito copias
     */
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;
};

#endif
