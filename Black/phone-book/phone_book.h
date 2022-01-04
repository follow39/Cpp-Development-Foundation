#pragma once

#include "iterator_range.h"
#include "contact.pb.h"

#include <optional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iosfwd>

struct Date {
    int year, month, day;
};

struct Contact {
    std::string name;
    std::optional<Date> birthday;
    std::vector<std::string> phones;
};

class PhoneBook {
public:
    using Contacts = std::vector<Contact>;
    using ContactRange = IteratorRange<Contacts::const_iterator>;

    explicit PhoneBook(std::vector<Contact> new_contacts)
            : contacts(std::make_move_iterator(new_contacts.begin()),
                       std::make_move_iterator(new_contacts.end())) {
        std::sort(contacts.begin(), contacts.end(), [](const auto &lhs, const auto &rhs) {
            return lhs.name < rhs.name;
        });
    }

    [[nodiscard]] ContactRange FindByNamePrefix(std::string_view name_prefix) const;

    void SaveTo(std::ostream &output) const;

private:
    Contacts contacts;
};

PhoneBook DeserializePhoneBook(std::istream &input);
