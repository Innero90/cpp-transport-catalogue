#include "transport_catalogue.h"
#include "stat_reader.h"

int main() {
    auto data_base = move(BuildDataBase());
    TransportCatalogue transport_catalogue(data_base);
    PrintInfo(transport_catalogue);
}
