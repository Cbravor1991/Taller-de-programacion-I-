// "Copyright 2023 cbravor@fi.uba.ar


#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

#include "server_game.h"
#include "server_protocol.h"
#include "server_server.h"

int main(int argc, char* argv[]) {
    try {
        if (argc == 3) {
            if (!argv[2]) {
                return 1;
            }

            std::string servicename = std::string(argv[1]);
            std::string nombre_archivo = std::string(argv[2]);
            Server server(argv[1], argv[2]);
            server.iniciarComunicacion();
            return 0;
        } else {
            std::cerr << "Bad program call. Expected " << argv[0]
                      << "<puerto/servicename> <escenarios>\n";
            return 1;
        }
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return 1;
    } catch (...) {
        std::cerr << "Something went wrong and "
                     "an unknown exception was caught.\n";
        return 1;
    }
}
