#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Stats {
public:
    Stats() {
        for(const auto& method : METHODS) {
            map_method[method];
        }
        for(const auto& uri : URIS) {
            map_uri[uri];
        }
    }

    void AddMethod(string_view method) {
        if(map_method.count(method) == 0) {
            method = METHODS.back();
        }
        ++map_method[method];
    }
    void AddUri(string_view uri) {
        if(map_uri.count(uri) == 0) {
            uri = URIS.back();
        }
        ++map_uri[uri];
    }
    const map<string_view, int>& GetMethodStats() const {
        return map_method;
    }
    const map<string_view, int>& GetUriStats() const {
        return map_uri;
    }
private:
    static inline const vector<string> METHODS = {"GET", "POST", "PUT", "DELETE", "UNKNOWN"};
    static inline const vector<string> URIS = {"/", "/order", "/product", "/basket", "/help", "unknown"};

    map<string_view, int> map_method;
    map<string_view, int> map_uri;
};

HttpRequest ParseRequest(string_view line) {
    HttpRequest result;
    line.remove_prefix(line.find_first_not_of(' '));
    result.method = line.substr(0, line.find(' '));
    line.remove_prefix(result.method.size() + 1);
    result.uri = line.substr(0, line.find(' '));
    line.remove_prefix(result.uri.size()+1);
    result.protocol = line;

    return result;
}
