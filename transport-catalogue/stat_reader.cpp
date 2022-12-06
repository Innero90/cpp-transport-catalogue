
#include "stat_reader.h"

void PrintBusInfo(string& bus, tuple<int, int, int, double> result) {
    if (get<0>(result) != 0) {
        cout << "Bus "s << bus << ": "s << get<0>(result) << " stops on route, "s
            << get<1>(result) << " unique stops, "s << get<2>(result) << " route length, "s << get<3>(result) << " curvature"s << endl;
    }
    else {
        cout << "Bus "s << bus << ": not found"s << endl;
    }
}

void PrintStopInfo(string& stop, set<string> result) {
    string first = *result.begin();
    if (first == "no buses"s || first == "not found"s) {
        cout << "Stop " << stop << ": " << first << endl;
    }
    else {
        bool is_first = true;
        cout << "Stop " << stop << ": buses ";
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
