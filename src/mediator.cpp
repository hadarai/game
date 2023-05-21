#include "mediator.hpp"

Mediator::Mediator(std::string _executable_filename,
                   std::string _map_filename,
                   std::string _status_filename,
                   std::string _orders_filename) : executable_filename(_executable_filename),
                                                   map_filename(_map_filename),
                                                   status_filename(_status_filename),
                                                   orders_filename(_orders_filename)
{
}

void Mediator::loop(void)
{
    std::string command = executable_filename + " " + map_filename + " " + status_filename + " " + orders_filename + " 10";
    std::cout << "Executing command:\n"
              << command << "\n";
    system(command.c_str());
}