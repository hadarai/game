#include <game.hpp>

const std::map<std::pair<char, char>, int> Game::calculate_damage = Game::create_damages();

Game::Game(
    std::string map_filename,
    std::string status_filename,
    std::string orders_filename,
    int time_limit)
{
    time_limit = time_limit;
    orders_filename = orders_filename;

    std::ifstream map_file;
    map_file.open(map_filename);

    int x = 0, y = 0;
    char sign;
    std::string line;

    while (std::getline(map_file, line))
    {
        std::vector<char> line_v(line.begin(), line.end());
        map.push_back(line_v);
        y++;
    }
    x = line.length();
    map_file.close();
    X = x;
    Y = y;

    std::ifstream status_file;
    status_file.open(status_filename);

    status_file >> money;
    char whose, type, produces;
    int id, hit_points;
    std::cout << "This much money: " << money << std::endl;
    std::string str;

    while (status_file >> whose >> type >> id >> x >> y >> hit_points)
    {
        if (type != 'B')
        {
            if (whose == MY_UNIT)
                my_units.insert({id,
                                 std::make_unique<Unit>(Unit(id, x, y, whose, type, hit_points))});
            else
                enemy_units.insert({id,
                                    std::make_unique<Unit>(Unit(id, x, y, whose, type, hit_points))});
        }
        else if (type == 'B')
        {
            status_file >> produces;
            if (whose == MY_UNIT)
                my_base = std::make_unique<Base>(Base(id, x, y, whose, type, hit_points, produces));
            else
                enemy_base = std::make_unique<Base>(Base(id, x, y, whose, type, hit_points, produces));
        }
    }
    status_file.close();
}

Game::Game(const Game &obj)
{
    time_limit = obj.time_limit;
    money = obj.money;

    my_base = std::make_unique<Base>(Base(*(obj.my_base)));
    enemy_base = std::make_unique<Base>(Base(*(obj.enemy_base)));
    map = std::vector<std::vector<char>>(obj.map);
    // ! How vector of pointers is copied!?
    my_units = std::map<int, std::shared_ptr<Unit>>(obj.my_units);
    enemy_units = std::map<int, std::shared_ptr<Unit>>(obj.enemy_units);
    X = obj.X;
    Y = obj.Y;
    orders_filename = std::string(obj.orders_filename);
}

Game::~Game()
{
    my_base.reset();
    enemy_base.reset();
}

void Game::print(void)
{
    for (std::vector<char> line : map)
    {
        for (char c : line)
            std::cout << c << " ";
        std::cout << std::endl;
    }
    std::cout << (*my_base).denote() << std::endl;
    std::cout << (*enemy_base).denote() << std::endl;
    for (auto const &[i, u] : my_units)
        std::cout << u->denote() << std ::endl;
    for (auto const &[i, u] : enemy_units)
        std::cout << u->denote() << std ::endl;
}

void Game::pretty_print(void)
{
    for (int j = 0; j < Y; j++)
    {
        for (int i = 0; i < X; i++)
        {
            char this_char = map[j][i];
            for (auto const &[id, u] : my_units)
            {
                if (u->get_x() == i && u->get_y() == j)
                    this_char = u->get_letter();
            }
            for (auto const &[id, u] : enemy_units)
            {
                if (u->get_x() == i && u->get_y() == j)
                    this_char = tolower(u->get_letter());
            }
            std::cout << this_char << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<Order> Game::generate_legal_orders(void)
{


    // todo generate really simple move for a unit
    std::vector<Order> orders;

    Order o;

    o.unit_id = my_units.begin()->first;
    o.action = 'M';
    o.parameters.move.x = my_units.begin()->second->get_x() + 1;
    o.parameters.move.y = my_units.begin()->second->get_y() + 1;
    std::cout << my_base->produced_unit_letter << std::endl;

    orders.push_back(o);
    return orders;
}

void Game::hit_a_unit(Unit unit, Unit enemy)
{
    auto it = calculate_damage.find(std::pair(unit.get_letter(), enemy.get_letter()));

    if (it == calculate_damage.end())
        throw "No such encounter!\n";
    else
    {
        // found
        std::cout << "damage dealt " << it->second << std::endl;

        if (enemy.deal(it->second) < 0)
        {
            // kill the unit
            std::cout
                << "Unit has been killed" << std::endl;
            // remove enemy from enemies if he's dead
            enemy_units.erase(enemy.get_id());
        }
    }
void Game::make_a_move(int id, int x, int y)
{
    // check if nobody else stands here

    for (auto const &[i, u] : enemy_units) // check if none of my units stands here
        if (u->does_it_stand_here(x, y))
            // enemy unit stands there - abort movement
            throw "Enemy unit already stands there. Abort move!\n";
    for (auto const &[i, u] : my_units) // check if none of my units stands here
        if (u->does_it_stand_here(x, y))
            throw "My unit already stands there. Abort move!\n";
    // check with base and obstacles
    if (map[y][x] != '0')
        throw "Base or obstacle already there! Abort move!\n";

    my_units[id]->move_to(x, y);
}

void Game::execute_an_order(Order order)
{
    switch (order.action)
    {
    case 'M':
        make_a_move(order.unit_id, order.parameters.move.x, order.parameters.move.y);
        break;
    case 'A':
        hit_a_unit(*(my_units[order.unit_id]), *(enemy_units[order.parameters.attack.prey_id]));
        break;
    case 'B':
        my_base->produce_an_unit(order.parameters.build.letter);
        break;
    }
}
