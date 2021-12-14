#include "descriptions.h"
#include "json.h"
#include "requests.h"
#include "sphere.h"
#include "transport_catalog.h"
#include "utils.h"

#include <iostream>
#include <fstream>

using namespace std;

int main() {
    fstream fin("input.json");
    fstream fout("output.json");

    const auto input_doc = Json::Load(fin);
//    const auto input_doc = Json::Load(cin);
    const auto &input_map = input_doc.GetRoot().AsMap();

    const TransportCatalog db(
            Descriptions::ReadDescriptions(input_map.at("base_requests").AsArray()),
            input_map.at("routing_settings").AsMap()
    );

    Json::PrintValue(
            Requests::ProcessAll(db, input_map.at("stat_requests").AsArray()),
            fout
//            cout
    );
    cout << endl;

    return 0;
}
