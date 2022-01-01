#pragma once

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace Json {

    class Node;

    using Dict = std::map<std::string, Node>;

    class Node : std::variant<std::vector<Node>, Dict, bool, int, double, std::string> {
    public:
        using variant::variant;

        [[nodiscard]] const variant &GetBase() const { return *this; }

        [[nodiscard]] const auto &AsArray() const { return std::get<std::vector<Node>>(*this); }

        [[nodiscard]] const auto &AsMap() const { return std::get<Dict>(*this); }

        [[nodiscard]] bool AsBool() const { return std::get<bool>(*this); }

        [[nodiscard]] int AsInt() const { return std::get<int>(*this); }

        [[nodiscard]] double AsDouble() const {
            return std::holds_alternative<double>(*this) ? std::get<double>(*this) : std::get<int>(*this);
        }

        [[nodiscard]] const auto &AsString() const { return std::get<std::string>(*this); }
    };

    class Document {
    public:
        explicit Document(Node root) : root(move(root)) {}

        [[nodiscard]] const Node &GetRoot() const {
            return root;
        }

    private:
        Node root;
    };

    Node LoadNode(std::istream &input);

    Document Load(std::istream &input);

    void PrintNode(const Node &node, std::ostream &output, size_t tabs = 1);

    template<typename Value>
    void PrintValue(const Value &value, std::ostream &output, size_t tabs = 1) {
        output << value;
    }

    template<>
    void PrintValue<std::string>(const std::string &value, std::ostream &output, size_t tabs);

    template<>
    void PrintValue<bool>(const bool &value, std::ostream &output, size_t tabs);

    template<>
    void PrintValue<std::vector<Node>>(const std::vector<Node> &nodes, std::ostream &output, size_t tabs);

    template<>
    void PrintValue<Dict>(const Dict &dict, std::ostream &output, size_t tabs);

    void Print(const Document &document, std::ostream &output, size_t tabs);

}

