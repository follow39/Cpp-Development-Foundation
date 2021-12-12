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
//    TestAll();

    Json::Document document = Json::Load(cin);
    Manager manager = BuildManager(document);
    Json::Save(cout, BuildResponse(manager, document));

    return 0;
}

void TestPath(const string& inputPath, const string& expectedPath, const string& outputPath = "output.json") {
    ifstream fin(inputPath);
    ofstream fout(outputPath);
    Json::Document document = Json::Load(fin);
    Manager manager = BuildManager(document);
    Json::Save(fout, BuildResponse(manager, document));
    fin.close();
    fout.close();

    ifstream fresult(outputPath);
    ifstream expected(expectedPath);
    Json::Document document_result = Json::Load(fresult);
    Json::Document document_expected = Json::Load(expected);
//    ASSERT_EQUAL(document_result, document_expected)
    fresult.close();
    expected.close();
}

void Test1() {
    TestPath("input1.json", "expected1.json", "output.json");
}

void Test2() {
    TestPath("input2.json", "expected2.json", "output.json");
}

void Test3() {
    TestPath("input3.json", "expected3.json", "output.json");
}

void TestFinal() {
    TestPath("input.json", "expected.json", "output.json");
}


void TestAll() {
    TestRunner tr;
    RUN_TEST(tr, Test1);
    RUN_TEST(tr, Test2);
    RUN_TEST(tr, Test3);
    RUN_TEST(tr, TestFinal);
}
