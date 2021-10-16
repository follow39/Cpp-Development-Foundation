#include <iostream>
#include "phone_number.h"

using namespace std;

int main()
{
    PhoneNumber ph{"+7-981-775-69-49"};

    cout << ph.GetCountryCode() << endl;
    cout << ph.GetCityCode() << endl;
    cout << ph.GetLocalNumber() << endl;
    cout << ph.GetInternationalNumber() << endl;

    return 0;
}
