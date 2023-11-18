// Copyright 2023 Cbravor@fi.uba.ar

#include "client_protocol.h"

#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <utility>
#include <valarray>
#include <vector>

#include <netinet/in.h>

#include "common_liberror.h"
#include "common_state_game.h"


ClientProtocol::ClientProtocol(const char* hostname, const char* servname):
        skt(hostname, servname)


{}


void ClientProtocol::enviar_un_byte(const uint8_t& datosEnviar) {
    bool was_closed = false;
    int bytes_enviar = 1;
    skt.sendall(&datosEnviar, bytes_enviar, &was_closed);

    if (was_closed) {
        throw LibError(errno, "No se pudo enviar el mensaje al cliente de un byte\n");
    }
}

void ClientProtocol::enviar_dos_bytes(const uint16_t& datosEnviar) {
    bool was_closed = false;
    int bytes_enviar = 2;
    uint16_t datosSerializados = serializar_datos_dos_bytes(datosEnviar);
    skt.sendall(&datosSerializados, bytes_enviar, &was_closed);

    if (was_closed) {
        throw LibError(errno, "No se pudo enviar dos bytes al servidor\n");
    }
}


uint16_t ClientProtocol::serializar_datos_dos_bytes(const uint16_t& datosEnviar) {
    return (htons(datosEnviar));
}


void ClientProtocol::enviar_string(const uint16_t& longitudString, const std::string& nombre) {
    bool was_closed = false;


    int tamanio_en_bytes_int = static_cast<int>(longitudString);

    skt.sendall(nombre.c_str(), tamanio_en_bytes_int, &was_closed);

    if (was_closed) {
        throw LibError(errno, "No se pudo enviar el mensaje el nombre del mapa al servidor\n");
    }
}


uint32_t ClientProtocol::recibir_4_bytes() {
    bool was_closed = false;
    int cant_bytes_recibidos = 4;
    uint32_t datosRecibidos = 0;
    skt.recvall(&datosRecibidos, cant_bytes_recibidos, &was_closed);
    if (was_closed) {
        throw LibError(errno, "No se pudo recibir el mensaje del servidor 4 bytes\n");
    }


    return deserializacion_datos_cuatro_bytes(datosRecibidos);
}
uint8_t ClientProtocol::recibir_1_byte() {
    bool was_closed = false;
    int cant_bytes_recibidos = 1;
    uint8_t datosRecibidos = 0;
    skt.recvall(&datosRecibidos, cant_bytes_recibidos, &was_closed);
    if (was_closed) {
        throw LibError(errno, "No se pudo recibir el mensaje del servidor 1 bytes\n");
    }

    return datosRecibidos;
}

uint32_t ClientProtocol::deserializacion_datos_cuatro_bytes(const uint32_t& datosRecibidos) {
    return (ntohl(datosRecibidos));
}
