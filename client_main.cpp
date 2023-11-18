// Copyright 2023 Cbravor@fi.uba.ar
#include <fstream>
#include <iostream>
#include <string>

#include "client_client.h"
#include "client_protocol.h"

int main(int argc, char* argv[]) {

    try {
        if (argc == 3) {
            Client client(argv[1], argv[2]);
            client.iniciar();

            return 0;
        } else {
            std::cerr << "Bad program call. Expected " << argv[0]
                      << "<ip/hostname server> <puerto/servicename\n";
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
