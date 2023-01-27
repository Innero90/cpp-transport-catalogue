#pragma once

#include "geo.h"

#include <map>

struct Bus {
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
    std::map<std::pair<std::string, std::string>, int> range_about_stops;
};

std::istream& operator>>(std::istream& is, Querys& q);

Querys BuildDataBase();
Querys BuildDataBase(std::istream& querys_data);
