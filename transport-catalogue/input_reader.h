#pragma once

#include <map>

using namespace std;

struct Bus {
    string name;
    bool is_round = false;
    vector<string> stops;
};

struct Stop {
    string name;
    double latitude = 0.0;
    double longitude = 0.0;
};

struct Querys {
    vector<Stop> stops;
    vector<Bus> buses;
    map<pair<string, string>, int> range_about_stops;
};

istream& operator>>(istream& is, Querys& q);

Querys BuildDataBase();
