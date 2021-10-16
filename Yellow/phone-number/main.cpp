#include <iostream>
#include "phone_number.h"

using namespace std;

int main()
{
    PhoneNumber ph{"+7-981-775-69-49"};

    cout << ph.GetInternationalNumber();

    return 0;
}
