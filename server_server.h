// "Copyright 2023 cbravor@fi.uba.ar

#ifndef SERVER_H_
#define SERVER_H_

#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "common_socket.h"
#include "common_state_game.h"
#include "server_game.h"
#include "server_protocol.h"

class Server {
private:
    Socket peer_skt;
    StateGame stateGame;
    Game game;
    std::uint8_t ultimaAccionRecibida;
    uint8_t existenciaDelMapa;
    static const uint8_t SELECT = 1;
    static const uint8_t DIR = 3;
    static const uint8_t MOVE = 4;
    static const uint8_t JUMP = 5;
    static const std::uint8_t MAPA_CARGADO = 00;
    static const std::uint8_t MAPA_NO_HALLADO = 01;


    /**
     * Envia un mensaje al cliente en respuesta a la última acción recibida por el servidor.
     * La respuesta varía según la acción, incluyendo información sobre la existencia de un mapa
     * y la posición actual del juego. Además, realiza impresiones en la salida estándar en algunos
     * casos dependiendo de los metodos de enviar a los que va a llamar.
     *
     * serverProtocol  Una instancia del protocolo del servidor para la comunicación.
     * skt_peer        El socket del cliente al cual se envía el mensaje.
     */


    void enviar_mensaje(ServerProtocol& ServerProtocol, Socket& skt_peer);

    /*
     * Acepta una conexión entrante y devuelve un nuevo socket que representa la conexión
     * establecida con el cliente.
     *
     * retorna un objeto Socket que representa la conexión con el cliente aceptado.
     */

    Socket accept();
    /*
     * Envia un mensaje al cliente indicando que se encontró el mapa seleccionado, junto con la
     * posición actual del juego e imprime la posicion actual por salida standar. serverProtocol:
     * Una instancia del protocolo del servidor para la comunicación. skt_peer: el socket del
     * cliente al cual se envía el mensaje.
     */
    void enviar_mensaje_accion_select_mapa_encontrado(ServerProtocol& serverProtocol,
                                                      Socket& skt_peer);
    /*
     * Envia un mensaje al cliente indicando que el mapa seleccionado no fue encontrado.
     *
     * serverProtocol: una instancia del protocolo del servidor para la comunicación.
     * skt_peer: el socket del cliente al cual se envía el mensaje.
     */
    void enviar_mensaje_accion_select_mapa_no_encontrado(ServerProtocol& serverProtocol,
                                                         Socket& skt_peer);
    /*
     * Envia un mensaje al cliente con la posición actual del juego luego de realizar una acción de
     * salto o dirección. Además, imprime la posición actual del juego en la salida estándar.
     *
     * serverProtocol: una instancia del protocolo del servidor para la comunicación.
     * skt_peer: el socket del cliente al cual se envía el mensaje.
     */
    void enviar_mensaje_accion_jump_o_dir(ServerProtocol& serverProtocol, Socket& skt_peer);

    /*
     * Envia un mensaje al cliente con la posición actual del juego después de realizar una acción
     * de movimiento. Además, imprime la posición actual del juego en la salida estándar.
     *
     * serverProtocol: Una instancia del protocolo del servidor para la comunicación.
     * skt_peer: El socket del cliente al cual se envía el mensaje.
     */
    void enviar_mensaje_accion_move(ServerProtocol& serverProtocol, Socket& skt_peer);
    /**
     * Ejecuta una acción de movimiento "move" en el juego, realizando un movimiento horizontal.
     */
    void ejecutar_accion_move();


    /*
     * Recibe y procesa un mensaje de acción "jump" del cliente, cargando el tipo de salto y
     * ejecutando el salto en el juego.
     *
     * server_vivo: Un puntero a una variable que indica si el servidor está vivo o no.
     * serverProtocol: Una instancia del protocolo del servidor para la comunicación.
     * skt_peer: el socket del cliente desde el cual se recibe el mensaje.
     */


    void recibir_mensaje_accion_jump(bool* server_vivo, ServerProtocol& ServerProtocol,
                                     Socket& skt_peer);

    /*
     * Recibe y procesa un mensaje de acción de dirección "dir" del cliente, cargando la dirección
     * en el juego.
     *
     * server_vivo: Un puntero a una variable que indica si el servidor está vivo o no.
     * serverProtocol: Una instancia del protocolo del servidor para la comunicación.
     * skt_peer: El socket del cliente desde el cual se recibe el mensaje.
     */

    void recibir_mensaje_accion_dir(bool* server_vivo, ServerProtocol& ServerProtocol,
                                    Socket& skt_peer);
    /*
     * Recibe y procesa un mensaje de acción "select" del cliente, determinando la existencia del
     * mapa seleccionado en el juego.
     *
     * server_vivo: Un puntero a una variable que indica si el servidor está vivo o no.
     * serverProtocol: Una instancia del protocolo del servidor para la comunicación.
     * skt_peer: El socket del cliente desde el cual se recibe el mensaje.
     */
    void recibir_mensaje_accion_select(bool* server_vivo, ServerProtocol& ServerProtocol,
                                       Socket& skt_peer);
    /*
     * Recibe y procesa un mensaje del cliente, determinando la acción solicitada y a partir de eso
     * determina que tipo de mensajes se recibiran
     *
     * server_vivo: Un puntero a una variable que indica si el servidor está vivo o no.
     * serverProtocol: Una instancia del protocolo del servidor para la comunicación.
     * skt_peer: El socket del cliente desde el cual se recibe el mensaje.
     */

    void recibir_mensaje(bool* server_vivo, ServerProtocol& serverProtocol, Socket& skt_peer);


public:
    /*
     * Constructor del ServerProtocol recibe el nombre del servidor

     */
    Server(const char* servname, const std::string& nombre_archivo);


    /*
     * Inicia la comunicación con un cliente aceptado, gestionando la recepción y envío de mensajes
     utilizando el protocolo del servidor a través del socket del cliente.
     *
     * retorn Un valor entero que indica el estado de la operación (0 si se completó la misma).
     */
    int iniciarComunicacion();


    /*
     * Deshabilito copias
     */
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
};

#endif
