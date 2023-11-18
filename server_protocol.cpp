// Copyright 2023 cbravor@fi.uba.ar

#include "server_protocol.h"

#include <cstring>
#include <iostream>
#include <sstream>
#include <utility>
#include <valarray>
#include <vector>

#include <netinet/in.h>

#include "common_liberror.h"
#include "common_state_game.h"

ServerProtocol::ServerProtocol()


{
    en_conexion = true;
    ultimaAccionRecibida = 0;
    acciones["select"] = 01;
    acciones["dir"] = 03;
    acciones["move"] = 04;
    acciones["jump"] = 0x05;
}


uint8_t ServerProtocol::recibir_1_byte(bool* server_vivo, Socket& skt_peer) {
    bool was_closed = false;
    int cant_bytes_recibidos = 1;
    uint8_t datosRecibidos = 0;
    skt_peer.recvall(&datosRecibidos, cant_bytes_recibidos, &was_closed);
    verificar_estado_socket(was_closed, server_vivo);
    return datosRecibidos;
}

void ServerProtocol::verificar_estado_socket(bool was_closed, bool* server_vivo) {
    if (was_closed) {
        *server_vivo = false;
        return;
    }
}

uint16_t ServerProtocol::deserializacion_datos_dos_bytes(const uint16_t& datosRecibidos) {
    return (ntohs(datosRecibidos));
}

std::vector<char> ServerProtocol::recibir_string(const int& tamanioString, bool* server_vivo,
                                                 Socket& skt_peer) {
    bool was_closed = false;
    std::vector<char> buffer_nombre(tamanioString);
    skt_peer.recvall(buffer_nombre.data(), tamanioString, &was_closed);
    verificar_estado_socket(was_closed, server_vivo);
    return buffer_nombre;
}


uint16_t ServerProtocol::recibir_2_byte(bool* server_vivo, Socket& skt_peer) {
    bool was_closed = false;
    int cant_bytes_recibidos = 2;
    uint16_t datosRecibidos = 0;
    skt_peer.recvall(&datosRecibidos, cant_bytes_recibidos, &was_closed);
    verificar_estado_socket(was_closed, server_vivo);


    return deserializacion_datos_dos_bytes(datosRecibidos);
}


void ServerProtocol::enviar_cuatro_bytes(const int& datosEnviar, Socket& skt_peer) {
    bool was_closed = false;
    uint32_t dato_32_bits = static_cast<uint32_t>(datosEnviar);
    int bytes_enviar = 4;
    uint32_t datosSerializados = serializar_datos_cuatro_bytes(dato_32_bits);
    skt_peer.sendall(&datosSerializados, bytes_enviar, &was_closed);

    if (was_closed) {
        throw LibError(errno, "No se pudo recibir el mensaje del cliente cuatro bytes\n");
    }
}


void ServerProtocol::enviar_un_byte(const uint8_t& datosEnviar, Socket& skt_peer) {
    bool was_closed = false;
    int bytes_enviar = 1;
    skt_peer.sendall(&datosEnviar, bytes_enviar, &was_closed);

    if (was_closed) {
        throw LibError(errno, "No se pudo recibir el mensaje del cliente un bytes\n");
    }
}

uint32_t ServerProtocol::serializar_datos_cuatro_bytes(const uint32_t& datosEnviar) {
    return (htonl(datosEnviar));
}
