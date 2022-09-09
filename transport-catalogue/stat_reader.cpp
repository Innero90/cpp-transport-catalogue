#pragma once

#include <iostream>
#include <string>

using namespace std;

void PrintInfo (TransportCatalogue& transport_catalogue) {
    int queries_count;
    cin >> queries_count;
    
    for (int i = 0; i < queries_count; ++i) {
        string query, query_;
        cin >> query;
        if (query == "Bus") {
            getline(cin, query_);
            query_ = query_.substr(1, query_.size());
            transport_catalogue.PrintBusInfo(query_);
        }
        if (query == "Stop") {
            getline(cin, query_);
            query_ = query_.substr(1, query_.size());
            transport_catalogue.PrintStopInfo(query_);
        }
    }
}
