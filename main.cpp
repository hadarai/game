#include <iostream>
#include <fstream>

#include "mediator.hpp"
#include "game.hpp"

int main(int argc, char *argv[])
{
    if (argc != 6)
    {
        std::cout << "Wrong amount of parameters!";
        std::cout << "Example usage: \n";
        std::cout << "./ <nazwa programu gracza> [M | G] mapa.txt status.txt rozkazy.txt [limit_czasowy]\n";
        return 0;
    }
    char role = *(argv[1]);
    std::string map_filename = argv[2];
    std::string status_filename = argv[3];
    std::string orders_filename = argv[4];
    int time_limit = atoi(argv[5]);

    if (role == 'M')
    {
        Mediator mediator(std::string(argv[0]), map_filename, status_filename, orders_filename);
        mediator.loop();

        // I'm the mediator
    }
    else
    {
        // I'm a player
        // std::cout << "Parsed:\nrola: " << role << "\nmapa:" << map_filename << "\nstatus: " << status_filename << "\nrozkazy: " << orders_filename << "\nlimit czasu: " << time_limit << "\n";

        Game game(map_filename, status_filename, orders_filename, time_limit);
        game.pretty_print();

        Game test_game(game);
        std::vector<Order> next_moves = test_game.generate_legal_orders();
        for (Order move : next_moves)
        {
            std::cout << move.denote() << std::endl;
            try
            {
                std::cout << "Let's try to execute an order\n";
                test_game.execute_an_order(move);
            }
            catch (const std::string msg)
            {
                std::cout << "Catching \n";
                std::cerr << msg << std::endl;
            }
            test_game.pretty_print();
        }
        game.save_orders_to_file(orders_filename, next_moves);
    }
    return 0;
}
