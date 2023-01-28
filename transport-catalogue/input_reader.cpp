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

Querys BuildDataBase(std::istream& querys_data) { // это разве не то что Вы имеете ввиду?
    Querys q;
    int querys_count;
    querys_data >> querys_count;
    for (int i = 0; i < querys_count; ++i) {
        querys_data >> q;
    }
    return q;
}

Bus BusQueryParser(std::string& line) {
    Bus bus;
    std::string_view parser = line;
    auto first = parser.find(' ');
    auto last = parser.find(':');
    bus.name = parser.substr(first + 1, last - 1);
    parser.remove_prefix(last + 2);
    if (parser.find('>') != parser.npos) {
        bus.is_round = true;
        while (last != parser.npos) {
            last = parser.find('>');
            bus.stops.push_back(std::string(parser.substr(0, last - 1)));
            parser.remove_prefix(last + 2);
        }
    }
    else {
        bus.is_round = false;
        while (last != parser.npos) {
            last = parser.find('-');
            bus.stops.push_back(std::string(parser.substr(0, last - 1)));
            parser.remove_prefix(last + 2);
        }
    }
    return bus;
}

Stop StopQueryParser(std::string& line, Querys& q) {
    using namespace std;
    Stop stop;
    string_view parser = line;
    auto first = parser.find(' ');
    auto last = parser.find(':');
    stop.name = parser.substr(first + 1, last - 1);
    parser.remove_prefix(last + 2);
    last = parser.find_first_of(',');
    stop.coord.lat = std::stod(string(parser.substr(0, last)));
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
            q.range_about_stops[{stop.name, parser.substr(0, last)}] = range;
            parser.remove_prefix(last + 2);
        } while (last != parser.npos);
    }
    else {
        stop.coord.lng = stod(string(parser.substr(0, last)));
    }
    return stop;
}

std::istream& operator>>(std::istream& is, Querys& q) { // не очень понимаю как лучше реализовать отщипавание, какие параметры отправлять, символы же все время разные, а если просто сделать функцию из двух строчек то смысл в ней
    using namespace std;
    string what_do, line;
    is >> what_do;
    if (what_do == "Bus") {
        getline(is, line);
        q.buses.push_back(move(BusQueryParser(line)));
    }
    else if (what_do == "Stop") {
        getline(is, line);
        q.stops.push_back(move(StopQueryParser(line, q)));
    }
    return is;
}
