// "Copyright 2023 cbravor@fi.uba.ar

#ifndef SERVER_PROTOCOL_H_
#define SERVER_PROTOCOL_H_

#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "common_socket.h"


class ServerProtocol {
private:
    std::uint8_t ultimaAccionRecibida;
    std::map<std::string, uint8_t> acciones;
    bool en_conexion;


public:
    /*
     * Constructor de la clase ServerProtocol que inicializa una instancia para manejar la
     * comunicación del servidor.
     */
    ServerProtocol();

    /*
     * Envía un valor de 32 bits (4 bytes) a traves del socket peer y verifica el estado del socket.
     *
     * datosEnviar el valor de las posiciones que voy a enviar.
     * skt_peer el socket a traves del cual se va a enviael valor de 32 bits.
     */
    void enviar_cuatro_bytes(const int& datosEnviar, Socket& skt_peer);

    /*
     * Envía un valor de 8 bits (1 byte) a traves socket peer y verifica el estado del socket.
     *
     * datosEnviar   El valor de 8 bits (1 byte) que se desea enviar.
     * skt_peer el socket a traves del cual se va a enviar el el valor de 8 bits (1 byte).
     */
    void enviar_un_byte(const uint8_t& datosEnviar, Socket& skt_peer);

    /*
     * Realiza la serialización de datos de 32 bits para asegurar el orden de bytes adecuado antes
     * de enviarlos, aplicando htonl.
     *
     * datosEnviar El valor de 32 bits que se desea serializar.
     * retorna el valor de 32 bits serializado con el orden de bytes ajustado.
     */
    uint32_t serializar_datos_cuatro_bytes(const uint32_t& datosEnviar);


    /*
     * Realiza la deserialización de datos de 16 bits recibidos, ajustando el orden de bytes
     aplicando la fucnion ntohs.
     *
     * datosRecibidos: El valor de 16 bits recibido que puede estar en formato de red o local.
     * retorna el valor de 16 bits deserializado con el orden de bytes ajustado.
     */
    uint16_t deserializacion_datos_dos_bytes(const uint16_t& datosRecibidos);

    /*
     * Recibe un valor de 16 bits (2 bytes) desde el socket peer y verifica el estado del socket.
     *
     * server_vivo un puntero a una variable que indica si el servidor está vivo o no.
     * skt_peer el socket desde el cual se va a recibir el valor de 16 bits.
     * retorna el valor de 16 bits recibido, con el orden de bytes ajustado .
     */
    uint16_t recibir_2_byte(bool* server_vivo, Socket& skt_peer);
    /**
     * Recibe un byte de datos desde el socket peer y verifica el estado del socket.
     *
     * server_vivo: Un puntero a una variable que indica si el servidor está vivo o no.
     * skt_peer: El socket desde el cual se va a recibir el byte de datos.
     * return  el byte de datos recibido.
     */
    uint8_t recibir_1_byte(bool* server_vivo, Socket& skt_peer);

    /*
     * Recibe un string de caracteres desde el socket peer con la longitud especificada y verifica
     * el estado del socket.
     *
     * tamanioString: la longitud del string que se va a recibir.
     * server_vivo: un puntero a una variable que indica si el servidor está vivo o no.
     * skt_peer: el socket desde el cual se va a recibir el string.
     * retorna: un vector de caracteres que representa el string recibido.
     */
    std::vector<char> recibir_string(const int& tamanioString, bool* server_vivo, Socket& skt_peer);


    /*
     * Verifica el estado del socket y actualiza la variable que indica si el servidor está vivo o
     * no.
     *
     * was_closed: Un valor booleano que indica si el socket ha sido cerrado.
     * server_vivo:  Un puntero a una variable que indica si el servidor está vivo o no.
     */
    void verificar_estado_socket(bool was_closed, bool* server_vivo);


    /*
     * Deshabilito copias
     */
    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;
};

#endif
