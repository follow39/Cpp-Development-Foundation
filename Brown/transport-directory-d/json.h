#pragma once

#include <istream>
#include <map>
#include <string>
#include <variant>
#include <vector>

namespace Json {

    class Node : public std::variant<std::vector<Node>,
            std::map<std::string, Node>,
            int,
            double,
            bool,
            std::string> {
    public:
        using variant::variant;

        const auto &AsArray() const {
            return std::get<std::vector<Node>>(*this);
        }

        const auto &AsMap() const {
            return std::get<std::map<std::string, Node>>(*this);
        }

        int AsInt() const {
            if (!std::holds_alternative<int>(*this)) {
                return static_cast<int>(std::get<double>(*this));
            }
            return std::get<int>(*this);
        }

        double AsDouble() const {
            if (!std::holds_alternative<double>(*this)) {
                return std::get<int>(*this);
            }
            return std::get<double>(*this);
        }

        bool AsBool() const {
            return std::get<bool>(*this);
        }

        const auto &AsString() const {
            return std::get<std::string>(*this);
        }

        void AddId(int id) {
            std::get<std::map<std::string, Node>>(*this).emplace("request_id", id);
        }
    };

    class Document {
    public:
        explicit Document(Node root);

        const Node &GetRoot() const;

    private:
        Node root;
    };

    Document Load(std::istream &input);

    void Save(std::ostream &output, Document document);

}