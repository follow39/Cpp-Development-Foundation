#ifndef DATE_H
#define DATE_H

const int MonthsCount = 12;
const int DaysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int FebruaryInLeapYear = 29;

class Date {
public:
    Date(int new_year, int new_month, int new_day);
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
    void operator++();
private:
    int year;
    int month;
    int day;
};

int GetDaysCount(int year, int month);
//void operator++(Date& d);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator<(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
//int operator-(const);

#endif // DATE_H
