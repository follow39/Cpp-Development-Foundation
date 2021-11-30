#include "json.h"

#include <cmath>

using namespace std;

namespace Json {

    Document::Document(Node root) : root(move(root)) {
    }

    const Node &Document::GetRoot() const {
        return root;
    }

    Node LoadNode(istream &input);

    Node LoadArray(istream &input) {
        vector<Node> result;

        for (char c; input >> c && c != ']';) {
            if (c != ',') {
                input.putback(c);
            }
            result.push_back(LoadNode(input));
        }

        return Node(move(result));
    }

    Node LoadNumber(istream &input) {
        int resulti = 0;
        double resultd = 0.0;
        int sign = 1;
        if (input.peek() == '-') {
            sign = -1;
            input.get();
        }
        while (isdigit(input.peek())) {
            resulti *= 10;
            resulti += input.get() - '0';
        }
        if (input.peek() == '.') {
            input.ignore(1);
            size_t temp_pow = 0;
            while (isdigit(input.peek())) {
                resultd *= 10;
                resultd += input.get() - '0';
                ++temp_pow;
            }
            resultd /= pow(10, temp_pow);
        } else {
            return Node(sign * resulti);
        }
        resultd += static_cast<double>(resulti);
        return Node(sign * resultd);
    }

    Node LoadBool(istream &input) {
        bool result = false;
        if (input.peek() == 't') {
            result = true;
            input.ignore(4);
        } else {
            result = false;
            input.ignore(5);
        }
        return result;
    }

    Node LoadString(istream &input) {
        string line;
        getline(input, line, '"');
        return Node(move(line));
    }

    Node LoadDict(istream &input) {
        map<string, Node> result;

        for (char c; input >> c && c != '}';) {
            if (c == ',') {
                input >> c;
            }

            string key = LoadString(input).AsString();
            input >> c;
            result.emplace(move(key), LoadNode(input));
        }

        return Node(move(result));
    }

    Node LoadNode(istream &input) {
        char c;
        input >> c;

        if (c == '[') {
            return LoadArray(input);
        } else if (c == '{') {
            return LoadDict(input);
        } else if (c == '"') {
            return LoadString(input);
        } else if (isdigit(c) || c == '-') {
            input.putback(c);
            return LoadNumber(input);
        } else {
            input.putback(c);
            return LoadBool(input);
        }
    }

    Document Load(istream &input) {
        return Document{LoadNode(input)};
    }

    //----------------------------SAVE--------------------------------

    string GetTabs(size_t tabs) {
        return string(tabs, '\t');
    }

    void SaveNode(ostream &output, const Node &node, size_t tabs);

    void SaveInt(ostream &output, int value) {
        output << to_string(value);
    }

    void SaveDouble(ostream &output, double value) {
        output << to_string(value);
    }

    void SaveBool(ostream &output, bool value) {
        output << (value ? "true" : "false");
    }

    void SaveString(ostream &output, const string &str) {
        output << '\"' << str << '\"';
    }

    void SaveArray(ostream &output, const vector<Node> &data, size_t tabs) {
        output << "[";
        bool first = true;
        for (auto &node: data) {
            if (!first) {
                output << ",";
            } else {
                first = false;
            }
            output << '\n';
            output << GetTabs(tabs);
            SaveNode(output, node, tabs);
        }
        if (!first) {
            output << '\n';
            output << GetTabs(tabs - 1);
        }
        output << "]";
    }

    void SaveDict(ostream &output, const map<string, Node> &data, size_t tabs) {
        output << "{";
        bool first = true;
        for (auto&[key, node]: data) {
            if (!first) {
                output << ",";
            } else {
                first = false;
            }
            output << '\n';
            output << GetTabs(tabs);
            SaveString(output, key);
            output << ": ";
            SaveNode(output, node, tabs);
        }
        output << '\n';
        output << GetTabs(tabs - 1);
        output << "}";
    }

    void SaveNode(ostream &output, const Node &node, size_t tabs = 0) {
        ++tabs;
        if (holds_alternative<int>(node)) {
            SaveInt(output, node.AsInt());
        } else if (holds_alternative<double>(node)) {
            SaveDouble(output, node.AsDouble());
        } else if (holds_alternative<bool>(node)) {
            SaveBool(output, node.AsBool());
        } else if (holds_alternative<string>(node)) {
            SaveString(output, node.AsString());
        } else if (holds_alternative<vector<Node>>(node)) {
            SaveArray(output, node.AsArray(), tabs);
        } else if (holds_alternative<map<string, Node>>(node)) {
            SaveDict(output, node.AsMap(), tabs);
        }
    }

    void Save(ostream &output, Document document) {
        output.precision(6);
        SaveNode(output, document.GetRoot());
    }
}