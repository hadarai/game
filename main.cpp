

#include <iostream>
#include <fstream>
#include "game.hpp"

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        std::cout << "Wrong amount of parameters!";
        std::cout << "Example usage: \n";
        std::cout << "./ <nazwa programu gracza> mapa.txt status.txt rozkazy.txt [limit_czasowy]\n";
        return 0;
    }

    std::string map_filename = argv[1];
    std::string status_filename = argv[2];
    std::string orders_filename = argv[3];
    int time_limit = atoi(argv[4]);

    std::cout << "Parsed:\nmapa:" << map_filename << "\nstatus: " << status_filename << "\nrozkazy: " << orders_filename << "\nlimit czasu: " << time_limit << "\n";

    Game game(map_filename, status_filename, orders_filename, time_limit);
    game.print();

    return 0;
}