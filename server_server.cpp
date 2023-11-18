// Copyright 2023 cbravor@fi.uba.ar

#include "server_server.h"

#include <cstring>
#include <iostream>
#include <sstream>
#include <utility>
#include <valarray>
#include <vector>

#include <netinet/in.h>

#include "common_liberror.h"


Server::Server(const char* servname, const std::string& nombre_archivo_recibido):
        peer_skt(servname),
        stateGame(),
        game(nombre_archivo_recibido)

{
    ultimaAccionRecibida = 0;
    existenciaDelMapa = 0;
    game.iniciar_partida();
}


int Server::iniciarComunicacion() {


    Socket skt_cliente = this->accept();

    peer_skt = std::move(skt_cliente);
    ServerProtocol serverProtocol;
    bool en_conexion = true;
    while (en_conexion) {
        recibir_mensaje(&en_conexion, serverProtocol, peer_skt);
        if (!en_conexion)
            break;
        enviar_mensaje(serverProtocol, peer_skt);
    }
    return 0;
}


Socket Server::accept() { return peer_skt.accept(); }


void Server::ejecutar_accion_move() {
    ultimaAccionRecibida = MOVE;
    game.ejecutar_movimiento_horizontal();
}
void Server::recibir_mensaje_accion_dir(bool* server_vivo, ServerProtocol& serverProtocol,
                                        Socket& skt_peer) {
    ultimaAccionRecibida = DIR;
    uint8_t direccionRecibida = serverProtocol.recibir_1_byte(server_vivo, skt_peer);
    game.carga_de_direccion(direccionRecibida);
}

void Server::recibir_mensaje_accion_select(bool* server_vivo, ServerProtocol& serverProtocol,
                                           Socket& skt_peer) {
    ultimaAccionRecibida = SELECT;
    uint8_t tamanioMapaEndianness = serverProtocol.recibir_2_byte(server_vivo, skt_peer);
    int largoMapa = static_cast<int>(tamanioMapaEndianness);
    std::vector<char> buffer_nombre(largoMapa);
    buffer_nombre = serverProtocol.recibir_string(largoMapa, server_vivo, skt_peer);
    std::string nombre_mapa(buffer_nombre.begin(), buffer_nombre.end());
    existenciaDelMapa = game.buscar_mapa(nombre_mapa);
}

void Server::recibir_mensaje_accion_jump(bool* server_vivo, ServerProtocol& serverProtocol,
                                         Socket& skt_peer) {
    ultimaAccionRecibida = JUMP;
    uint8_t saltoRecibido = serverProtocol.recibir_1_byte(server_vivo, skt_peer);
    game.carga_tipo_de_salto(saltoRecibido);
    game.ejecutar_salto();
}


void Server::recibir_mensaje(bool* server_vivo, ServerProtocol& serverProtocol, Socket& skt_peer) {

    uint8_t accion = serverProtocol.recibir_1_byte(server_vivo, skt_peer);

    if (accion == SELECT) {

        recibir_mensaje_accion_select(server_vivo, serverProtocol, skt_peer);

    } else if (accion == DIR) {
        recibir_mensaje_accion_dir(server_vivo, serverProtocol, skt_peer);
    } else if (accion == MOVE) {
        ejecutar_accion_move();
    } else if (accion == JUMP) {
        recibir_mensaje_accion_jump(server_vivo, serverProtocol, skt_peer);
    }
}

void Server::enviar_mensaje_accion_select_mapa_encontrado(ServerProtocol& serverProtocol,
                                                          Socket& skt_peer) {
    serverProtocol.enviar_un_byte(existenciaDelMapa, skt_peer);
    serverProtocol.enviar_cuatro_bytes(game.obtener_posicion_X(), skt_peer);
    serverProtocol.enviar_cuatro_bytes(game.obtener_posicion_Y(), skt_peer);
    stateGame.imprimir_posicion_actual(game.obtener_posicion_X(), game.obtener_posicion_Y());
}

void Server::enviar_mensaje_accion_select_mapa_no_encontrado(ServerProtocol& serverProtocol,
                                                             Socket& skt_peer) {
    serverProtocol.enviar_un_byte(existenciaDelMapa, skt_peer);
}


void Server::enviar_mensaje_accion_jump_o_dir(ServerProtocol& serverProtocol, Socket& skt_peer) {
    serverProtocol.enviar_cuatro_bytes(game.obtener_posicion_X(), skt_peer);
    serverProtocol.enviar_cuatro_bytes(game.obtener_posicion_Y(), skt_peer);
    stateGame.imprimir_posicion_actual(game.obtener_posicion_X(), game.obtener_posicion_Y());
}
void Server::enviar_mensaje_accion_move(ServerProtocol& serverProtocol, Socket& skt_peer) {
    serverProtocol.enviar_cuatro_bytes(game.obtener_posicion_X(), skt_peer);
    serverProtocol.enviar_cuatro_bytes(game.obtener_posicion_Y(), skt_peer);

    stateGame.imprimir_posicion_actual(game.obtener_posicion_X(), game.obtener_posicion_Y());
}


void Server::enviar_mensaje(ServerProtocol& serverProtocol, Socket& skt_peer) {

    if (ultimaAccionRecibida == SELECT) {
        if (existenciaDelMapa == 0x00) {
            enviar_mensaje_accion_select_mapa_encontrado(serverProtocol, skt_peer);
        } else if (existenciaDelMapa == 0x01) {
            enviar_mensaje_accion_select_mapa_encontrado(serverProtocol, skt_peer);
        }
    }


    if (ultimaAccionRecibida == DIR) {
        enviar_mensaje_accion_jump_o_dir(serverProtocol, skt_peer);
    }

    if (ultimaAccionRecibida == MOVE) {
        enviar_mensaje_accion_move(serverProtocol, skt_peer);
    }

    if (ultimaAccionRecibida == JUMP) {


        enviar_mensaje_accion_jump_o_dir(serverProtocol, skt_peer);
    }
}
