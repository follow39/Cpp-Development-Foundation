#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;



class Rational {
public:
    Rational() {
        p = 0;
        q = 1;
    }
    Rational(int numerator, int denominator)
    {
        p = numerator;
        q = denominator;
        UpdateValue();
    }

    int Numerator() const {
        return p;
    }
    int Denominator() const {
        return q;
    }
private:
    void UpdateValue() {
        if(p == 0)
        {
            q = 1;
            return;
        }
        ReduceFraction();
        UpdateSign();
    }
    void ReduceFraction() {
        int gcd = GCD(p, q);
        p /= gcd;
        q /= gcd;
    }
    void UpdateSign() {
        if(p < 0 && q < 0) {
            p = abs(p);
            q = abs(q);
        }
        else if(p < 0 || q < 0) {
            p = -1 * abs(p);
            q = abs(q);
        }
    }
    int GCD(int a, int b) {
        while (a > 0 && b > 0) {
            if (a > b) {
                a %= b;
            } else {
                b %= a;
            }
        }
        return a + b;
    }
    int p;
    int q;
};


int main() {
    {
        const Rational r(3, 10);
        if (r.Numerator() != 3 || r.Denominator() != 10) {
            cout << "Rational(3, 10) != 3/10" << endl;
            return 1;
        }
    }

    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(-4, 6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(4, -6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1) {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }

    cout << "OK" << endl;
    return 0;
}



