#pragma once

#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <algorithm>
#include <set>
#include "geo.h"
#include "input_reader.h"

class TransportCatalogue {
    public:
    
    TransportCatalogue(vector<Query>& q_data);
    
    int StopsCountInRoute(int num);
    
    int UniqStopsCountInRoute(int num);
    
    pair<int, double> ComputeRouteRange(int num);
    
    void PrintBusInfo(string route_number);
    
    void PrintStopInfo(string stop);
    
    private:
    
    struct RouteStats {
        vector<string> stops_;
        bool is_round;
    };
    
    struct StopsStats {
        Coordinates coord;
        unordered_set<string> routes_for_stop;
        unordered_map<string, int> range_to_close_stop_;
    };
    
    RouteStats stats_;
    vector<string> routes;
    vector<RouteStats> stops_in_route;
    unordered_map<string, StopsStats> all_stops_info;
};
