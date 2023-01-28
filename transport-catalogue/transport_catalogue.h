#pragma once

#include <deque>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include "input_reader.h"

using namespace std;

struct StopInfo {
    StopInfo(Stop stop) :
        name_(stop.name) {
        coord.lat = stop.coord.lat;
        coord.lng = stop.coord.lng;
    }

    string name_;
    Coordinates coord;
};

struct RouteInfo {
    RouteInfo(Bus bus) :
        name_(bus.name), is_round_(bus.is_round) {
    }

    string_view name_;
    bool is_round_;
    deque<StopInfo*> stops_;
};

struct BusInfoResult {
    int stops_on_route = 0;
    int unique_stops = 0;
    int route_length = 0;
    double curvature = 0.0;
};

class TransportCatalogue {
public:
    TransportCatalogue(Querys data_base);

    void AddStop(Stop stop);
    void AddBus(Bus bus);

    BusInfoResult GetBusInfo(string& bus);
    set<string> GetStopInfo(string& stop);

    int GetStopsCountInRoute(string& bus);
    int GetUniqStopsCountInRoute(string& bus);
    int ComputeMeterRouteLenght(string& bus);
    double ComputeCoordRouteLenght(string& bus);

private:
    deque<StopInfo> stops_;
    unordered_map<string_view, StopInfo*> stops;
    deque<RouteInfo> routes_;
    unordered_map<string_view, RouteInfo*> routes;
    map<pair<string_view, string_view>, int> range_about_stops;   //если поставить unordered_map,то ломается словарь, не понимаю почему? так же если ставить string_view ломается результат метода GetStopInfo
};
