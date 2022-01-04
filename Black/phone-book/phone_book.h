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

    [[nodiscard]] ContactRange FindByNamePrefix(std::string_view name_prefix) const {
        if (name_prefix.empty()) {
            return IteratorRange{contacts.begin(), contacts.end()};
        }

        auto first = std::lower_bound(contacts.begin(), contacts.end(), name_prefix,
                                      [](const Contact &contact, std::string_view name_prefix) {
                                          auto head = Head(contact.name, static_cast<int>(name_prefix.size()));
                                          return std::lexicographical_compare(head.begin(), head.end(),
                                                                              name_prefix.begin(), name_prefix.end());
                                      });
        auto last = std::upper_bound(first, contacts.end(), name_prefix,
                                     [](std::string_view name_prefix, const Contact &contact) {
                                         auto head = Head(contact.name, static_cast<int>(name_prefix.size()));
                                         return std::lexicographical_compare(
                                                                             name_prefix.begin(), name_prefix.end(),
                                                                             head.begin(), head.end());
                                     });

        return IteratorRange{first, last};
    }

    void SaveTo(std::ostream &output) const {
        PhoneBookSerialize::ContactList contactList;
        for (const auto &contact: contacts) {
            auto contactS = contactList.add_contact();
            contactS->set_name(contact.name);
            if (contact.birthday) {
                auto birthdayS = contactS->mutable_birthday();
                birthdayS->set_day(contact.birthday->day);
                birthdayS->set_month(contact.birthday->month);
                birthdayS->set_year(contact.birthday->year);
            }
            if (!contact.phones.empty()) {
            }
            for (const auto &phone_number: contact.phones) {
                contactS->add_phone_number(phone_number);
            }
        }
        contactList.SerializeToOstream(&output);
    }

private:
    Contacts contacts;
};

PhoneBook DeserializePhoneBook(std::istream &input) {
    std::vector<Contact> contacts;
    PhoneBookSerialize::ContactList contactList;
    contactList.ParseFromIstream(&input);
    for (const auto &contactP: contactList.contact()) {
        Contact contact;
        contact.name = contactP.name();
        if (contactP.has_birthday()) {
            contact.birthday->day = contactP.birthday().day();
            contact.birthday->month = contactP.birthday().month();
            contact.birthday->year = contactP.birthday().year();
        }
        for (const auto &phone_number: contactP.phone_number()) {
            contact.phones.push_back(phone_number);
        }
        contacts.push_back(std::move(contact));
    }
    return PhoneBook{move(contacts)};
}
