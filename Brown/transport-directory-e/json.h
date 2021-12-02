#pragma once

#include <iostream>
#include <map>
#include <string>
#include <variant>
#include <vector>

namespace Json {
    class Node;

    class Document;

    Document Load(std::istream &input);

    void Save(std::ostream &output, const Document &document);

    class Node : public std::variant<std::vector<Node>,
            std::map<std::string, Node>,
            int,
            double,
            bool,
            std::string> {
    public:
        using variant::variant;

        [[nodiscard]] const auto &AsArray() const {
            return std::get<std::vector<Node>>(*this);
        }

        [[nodiscard]] const auto &AsMap() const {
            return std::get<std::map<std::string, Node>>(*this);
        }

        [[nodiscard]]  int AsInt() const {
            if (!std::holds_alternative<int>(*this)) {
                return static_cast<int>(std::get<double>(*this));
            }
            return std::get<int>(*this);
        }

        [[nodiscard]]   double AsDouble() const {
            if (!std::holds_alternative<double>(*this)) {
                return std::get<int>(*this);
            }
            return std::get<double>(*this);
        }

        [[nodiscard]]    bool AsBool() const {
            return std::get<bool>(*this);
        }

        [[nodiscard]]   const auto &AsString() const {
            return std::get<std::string>(*this);
        }

        void AddId(int id) {
            std::get<std::map<std::string, Node>>(*this).emplace("request_id", id);
        }
    };

    class Document {
    public:
        explicit Document(Node root);

        [[nodiscard]] const Node &GetRoot() const;

        bool operator==(const Document &other) const {
            return root == other.root;
        }

        friend std::ostream &operator<<(std::ostream &os, const Document &document) {
            Save(os, document);
            return os;
        }

    private:
        Node root;
    };

}