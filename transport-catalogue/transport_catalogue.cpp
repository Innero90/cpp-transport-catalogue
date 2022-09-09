#include "transport_catalogue.h"

TransportCatalogue::TransportCatalogue(vector<Query>& q_data) {
    for(auto q : q_data) {
        switch (q.type) {
            case QueryType::NewBus:
                routes.push_back(q.bus_name);
                stats_.stops_ = q.stops;
                stats_.is_round = q.is_round;
                stops_in_route.push_back(stats_);
                for(auto stop : q.stops) {
                    all_stops_info[stop].routes_for_stop.insert(q.bus_name);
                }
                break;
            case QueryType::NewStop:
                Coordinates coord_;
                coord_.lat = q.latitude;
                coord_.lng = q.longitude;
                all_stops_info[q.stop_name].coord = coord_;
                all_stops_info[q.stop_name].range_to_close_stop_ = q.range_to_close_stop;
                break;
        }
    }
}

int TransportCatalogue::StopsCountInRoute(int num) {
    if (stops_in_route[num].is_round) {
        return stops_in_route[num].stops_.size();
    } else {
        return stops_in_route[num].stops_.size() * 2 - 1;
    }
}

int TransportCatalogue::UniqStopsCountInRoute(int num) {
    set<string> stops;
    for (auto stop : stops_in_route[num].stops_) {
        stops.insert(stop);
    }
    return stops.size();
}

pair<int, double> TransportCatalogue::ComputeRouteRange(int num) {
    pair<int, double> length = {0, 0};
    if (stops_in_route[num].is_round) {
        for (size_t i = 0; i < stops_in_route[num].stops_.size() - 1; ++i) {
            if (all_stops_info.at(stops_in_route[num].stops_[i]).range_to_close_stop_.count(stops_in_route[num].stops_[i + 1]) != 0) {
                length.first += all_stops_info.at(stops_in_route[num].stops_[i]).range_to_close_stop_.at(stops_in_route[num].stops_[i + 1]);
            } else {
                length.first += all_stops_info.at(stops_in_route[num].stops_[i + 1]).range_to_close_stop_.at(stops_in_route[num].stops_[i]);
            }
            length.second += ComputeDistance(all_stops_info.at(stops_in_route[num].stops_[i]).coord, all_stops_info.at(stops_in_route[num].stops_[i + 1]).coord);
        }
    } else {
        for (size_t i = 0; i < stops_in_route[num].stops_.size() - 1; ++i) {
            if (all_stops_info.at(stops_in_route[num].stops_[i]).range_to_close_stop_.count(stops_in_route[num].stops_[i + 1]) != 0) {
                length.first += all_stops_info.at(stops_in_route[num].stops_[i]).range_to_close_stop_.at(stops_in_route[num].stops_[i + 1]);
            } else {
                length.first += all_stops_info.at(stops_in_route[num].stops_[i + 1]).range_to_close_stop_.at(stops_in_route[num].stops_[i]);
            }
            length.second += ComputeDistance(all_stops_info.at(stops_in_route[num].stops_[i]).coord, all_stops_info.at(stops_in_route[num].stops_[i + 1]).coord);
        }
        for (size_t i = stops_in_route[num].stops_.size() - 1; i > 0; --i) {
            if (all_stops_info.at(stops_in_route[num].stops_[i]).range_to_close_stop_.count(stops_in_route[num].stops_[i - 1]) != 0) {
                length.first += all_stops_info.at(stops_in_route[num].stops_[i]).range_to_close_stop_.at(stops_in_route[num].stops_[i - 1]);
            } else {
                length.first += all_stops_info.at(stops_in_route[num].stops_[i - 1]).range_to_close_stop_.at(stops_in_route[num].stops_[i]);
            }
            length.second += ComputeDistance(all_stops_info.at(stops_in_route[num].stops_[i]).coord, all_stops_info.at(stops_in_route[num].stops_[i - 1]).coord);
        }
    }
    return length;
}

void TransportCatalogue::PrintBusInfo(string route_number) {
    if (find(begin(routes), end(routes), route_number) != end(routes)) {
        int i = 0;
        for (auto route : routes) {
            if (route == route_number) {
                pair<int, double> lenght = ComputeRouteRange(i);
                cout << "Bus " << route_number << ": ";
                cout << StopsCountInRoute(i) << " stops on route, ";
                cout << UniqStopsCountInRoute(i) << " unique stops, ";
                cout << lenght.first << " route length, ";
                cout << lenght.first / lenght.second << " curvature" << endl;
            } else {
                ++i;
            }
        }
    } else {
        cout << "Bus " << route_number << ": not found" << endl;
    }
}

void TransportCatalogue::PrintStopInfo(string stop) {
    if (!all_stops_info.count(stop)) {
        cout << "Stop " << stop << ": not found" << endl;
    } else if (all_stops_info.at(stop).routes_for_stop.empty()) {
        cout << "Stop " << stop << ": no buses" << endl;
    } else {
        cout << "Stop " << stop << ": buses";
        set<string> nums;
        for (auto bus : all_stops_info.at(stop).routes_for_stop) {
            nums.insert(bus);
        }
        for (auto num : nums){
            cout << " " << num;
        }
        cout << endl;
    }
}
