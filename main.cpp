#include <iostream>
#include <fstream>

#include "mediator.hpp"
#include "game.hpp"

int main(int argc, char *argv[])
{
    std::string game_filename, map_filename, status_filename, orders_filename;
    int time_limit;

#ifdef M
    // I'm the mediator
    if (argc != 6)
    {
        std::cout << "Wrong amount of parameters!\n";
        std::cout << "Example usage: \n";
        std::cout << "./<program mediatora> <program gracza> mapa.txt status.txt rozkazy.txt [limit_czasowy]\n";
        return 0;
    }
    game_filename = std::string(argv[1]);
    map_filename = argv[2];
    status_filename = argv[3];
    orders_filename = argv[4];
    time_limit = atoi(argv[5]);

    Mediator mediator(game_filename, map_filename, status_filename, orders_filename);
    mediator.loop();

#elif P
    // I'm a player
    if (argc != 5)
    {
        std::cout << "Wrong amount of parameters!\n";
        std::cout << "Example usage: \n";
        std::cout << "./ <nazwa programu> mapa.txt status.txt rozkazy.txt [limit_czasowy]\n";
        return 0;
    }
    map_filename = argv[1];
    status_filename = argv[2];
    orders_filename = argv[3];
    time_limit = atoi(argv[4]);

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
#endif
    return 0;
}
