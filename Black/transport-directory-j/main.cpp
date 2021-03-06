#include "descriptions.h"
#include "json.h"
#include "requests.h"
#include "sphere.h"
#include "transport_catalog.h"
#include "utils.h"

#include <iostream>
#include <fstream>

using namespace std;

#define DEBUGIO 0

int main() {
#if DEBUGIO
    ifstream fin("input1.json");
    const auto input_doc = Json::Load(fin);
    fin.close();
#else
    const auto input_doc = Json::Load(cin);
#endif
    const auto &input_map = input_doc.GetRoot().AsMap();

    const TransportCatalog db(
            Descriptions::ReadDescriptions(input_map.at("base_requests").AsArray()),
            input_map.at("routing_settings").AsMap(),
            input_map.at("render_settings").AsMap()
    );

    Json::PrintValue(
            Requests::ProcessAll(db, input_map.at("stat_requests").AsArray()),
            cout
    );
    cout << endl;

#ifdef DEBUGIO
    ofstream fout("out.svg");
    fout << db.RenderMap();
    fout.close();
#endif

    return 0;
}
