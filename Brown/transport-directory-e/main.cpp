#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <iomanip>
#include <sstream>

#include "stop.h"
#include "bus.h"
#include "manager.h"
#include "path.h"
#include "json.h"
#include "test_runner.h"

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

void TestAll();

int main() {
    TestAll();

//    /*
    Json::Document document = Json::Load(cin);
    Manager manager = BuildManager(document);
    Json::Save(cout, BuildResponse(manager, document));
//     */

    return 0;
}

void Test1() {
    ifstream in("input1.json");
    ifstream expected("expected1.json");
    ostringstream out;
    ostringstream out_expected;

    Json::Document document = Json::Load(in);
    Manager manager = BuildManager(document);
    Json::Save(out, BuildResponse(manager, document));

    Json::Document document_expected = Json::Load(expected);
    Json::Save(out_expected, document_expected);

    ASSERT_EQUAL(out.str(), out_expected.str())

    in.close();
    expected.close();
}

void Test2() {
    ifstream in("input2.json");
    ifstream expected("expected2.json");
    ostringstream out;
    ostringstream out_expected;

    Json::Document document = Json::Load(in);
    Manager manager = BuildManager(document);
    Json::Save(out, BuildResponse(manager, document));

    Json::Document document_expected = Json::Load(expected);
    Json::Save(out_expected, document_expected);

    ASSERT_EQUAL(out.str(), out_expected.str())

    in.close();
    expected.close();
}

void Test3() {
    ifstream in("input3.json");
    ifstream expected("expected3.json");
    ostringstream out;
    ostringstream out_expected;

    Json::Document document = Json::Load(in);
    Manager manager = BuildManager(document);
    Json::Save(out, BuildResponse(manager, document));

    Json::Document document_expected = Json::Load(expected);
    Json::Save(out_expected, document_expected);

    ASSERT_EQUAL(out.str(), out_expected.str())

    in.close();
    expected.close();
}

void Test() {
    ifstream in("input.json");
    ifstream expected("expected.json");
    ostringstream out;
    ostringstream out_expected;

    Json::Document document = Json::Load(in);
    Manager manager = BuildManager(document);
    Json::Save(out, BuildResponse(manager, document));

    Json::Document document_expected = Json::Load(expected);
    Json::Save(out_expected, document_expected);

//    ASSERT_EQUAL(out.str(), out_expected.str())
    ASSERT_EQUAL(document, document_expected)

    in.close();
    expected.close();
}


void TestAll() {
    TestRunner tr;
    RUN_TEST(tr, Test1);
//    RUN_TEST(tr, Test2);
//    RUN_TEST(tr, Test3);
//    RUN_TEST(tr, Test);
}
