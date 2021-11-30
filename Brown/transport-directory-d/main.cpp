#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <iomanip>

#include "stop.h"
#include "bus.h"
#include "manager.h"
#include "json.h"

using namespace std;

enum class CreationRequestType {
    ADD_STOP,
    ADD_BUS,
};

enum class PrintRequestType {
    PRINT_BUS,
    PRINT_STOP,
};

CreationRequestType ParseCreationRequestType(const string &request) {
    CreationRequestType result;
    if (request[0] == 'S') {
        result = CreationRequestType::ADD_STOP;
    } else {
        result = CreationRequestType::ADD_BUS;
    }
    return result;
}

PrintRequestType ParsePrintRequestType(const string &request) {
    PrintRequestType result;
    if (request[0] == 'S') {
        result = PrintRequestType::PRINT_STOP;
    } else {
        result = PrintRequestType::PRINT_BUS;
    }
    return result;
}

Json::Node BuildError(const string &message) {
    std::map<std::string, Json::Node> result;
    result.emplace("error_message", Json::Node(message));
    return result;
}

void ProcessCreationRequest(Manager &manager, const Json::Node &request) {
    const std::map<std::string, Json::Node> &request_as_map = request.AsMap();
    CreationRequestType type = ParseCreationRequestType(request_as_map.at("type").AsString());
    if (type == CreationRequestType::ADD_BUS) {
        manager.AddBus(Bus(request_as_map));
    } else if (type == CreationRequestType::ADD_STOP) {
        manager.AddStop(Stop(request_as_map));
    }
}

Manager BuildManager(const vector<Json::Node> &node) {
    Manager manager;
    for (const auto &request: node) {
        ProcessCreationRequest(manager, request);
    }
    manager.UpdateLengths();
    return move(manager);
}

Json::Document BuildResponse(const Manager &manager, const vector<Json::Node> &requests) {
    vector<Json::Node> result;
    result.reserve(requests.size());

    for (const auto &request: requests) {
        Json::Node temp;
        PrintRequestType type = ParsePrintRequestType(request.AsMap().at("type").AsString());
        if (type == PrintRequestType::PRINT_BUS) {
            optional<BusInfo> busInfo = manager.GetBusInfo(request.AsMap().at("name").AsString());
            if (busInfo) {
                temp = busInfo->ToJson();
            } else {
                temp = BuildError("not found");
            }
        } else if (type == PrintRequestType::PRINT_STOP) {
            optional<StopInfo> stopInfo = manager.GetStopInfo(request.AsMap().at("name").AsString());
            if (stopInfo) {
                temp = stopInfo->ToJson();
            } else {
                temp = BuildError("not found");
            }
        }
        temp.AddId(request.AsMap().at("id").AsInt());
        result.push_back(move(temp));
    }

    return Json::Document(Json::Node(move(result)));
}

int main() {
    ifstream in("input.json");
    ofstream out("output.json");
    out << fixed;
    out.precision(6);

    Json::Document document = Json::Load(in);
    Manager manager = BuildManager(document.GetRoot().AsMap().at("base_requests").AsArray());
    Json::Save(out, BuildResponse(manager, document.GetRoot().AsMap().at("stat_requests").AsArray()));

    in.close();
    out.close();

//    cout.precision(6);
//    Json::Document documentы = Json::Load(cin);
//    Manager manager = BuildManager(document.GetRoot().AsMap().at("base_requests").AsArray());
//    Json::Save(cout, BuildResponse(manager, document.GetRoot().AsMap().at("stat_requests").AsArray()));

    return 0;
}
