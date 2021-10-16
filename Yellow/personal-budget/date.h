#ifndef DATE_H
#define DATE_H

class Date {
public:
    Date();
    Date(int new_year, int new_month, int new_day);
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
    Date& operator++();
private:
    int year;
    int month;
    int day;
};

#endif // DATE_H
