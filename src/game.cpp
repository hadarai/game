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
                my_units.push_back(
                    std::make_unique<Unit>(Unit(id, x, y, whose, type, hit_points)));
            else
                enemy_units.push_back(
                    std::make_unique<Unit>(Unit(id, x, y, whose, type, hit_points)));
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
    my_units = std::vector<std::shared_ptr<Unit>>(obj.my_units);
    enemy_units = std::vector<std::shared_ptr<Unit>>(obj.enemy_units);
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
    for (std::shared_ptr<Unit> u : my_units)
        std::cout << (*u).denote() << std ::endl;
    for (std::shared_ptr<Unit> u : enemy_units)
        std::cout << (*u).denote() << std ::endl;
}

void Game::pretty_print(void)
{
    for (int j = 0; j < Y; j++)
    {
        for (int i = 0; i < X; i++)
        {
            char this_char = map[j][i];
            for (std::shared_ptr<Unit> u : my_units)
            {
                if ((*u).get_x() == i && (*u).get_y() == j)
                    this_char = (*u).get_letter();
            }
            for (std::shared_ptr<Unit> u : enemy_units)
            {
                if ((*u).get_x() == i && (*u).get_y() == j)
                    this_char = tolower((*u).get_letter());
            }
            std::cout << this_char << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<Game> Game::generate_my_legal_moves(void)
{
    std::vector<Game> games;

    for (char unit_letter : available_unit_letters) // for each unit that base produces
    {
        for (std::shared_ptr<Unit> u : my_units) // for each my unit make a move
        {
            Game game_instance(*this); // this probably should be a pointer, so I can make a return
            for (int i = 0; i < X; i++)
            {
                for (int j = 0; j < Y; j++)
                    if ((*u).field_in_move_distance(i, j))
                    {
                        if ([&](void)
                            {
                                // check if nobody else stands here
                            for (std::shared_ptr<Unit> u : game_instance.enemy_units) // check if none of my units stands here
                            {
                                
                                if ((*u).does_it_stand_here(i, j))
                                {
                                    // enemy unit stands there - abort movement
                                    return false;
                                }
                            }
                            for (std::shared_ptr<Unit> u : game_instance.my_units) // check if none of my units stands here
                            {
                                if ((*u).does_it_stand_here(i, j))
                                {
                                    return false;
                                    // my unit stands there - abort movement
                                }
                            }
                            return true; }())
                        {
                            // make a move
                            (*u).move_to(i, j);
                            games.push_back(game_instance);
                        }
                    }
            }
        }
        for (std::shared_ptr<Unit> me : my_units) // for each my unit make an attack
        {
            Game game_instance(*this);

            for (std::shared_ptr<Unit> enemy : game_instance.enemy_units) // try to attack every enemy
            {
                // check if an enemy unit is in attack range
                if ((*me).field_in_attack_range((*enemy).get_x(), (*enemy).get_y()))
                {
                    // make an attack
                    game_instance.hit_a_unit(*me, *enemy); // this function also kills the enemy
                    games.push_back(game_instance);
                }
            }
        }
    }
    return games;
}

void Game::hit_a_unit(Unit unit, Unit enemy)
{
    auto it = calculate_damage.find(std::pair(unit.get_letter(), enemy.get_letter()));

    if (it == calculate_damage.end())
    {
        // TODO throw an exception
        std::cerr << "Element not found";
    }
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
            enemy_units.erase(
                std::remove(enemy_units.begin(),
                            enemy_units.end(),
                            std::shared_ptr<Unit>(&enemy)),
                enemy_units.end());
        }
    }
}