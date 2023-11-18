// Copyright 2023 cbravor@fi.uba.ar


#include "client_client.h"

#include <cstring>
#include <iostream>
#include <sstream>
#include <utility>
#include <valarray>
#include <vector>

#include <netinet/in.h>

#include "common_liberror.h"


Client::Client(const char* hostname, const char* servname):


        clientProtocol(hostname, servname), stateGame() {

    acciones["select"] = 01;
    acciones["dir"] = 03;
    acciones["move"] = 04;
    acciones["jump"] = 05;
    tamanioMapa["basic"] = 0005;
    tamanioMapa["nobasic"] = 0007;
    tamanioMapa["small"] = 0005;
    direccionSeleccionada["0"] = 00;
    direccionSeleccionada["1"] = 01;
    saltoSeleccionado["0"] = 00;
    saltoSeleccionado["1"] = 01;

    posicionXEndianess = 0;
    posicionYEndianess = 0;
}

int Client::iniciar() {

    std::string primerEntrada;
    std::string segundaEntrada;
    std::vector<std::string> comandos;

    // Abre std::cin como un flujo de archivo
    std::ifstream input_stream(
            "/dev/stdin");  // En sistemas Unix, "/dev/stdin" se refiere a la entrada estándar

    if (!input_stream) {
        std::cerr << "No se pudo abrir la entrada estándar como un archivo." << std::endl;
        return 1;
    }

    while (input_stream >> primerEntrada) {


        if (primerEntrada != "select" && primerEntrada != "dir" && primerEntrada != "move" &&
            primerEntrada != "jump" && primerEntrada != "#") {
            continue;
        }


        if (primerEntrada == "move") {
            comandos.clear();
            comandos.push_back(primerEntrada);
            enviar_mensaje_accion_move(comandos);
            recibir_mensaje_accion_jump_dir_move();
            stateGame.imprimir_posicion_actual(posicionXEndianess, posicionYEndianess);

        } else if (primerEntrada == "select") {
            comandos.clear();
            input_stream >> segundaEntrada;
            if (segundaEntrada == "basic" || segundaEntrada == "nobasic" ||
                segundaEntrada == "small") {
                comandos.push_back(primerEntrada);
                comandos.push_back(segundaEntrada);
                enviar_mensaje_accion_select(comandos);
                bool situacionMapa = recibir_mensaje_accion_select();
                if (situacionMapa == MAPA_ENCONTRADO) {

                    stateGame.imprimir_posicion_actual(posicionXEndianess, posicionYEndianess);
                } else if (situacionMapa == MAPA_NO_ENCONTRADO) {
                    stateGame.imprimir_falla();
                }
            }


        } else if (primerEntrada == "dir") {
            comandos.clear();
            input_stream >> segundaEntrada;
            if (segundaEntrada == "0" || segundaEntrada == "1") {
                comandos.push_back(primerEntrada);
                comandos.push_back(segundaEntrada);
                enviar_mensaje_accion_jump_o_dir(comandos);
                recibir_mensaje_accion_jump_dir_move();
                stateGame.imprimir_posicion_actual(posicionXEndianess, posicionYEndianess);
            }


        } else if (primerEntrada == "jump") {
            comandos.clear();
            input_stream >> segundaEntrada;
            comandos.push_back(primerEntrada);
            comandos.push_back(segundaEntrada);
            if (segundaEntrada == "0" || segundaEntrada == "1") {
                comandos.push_back(primerEntrada);
                comandos.push_back(segundaEntrada);
                enviar_mensaje_accion_jump_o_dir(comandos);
                recibir_mensaje_accion_jump_dir_move();
                stateGame.imprimir_posicion_actual(posicionXEndianess, posicionYEndianess);
            }
        }
    }
    input_stream.close();


    return 0;
}

void Client::enviar_mensaje_accion_select(const std::vector<std::string>& comandos) {

    clientProtocol.enviar_un_byte(acciones[comandos[0]]);
    clientProtocol.enviar_dos_bytes(tamanioMapa[comandos[1]]);
    clientProtocol.enviar_string(tamanioMapa[comandos[1]], comandos[1]);
}

void Client::enviar_mensaje_accion_jump_o_dir(const std::vector<std::string>& comandos) {

    clientProtocol.enviar_un_byte(acciones[comandos[0]]);
    clientProtocol.enviar_un_byte(direccionSeleccionada[comandos[1]]);
}

void Client::enviar_mensaje_accion_move(const std::vector<std::string>& comandos) {

    clientProtocol.enviar_un_byte(acciones[comandos[0]]);
}

void Client::recibir_mensaje_accion_jump_dir_move() {
    posicionXEndianess = clientProtocol.recibir_4_bytes();
    posicionYEndianess = clientProtocol.recibir_4_bytes();
}


bool Client::recibir_mensaje_accion_select() {
    uint8_t validacionMapa = clientProtocol.recibir_1_byte();
    if (validacionMapa == 0) {
        posicionXEndianess = clientProtocol.recibir_4_bytes();
        posicionYEndianess = clientProtocol.recibir_4_bytes();
    } else if (validacionMapa == 1) {

        return MAPA_NO_ENCONTRADO;
    }


    return MAPA_ENCONTRADO;
}
