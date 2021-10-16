#include "phone_number.h"
#include <sstream>
#include <exception>


PhoneNumber::PhoneNumber(const string &international_number) {
    stringstream ss(international_number);
    char ch1 = 0;
    char ch2 = 0;
    char ch3 = 0;
    string country_code_;
    string city_code_;
    string local_number_;

    ss >> ch1;
    ss.get(country_code_.data(), '-');
    ss >> ch2;
    ss.get(city_code_.data(), '-');
    ss >> ch3;
    ss.get(local_number_.data(), '-');

    if(ch1 != '+' || ch2 != '-' || ch3 != '-') {
        throw invalid_argument(international_number);
    }
}

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

string PhoneNumber::GetCityCode() const {
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    return "+"s + GetCountryCode() + "-"s + GetCityCode() +
            "-" + GetLocalNumber();
}
