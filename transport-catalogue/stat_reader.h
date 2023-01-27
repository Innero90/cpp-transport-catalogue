#pragma once

#include <iostream>
#include <string>

#include "transport_catalogue.h"

void PrintBusInfo(const string& bus, tuple<int, int, double> result);
void PrintStopInfo(const string& stop, set<string> result);
void PrintInfo(TransportCatalogue& transport_catalogue);
