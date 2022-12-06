#pragma once

#include <iostream>
#include <string>

#include "transport_catalogue.h"

using namespace std;

void PrintBusInfo(string& bus, tuple<int, int, double> result);
void PrintStopInfo(string& stop, set<string> result);
void PrintInfo(TransportCatalogue& transport_catalogue);
