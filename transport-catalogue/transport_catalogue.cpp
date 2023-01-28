#include "transport_catalogue.h"

TransportCatalogue::TransportCatalogue(Querys data_base) {
    for (auto& stop : data_base.stops) {
        AddStop(stop);
    }
    for (auto& bus : data_base.buses) {
        AddBus(bus);
    }
    for (auto& stops : data_base.range_about_stops) {
        range_about_stops.insert(move(stops));
    }
}

void TransportCatalogue::AddStop(Stop stop) {
    StopInfo stop_(move(stop));
    stops_.push_back(move(stop_));
    string_view name = stops_.back().name_;
    stops[name] = &stops_.back();
}

void TransportCatalogue::AddBus(Bus bus) {
    RouteInfo route_info(bus);
    for (auto& stop : bus.stops) {
        route_info.stops_.push_back(stops[stop]);
    }
    routes_.push_back(move(route_info));
    string_view name = routes_.back().name_;
    routes[name] = &routes_.back();
}

BusInfoResult TransportCatalogue::GetBusInfo(string& bus) {
    if (routes.find(bus) != routes.end()) {
        int stops_count = GetStopsCountInRoute(bus);
        int uniq_stops_count = GetUniqStopsCountInRoute(bus);
        int m_route_lenght = ComputeMeterRouteLenght(bus);
        double coord_route_lenght = ComputeCoordRouteLenght(bus);
        return { stops_count, uniq_stops_count, m_route_lenght, m_route_lenght / coord_route_lenght };
    }
    else {
        return { 0, 0, 0, 0.0 };
    }
}

set<string> TransportCatalogue::GetStopInfo(string& stop) {
    set<string> result;
    if (!stops.count(stop)) {
        result.insert("not found"s);
        return result;
    }
    else {
        for (auto& route : routes_) {
            for (auto& stop_ : route.stops_) {
                if (stop_->name_ == stop) {
                    result.insert(string(route.name_));
                }
            }
        }
    }
    if (result.empty()) {
        result.insert("no buses"s);
        return result;
    }
    return result;
}

int TransportCatalogue::GetStopsCountInRoute(string& bus) {
    auto route = *routes[bus];
    if (route.is_round_) {
        return route.stops_.size();
    }
    else {
        return route.stops_.size() * 2 - 1;
    }
}

int TransportCatalogue::GetUniqStopsCountInRoute(string& bus) {
    auto route = *routes[bus];
    unordered_set<StopInfo*> result;
    for (const auto& stop : route.stops_) {
        result.insert(stop);
    }
    return result.size();
}

int TransportCatalogue::ComputeMeterRouteLenght(string& bus) {
    auto route = *routes[bus];
    int result = 0;
    if (route.is_round_) {
        for (size_t i = 0; i < route.stops_.size() - 1; ++i) {
            if (range_about_stops.count({ route.stops_[i]->name_, route.stops_[i + 1]->name_ })) {
                result += range_about_stops.at({ route.stops_[i]->name_, route.stops_[i + 1]->name_ });
            }
            else {
                result += range_about_stops.at({ route.stops_[i + 1]->name_, route.stops_[i]->name_ });
            }
        }
    }
    else {
        for (size_t i = 0; i < route.stops_.size() - 1; ++i) {
            if (range_about_stops.count({ route.stops_[i]->name_, route.stops_[i + 1]->name_ })) {
                result += range_about_stops.at({ route.stops_[i]->name_, route.stops_[i + 1]->name_ });
            }
            else {
                result += range_about_stops.at({ route.stops_[i + 1]->name_, route.stops_[i]->name_ });
            }
        }
        for (size_t i = route.stops_.size() - 1; i > 0; --i) {
            if (range_about_stops.count({ route.stops_[i]->name_, route.stops_[i - 1]->name_ })) {
                result += range_about_stops.at({ route.stops_[i]->name_, route.stops_[i - 1]->name_ });
            }
            else {
                result += range_about_stops.at({ route.stops_[i - 1]->name_, route.stops_[i]->name_ });
            }
        }
    }
    return result;
}

double TransportCatalogue::ComputeCoordRouteLenght(string& bus) {
    auto route = *routes[bus];
    double result = 0;
    if (route.is_round_) {
        for (size_t i = 0; i < route.stops_.size() - 1; ++i) {
            result += ComputeDistance(route.stops_[i]->coord, route.stops_[i + 1]->coord);
        }
    }
    else {
        for (size_t i = 0; i < route.stops_.size() - 1; ++i) {
            result += ComputeDistance(route.stops_[i]->coord, route.stops_[i + 1]->coord);
        }
        for (size_t i = route.stops_.size() - 1; i > 0; --i) {
            result += ComputeDistance(route.stops_[i]->coord, route.stops_[i - 1]->coord);
        }
    }
    return result;
}
