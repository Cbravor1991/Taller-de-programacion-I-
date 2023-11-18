// Copyright 2023 cbravor@fi.uba.ar

#ifndef CLIENT_PROTOCOL_H_
#define CLIENT_PROTOCOL_H_

#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "common_socket.h"


class ClientProtocol {
private:
    Socket skt;


public:
    /*
     * Constructor de la clase ClientProtocol que inicializa una conexión de socket con el servidor
     *utilizando el nombre del host y el nombre del servicio proporcionados, y crea una instancia de
     *StateGame para gestionar el estado del juego.
     *
     *hostname: El nombre del host al que se va a
     *conectar el cliente.
     *servname: El nombre del servicio o puerto al que se va a conectar el
     *cliente.
     */
    ClientProtocol(const char* hostname, const char* servname);

    /*
     * Envía dos bytes de datos al servidor utilizando el socket.
     *
     * datosEnviar: Los datos de 16 bits que se desean enviar al servidor.
     * LibError: Si ocurre un error durante la transmisión, se lanza una excepción LibError.
     */
    void enviar_dos_bytes(const uint16_t& datosEnviar);

    /*
     * Envía un byte de datos al servidor utilizando el socket.
     *
     * datosEnviar: El byte de datos que se desea enviar al servidor.
     * LibError:Si ocurre un error durante la transmisión, se lanza una excepción LibError.
     */
    void enviar_un_byte(const uint8_t& datosEnviar);
    /*
     * Serializa un valor de 16 bits en un formato de 16 bits aplicando hthons
     *
     * datosEnviar: El valor de 16 bits que se desea serializar.
     * Retorna: El valor serializado en formato de 16 bits en orden de red.
     */
    uint16_t serializar_datos_dos_bytes(const uint16_t& datosEnviar);

    /**
     * Envía una cadena de caracteres al servidor utilizando socket.
     *
     * longitudString: La longitud de la cadena de caracteres a enviar (en formato de 16
     * bits).
     * nombre: La cadena de caracteres que se desea enviar al servidor.
     * LibError: Si ocurre un error durante la transmisión, se lanza una excepción LibError.
     */
    void enviar_string(const uint16_t& longitudMapa, const std::string& nombre);


    /*
     * Recibe y procesa un mensaje de 4 bytes del servidor
     *
     * Retorna: El valor de 32 bits recibido del servidor, deserializado en formato de
     * host (dependiendo de la arquitectura).
     * LibError: Si ocurre un error durante la recepción, se
     * lanza una excepción LibError.
     */
    uint32_t recibir_4_bytes();

    /*
     * Recibe y procesa un mensaje de 1 byte del servidor
     *
     * Retorna: El valor de 8 bits recibido del servidor.
     * LibError: Si ocurre un error durante la recepción, se lanza una excepción LibError.
     */
    uint8_t recibir_1_byte();

    /*
     * Deserializa un valor de 32 bits recibido en un formato de 32 bits utilizando ntohl
     *
     * datosRecibidos: El valor de 32 bits recibido.
     * Retorna: El valor deserializado aplicando ntohl en formato de host.
     */
    uint32_t deserializacion_datos_cuatro_bytes(const uint32_t& datosRecibidos);


    /*
     * Deshabilito copias
     */
    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;
};

#endif
