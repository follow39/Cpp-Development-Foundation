#include "phone_number.h"
#include <sstream>
#include <exception>


PhoneNumber::PhoneNumber(const string &international_number) {
    stringstream ss(international_number);
    char ch1 = 0;
    char ch2 = 0;
    char ch3 = 0;

    ss >> ch1;
    getline(ss, country_code_, '-');
    getline(ss, city_code_, '-');
    getline(ss, local_number_);

    if(ch1 != '+' || country_code_.empty() ||
            city_code_.empty() || local_number_.empty()) {
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
