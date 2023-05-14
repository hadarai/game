#include <game.hpp>

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
        if (type == 'B')
        {
            status_file >> produces;
            if (whose == MY_UNIT)
                my_base = std::make_unique<Base>(Base(id, x, y, whose, type, hit_points, produces));
            else
                enemy_base = std::make_unique<Base>(Base(id, x, y, whose, type, hit_points, produces));
        }
        else
        {
            units.push_back(
                std::make_unique<Unit>(Unit(id, x, y, whose, type, hit_points)));
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
    units = std::vector<std::shared_ptr<Unit>>(obj.units);
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
    std::cout << "Map:\n";
    for (std::vector<char> line : map)
    {
        for (char c : line)
            std::cout << c;
        std::cout << std::endl;
    }
    std::cout << (*my_base).denote() << std::endl;
    std::cout << (*enemy_base).denote() << std::endl;

    for (std::shared_ptr<Unit> u : units)
    {
        std::cout << (*u).denote() << std ::endl;
    }
}
