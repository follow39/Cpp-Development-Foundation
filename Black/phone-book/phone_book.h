#pragma once

#include "iterator_range.h"
#include "contact.pb.h"

#include <optional>
#include <string>
#include <string_view>
#include <vector>
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
    explicit PhoneBook(std::vector<Contact> new_contacts) {

    }

//    IteratorRange<???> FindByNamePrefix(std::string_view name_prefix) const;

    void SaveTo(std::ostream &output) const {

    }

private:
    std::vector<Contact> contacts;
};

PhoneBook DeserializePhoneBook(std::istream &input);
