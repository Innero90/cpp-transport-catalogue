#pragma once

#include <string>
#include <unordered_map>
#include <set>
#include <vector>

#include "geo.h"

namespace transport {

struct BusStat {
    int all_stops;
    int unique_stops;
    unsigned int length;
    double curvature;
};

struct Stop {
    std::string name;
    geo::Coordinates coordinates;
    std::set<std::string_view> buses_through;
};

struct Bus {
    std::string name;
    std::vector<Stop*> bus_stops;
    bool circular;
};

namespace parsed {

struct Bus {
    std::string name;
    std::vector<std::string> stops;
    bool circular;
};

struct Distances {
    std::string from;
    std::unordered_map<std::string, int> d_map;
};

struct Stop {
    std::string name;
    double lat;
    double lng;
};

}

}
