#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

enum class QueryType {
    NewBus,
    NewStop
};

struct Query {
    QueryType type;
    string stop_name;
    string bus_name;
    vector<string> stops;
    double latitude;
    double longitude;
    bool is_round;
    unordered_map<string, int> range_to_close_stop;
};

istream& operator>>(istream& is, Query& q);

vector<Query> BuildDataBase();
