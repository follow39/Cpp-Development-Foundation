#include "requests.h"
#include "transport_router.h"

#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

namespace Requests {

    Json::Dict Stop::Process(const TransportCatalog &db) const {
        const auto *stop = db.GetStop(name);
        Json::Dict dict;
        if (!stop) {
            dict["error_message"] = Json::Node("not found"s);
        } else {
            vector<Json::Node> bus_nodes;
            bus_nodes.reserve(stop->bus_names.size());
            for (const auto &bus_name: stop->bus_names) {
                bus_nodes.emplace_back(bus_name);
            }
            dict["buses"] = Json::Node(move(bus_nodes));
        }
        return dict;
    }

    Json::Dict Bus::Process(const TransportCatalog &db) const {
        const auto *bus = db.GetBus(name);
        Json::Dict dict;
        if (!bus) {
            dict["error_message"] = Json::Node("not found"s);
        } else {
            dict = {
                    {"stop_count",        Json::Node(static_cast<int>(bus->stop_count))},
                    {"unique_stop_count", Json::Node(static_cast<int>(bus->unique_stop_count))},
                    {"route_length",      Json::Node(bus->road_route_length)},
                    {"curvature",         Json::Node(bus->road_route_length / bus->geo_route_length)},
            };
        }
        return dict;
    }

    struct RouteItemResponseBuilder {
        Json::Dict operator()(const TransportRouter::RouteInfo::BusItem &bus_item) const {
            return Json::Dict{
                    {"type",       Json::Node("Bus"s)},
                    {"bus",        Json::Node(bus_item.bus_name)},
                    {"time",       Json::Node(bus_item.time)},
                    {"span_count", Json::Node(static_cast<int>(bus_item.span_count))}
            };
        }

        Json::Dict operator()(const TransportRouter::RouteInfo::WaitItem &wait_item) const {
            return Json::Dict{
                    {"type",      Json::Node("Wait"s)},
                    {"stop_name", Json::Node(wait_item.stop_name)},
                    {"time",      Json::Node(wait_item.time)},
            };
        }
    };

    Json::Dict Route::Process(const TransportCatalog &db) const {
        Json::Dict dict;
        const auto route = db.FindRoute(stop_from, stop_to);
        if (!route) {
            dict["error_message"] = Json::Node("not found"s);
        } else {
            dict["total_time"] = Json::Node(route->total_time);
            vector<Json::Node> items;
            items.reserve(route->items.size());
            for (const auto &item: route->items) {
                items.emplace_back(visit(RouteItemResponseBuilder{}, item));
            }

            dict["items"] = move(items);
        }

        return dict;
    }

    Json::Dict SvgMap::Process(const TransportCatalog &db) const {
        auto initExpr = [&db] {
            stringstream ss;
#if DEBUGIO
            ss << db.RenderMap();
#else
            ss << std::quoted(db.RenderMap());
#endif
            std::string result = ss.str();
#if DEBUGIO
#else
            result.pop_back();
            result.erase(result.begin());
#endif
            return result;
        };
        const std::string renderedMap = initExpr();
        Json::Dict dict;
        if (renderedMap.empty()) {
            dict["error_message"] = Json::Node("not found"s);
        } else {
            dict = {
                    {"map", renderedMap}
            };
        }
        return dict;
    }

    variant<Stop, Bus, Route, SvgMap> Read(const Json::Dict &attrs) {
        const string &type = attrs.at("type").AsString();
        if (type == "Bus") {
            return Bus{attrs.at("name").AsString()};
        } else if (type == "Stop") {
            return Stop{attrs.at("name").AsString()};
        } else if (type == "Route") {
            return Route{attrs.at("from").AsString(), attrs.at("to").AsString()};
        } else if (type == "Map") {
            return SvgMap{};
        }
        return {};
    }

    vector<Json::Node> ProcessAll(const TransportCatalog &db, const vector<Json::Node> &requests) {
        vector<Json::Node> responses;
        responses.reserve(requests.size());
        for (const Json::Node &request_node: requests) {
            Json::Dict dict = visit([&db](const auto &request) {
                                        return request.Process(db);
                                    },
                                    Requests::Read(request_node.AsMap()));
            dict["request_id"] = Json::Node(request_node.AsMap().at("id").AsInt());
            responses.emplace_back(dict);
        }
        return responses;
    }

}
