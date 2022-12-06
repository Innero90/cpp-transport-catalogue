#pragma once

#include <deque>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include "input_reader.h"
#include "geo.h"

using namespace std;

class TransportCatalogue {
public:
    TransportCatalogue(Querys data_base);

    void AddStop(Stop stop);
    void AddBus(Bus bus);

    tuple<int, int, int, double> GetBusInfo(string& bus);
    set<string> GetStopInfo(string& stop);

    int StopsCountInRoute(string& bus);
    int UniqStopsCountInRoute(string& bus);
    int ComputeMeterRouteLenght(string& bus);
    double ComputeCoordRouteLenght(string& bus);

private:
    struct StopInfo {
        StopInfo(Stop stop) :
            name_(stop.name) {
            coord.lat = stop.latitude;
            coord.lng = stop.longitude;
        }

        string name_;
        Coordinates coord;
    };

    struct RouteInfo {
        RouteInfo(Bus bus) :
            name_(bus.name), is_round_(bus.is_round) {
        }

        string name_;
        bool is_round_;
        deque<StopInfo*> stops_;
    };

    deque<StopInfo> stops_;
    unordered_map<string_view, StopInfo*> stops;
    deque<RouteInfo> routes_;
    unordered_map<string_view, RouteInfo*> routes;
    map<pair<string, string>, int> range_about_stops;
};
