#include <sstream>
#include <vector>
#include <iostream>

#include "input_reader.h"

Querys BuildDataBase() {
    Querys q;
    int querys_count;
    std::cin >> querys_count;
    for (int i = 0; i < querys_count; ++i) {
        std::cin >> q;
    }
    return q;
}

Querys BuildDataBase(std::istream& querys_data) {
    Querys q;
    int querys_count;
    querys_data >> querys_count;
    for (int i = 0; i < querys_count; ++i) {
        querys_data >> q;
    }
    return q;
}

std::istream& operator>>(std::istream& is, Querys& q) {
    using namespace std;
    string what_do, line;
    is >> what_do;
    if (what_do == "Bus") {
        Bus bus;
        getline(is, line);
        string_view parser = line;
        auto first = parser.find(' ');
        auto last = parser.find(':');
        bus.name = parser.substr(first + 1, last - 1);
        parser.remove_prefix(last + 2);
        if (parser.find('>') != parser.npos) {
            bus.is_round = true;
            while (last != parser.npos) {
                last = parser.find('>');
                bus.stops.push_back(string(parser.substr(0, last - 1)));
                parser.remove_prefix(last + 2);
            }
        }
        else {
            bus.is_round = false;
            while (last != parser.npos) {
                last = parser.find('-');
                bus.stops.push_back(string(parser.substr(0, last - 1)));
                parser.remove_prefix(last + 2);
            }
        }
        q.buses.push_back(bus);
    }
    else if (what_do == "Stop") {
        Stop stop;
        getline(is, line);
        string_view parser = line;
        auto first = parser.find(' ');
        auto last = parser.find(':');
        stop.name = parser.substr(first + 1, last - 1);
        parser.remove_prefix(last + 2);
        last = parser.find_first_of(',');
        stop.coord.lat = stod(string(parser.substr(0, last)));
        parser.remove_prefix(last + 2);
        last = parser.find_first_of(' ');
        if (last != parser.npos) {
            last = parser.find_first_of(',');
            stop.coord.lng = stod(string(parser.substr(0, last)));
            parser.remove_prefix(last + 2);
            do {
                auto find_m = parser.find('m');
                auto range = stoi(string(parser.substr(0, find_m)));
                parser.remove_prefix(find_m + 5);
                last = parser.find_first_of(',');
                q.range_about_stops[{stop.name, string(parser.substr(0, last))}] = range;
                parser.remove_prefix(last + 2);
            } while (last != parser.npos);
        }
        else {
            stop.coord.lng = stod(string(parser.substr(0, last)));
        }
        q.stops.push_back(stop);
    }
    return is;
}
