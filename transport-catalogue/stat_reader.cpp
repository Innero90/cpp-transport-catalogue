#include "stat_reader.h"

void PrintBusInfo(const string& bus_name, BusInfoResult result) {
    if (result.stops_on_route != 0) {
        cout << "Bus "s << bus_name << ": "s << result.stops_on_route << " stops on route, "s
            << result.unique_stops << " unique stops, "s << result.route_length << " route length, "s << result.curvature << " curvature"s << endl;
    }
    else {
        cout << "Bus "s << bus_name << ": not found"s << endl;
    }
}

void PrintStopInfo(const string& stop_name, set<string> result) {
    string first = *result.begin();
    if (first == "no buses"s || first == "not found"s) {
        cout << "Stop " << stop_name << ": " << first << endl;
    }
    else {
        bool is_first = true;
        cout << "Stop " << stop_name << ": buses ";
        for (auto& text : result) {
            if (!is_first) {
                cout << " ";
            }
            cout << text;
            is_first = false;
        }
        cout << endl;
    }
}

void PrintInfo(TransportCatalogue& transport_catalogue) {
    int queries_count;
    cin >> queries_count;

    for (int i = 0; i < queries_count; ++i) {
        string what_do, query;
        cin >> what_do;
        if (what_do == "Bus") {
            getline(cin, query);
            query = query.substr(1, query.size());
            auto result = transport_catalogue.GetBusInfo(query);
            PrintBusInfo(query, result);
        }
        if (what_do == "Stop") {
            getline(cin, query);
            query = query.substr(1, query.size());
            auto result = transport_catalogue.GetStopInfo(query);
            PrintStopInfo(query, result);
        }
    }
}
