#pragma once

#include "geo.h"

#include <map>

struct Bus {            // у меня ломается весь справочник если выносить структуры и начинать пользоваться теми что в каталоге, почему не понимаю, как правильно подключить файлы
    std::string name;
    bool is_round = false;
    std::vector<std::string> stops;
};

struct Stop {
    std::string name;
    Coordinates coord;
};

struct Querys {
    std::vector<Stop> stops;
    std::vector<Bus> buses;
    std::map<std::pair<std::string_view, std::string_view>, int> range_about_stops;
};

std::istream& operator>>(std::istream& is, Querys& q);

Querys BuildDataBase();
Querys BuildDataBase(std::istream& querys_data);
Bus BusQueryParser(std::string& line);
Stop StopQueryParser(std::string& line, Querys& q);
