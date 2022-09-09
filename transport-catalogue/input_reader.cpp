#include <sstream>

#include "input_reader.h"

istream& operator>>(istream& is, Query& q) {
    string what_do, line;
    is >> what_do;
    if (what_do == "Bus") {
        q.type = QueryType::NewBus;
        getline(is, line);
        string_view parser = line;
        auto first = parser.find(' ');
        auto last = parser.find(':');
        q.bus_name = parser.substr(first + 1, last - 1);
        parser.remove_prefix(last + 2);
        if (parser.find('>') != parser.npos) {
            q.is_round = true;
            while (last != parser.npos) {
                last = parser.find('>');
                q.stops.push_back(string(parser.substr(0, last - 1)));
                parser.remove_prefix(last + 2);
            }
        } else {
            q.is_round = false;
            while (last != parser.npos) {
                last = parser.find('-');
                q.stops.push_back(string(parser.substr(0, last - 1)));
                parser.remove_prefix(last + 2);
            }
        }
    } else if (what_do == "Stop") {
        q.type = QueryType::NewStop;
        getline(is, line);
        string_view parser = line;
        auto first = parser.find(' ');
        auto last = parser.find(':');
        q.stop_name = parser.substr(first + 1, last - 1);
        parser.remove_prefix(last + 2);
        last = parser.find_first_of(',');
        q.latitude = stod(string(parser.substr(0, last)));
        parser.remove_prefix(last + 2);
        last = parser.find_first_of(' ');
        if (last != parser.npos) {
            last = parser.find_first_of(',');
            q.longitude = stod(string(parser.substr(0, last)));
            parser.remove_prefix(last + 2);
            do {
                auto find_m = parser.find('m');
                auto range = stoi(string(parser.substr(0, find_m)));
                parser.remove_prefix(find_m + 5);
                last = parser.find_first_of(',');
                q.range_to_close_stop[string(parser.substr(0, last))] = range;
                parser.remove_prefix(last + 2);
            } while (last != parser.npos);
        } else {
            q.longitude = stod(string(parser.substr(0, last)));
        }
    }
    return is;
}

vector<Query> BuildDataBase() {
    int queries_count;
    Query q;
    vector<Query> a;
    
    cin >> queries_count;
    
    for (int i = 0; i < queries_count; ++i) {
        cin >> q;
        a.push_back(move(q));
    }
    return a;
}
