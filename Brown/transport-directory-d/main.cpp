#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>

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

vector<string> ReadRequests(istream &is) {
    size_t n = 0;
    is >> n;
    is.ignore(1);

    vector<string> result;
    while (n-- > 0) {
        string line;
        getline(is, line);
        result.push_back(line);
    }
    return move(result);
}

CreationRequestType ParseCreationRequestType(const string &request) {
    CreationRequestType result;
    if (request[0] == 'S') {
        result = CreationRequestType::ADD_STOP;
    } else {
        result = CreationRequestType::ADD_BUS;
    }
    return result;
}

void ProcessCreationRequest(Manager &manager, const string &request) {
    CreationRequestType type = ParseCreationRequestType(request);
    if (type == CreationRequestType::ADD_BUS) {
        manager.AddBus(Bus(request));
    } else if (type == CreationRequestType::ADD_STOP) {
        manager.AddStop(Stop(request));
    }
}

Manager BuildManager(vector<string> requests) {
    Manager manager;
    for (auto &request: requests) {
        ProcessCreationRequest(manager, request);
    }
    manager.UpdateLengths();
    return move(manager);
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

void ProcessPrintRequest(ostream &os, const Manager &manager, const string &request) {
    PrintRequestType type = ParsePrintRequestType(request);
    if (type == PrintRequestType::PRINT_BUS) {
        os << manager.GetBusInfo(string(request.substr(request.find(' ') + 1, string_view::npos))) << '\n';
    } else if (type == PrintRequestType::PRINT_STOP) {
        os << manager.GetStopInfo(string(request.substr(request.find(' ') + 1, string_view::npos))) << '\n';
    }
}

void ProcessPrintRequests(ostream &os, const Manager &manager, const vector<string> &requests) {
    for (const auto &request: requests) {
        ProcessPrintRequest(os, manager, request);
    }
}

int main() {
//    cout.precision(6);

//    Manager manager = BuildManager(ReadRequests(cin));
//    ProcessPrintRequests(cout, manager, ReadRequests(cin));

    fstream f("input.json");

    Json::Document document = Json::Load(f);

    return 0;
}
