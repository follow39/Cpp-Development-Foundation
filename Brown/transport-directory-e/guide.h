#pragma once

#include "graph.h"
#include "json.h"
#include "router.h"

#include <string>
#include <optional>

struct PathRequest {
    std::string from;
    std::string to;
};

struct TimingInfo {
    int bus_wait_time = 0;
    int bus_velocity = 0;
};

struct PathItem {
    std::string type;
    std::string stop_name;
    int time = 0;

    [[nodiscard]] Json::Node ToJson() const {
        std::map<std::string, Json::Node> result;
        result.emplace("type", Json::Node(type));
        result.emplace("stop_name", Json::Node(stop_name));
        result.emplace("time", Json::Node(time));
    }
};

struct Path {
    int total_time = 0;
    std::vector<PathItem> items;

    [[nodiscard]] Json::Node ToJson() const {
        std::map<std::string, Json::Node> result;
        std::vector<Json::Node> result_items;
        for (const auto &item: items) {
            result_items.emplace_back(item.ToJson());
        }
        result.emplace("total_time", Json::Node(total_time));
        result.emplace("items", Json::Node(std::move(result_items)));
        return Json::Node{std::move(result)};
    }
};

template<typename Weight>
class Guide {
public:
    Guide(const std::vector<std::string> &new_stopsIndex,
          const std::unordered_map<std::string, Graph::VertexId> &new_stopsInvertedIndex,
          std::optional<Graph::Router<Weight>> new_router)
            : stopsIndex(new_stopsIndex),
              stopsInvertedIndex(new_stopsInvertedIndex),
              router(move(new_router)) {}


    std::optional<Path> GetPath(const PathRequest &pathRequest) {
        auto routerInfo = router->BuildRoute(stopsInvertedIndex.at(pathRequest.from),
                                             stopsInvertedIndex.at(pathRequest.to));

        Path result;


        return result;
    }

private:
    const std::vector<std::string> &stopsIndex;
    const std::unordered_map<std::string, Graph::VertexId> &stopsInvertedIndex;
    std::optional<Graph::Router<Weight>> router;
};