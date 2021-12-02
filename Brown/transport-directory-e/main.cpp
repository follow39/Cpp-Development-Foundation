#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <iomanip>

#include "stop.h"
#include "bus.h"
#include "manager.h"
#include "path.h"
#include "json.h"

using namespace std;

enum class CreationRequestType {
    ADD_STOP,
    ADD_BUS,
};

enum class PrintRequestType {
    PRINT_BUS,
    PRINT_STOP,
    PRINT_ROUTE,
};

CreationRequestType ParseCreationRequestType(const string &request) {
    CreationRequestType result;
    if (request == "Stop") {
        result = CreationRequestType::ADD_STOP;
    } else {
        result = CreationRequestType::ADD_BUS;
    }
    return result;
}

PrintRequestType ParsePrintRequestType(const string &request) {
    PrintRequestType result;
    if (request == "Stop") {
        result = PrintRequestType::PRINT_STOP;
    } else if (request == "Bus") {
        result = PrintRequestType::PRINT_BUS;
    } else if (request == "Route") {
        result = PrintRequestType::PRINT_ROUTE;
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

Manager BuildManager(const Json::Document &document) {
    auto &requests = document.GetRoot().AsMap().at("base_requests").AsArray();
    Manager manager(RoutingSettings{
            document.GetRoot().AsMap().at("routing_settings").AsMap()});
    for (const auto &request: requests) {
        ProcessCreationRequest(manager, request);
    }
    manager.PrepareToProcess();
    return move(manager);
}

template<typename OptInfo>
Json::Node BuildResponseNode(OptInfo info) {
    if (info) {
        return info->ToJson();
    }
    return BuildError("not found");
}

Json::Document BuildResponse(const Manager &manager, const Json::Document &document) {
    auto &requests = document.GetRoot().AsMap().at("stat_requests").AsArray();
    vector<Json::Node> result;
    result.reserve(requests.size());

    for (const auto &request: requests) {
        Json::Node temp;
        PrintRequestType type = ParsePrintRequestType(request.AsMap().at("type").AsString());
        if (type == PrintRequestType::PRINT_BUS) {
            temp = BuildResponseNode(manager.GetBusInfo(request.AsMap().at("name").AsString()));
        } else if (type == PrintRequestType::PRINT_STOP) {
            temp = BuildResponseNode(manager.GetStopInfo(request.AsMap().at("name").AsString()));
        } else if (type == PrintRequestType::PRINT_ROUTE) {
            temp = BuildResponseNode(manager.RoutePath(PathRequest{request.AsMap()}));
        }
        temp.AddId(request.AsMap().at("id").AsInt());
        result.push_back(move(temp));
    }

    return Json::Document(Json::Node(move(result)));
}

int main() {
    ifstream in("input.json");
    ofstream out("output.json");
    Json::Document document = Json::Load(in);
    Manager manager = BuildManager(document);
    Json::Save(out, BuildResponse(manager, document));

    in.close();
    out.close();

//    Json::Document document = Json::Load(cin);
//    Manager manager = BuildManager(document.GetRoot().AsMap().at("base_requests").AsArray());
//    Json::Save(cout, BuildResponse(manager, document.GetRoot().AsMap().at("stat_requests").AsArray()));

    return 0;
}
