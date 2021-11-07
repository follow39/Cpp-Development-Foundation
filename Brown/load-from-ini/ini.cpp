#include "ini.h"
#include <iostream>
#include <string>
#include <string_view>

using namespace std;

namespace Ini {
    pair<string, string> Split(string_view line, char by) {
        size_t pos = line.find(by);
        string_view left = line.substr(0, pos);

        return {static_cast<string>(left),
                static_cast<string>(line.substr(pos + 1))};
    }

    string Unquote(string_view value) {
        if (!value.empty() && value.front() == '[') {
            value.remove_prefix(1);
        }
        if (!value.empty() && value.back() == ']') {
            value.remove_suffix(1);
        }
        return static_cast<string>(value);
    }

    Section &Document::AddSection(string name) {
        auto it = sections.insert({name, Section{}});
        return it.first->second;
    }

    const Section &Document::GetSection(const string &name) const {
        return sections.at(name);
    }

    size_t Document::SectionCount() const {
        return sections.size();
    }

    Document Load(istream &input) {
        Document result;
        while (input) {
            string section_name;
            getline(input, section_name);
            if (section_name[0] == '[') {
                Section& current_section = result.AddSection(Unquote(section_name));
                while (input) {
                    string section_line;
                    getline(input, section_line);
                    if (section_line.empty()) {
                        break;
                    }
                    auto temp = Split(section_line, '=');
                    current_section.insert(temp);
                }
            }
        }
        return result;
    }
}