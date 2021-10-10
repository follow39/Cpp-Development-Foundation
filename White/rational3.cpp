#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;


int GCD(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (a > 0 && b > 0) {
        if (a > b) {
            a %= b;
        } else {
            b %= a;
        }
    }
    return a + b;
}
int LCM(int a, int b) {
    a = abs(a);
    b = abs(b);
    return (a*b)/GCD(a,b);
}

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
    int p;
    int q;
};

Rational operator+(const Rational& lhs, const Rational& rhs) {
    int lcm = LCM(lhs.Denominator(), rhs.Denominator());
    return Rational{lhs.Numerator()*lcm/lhs.Denominator() + rhs.Numerator()*lcm/rhs.Denominator(), lcm};
}
Rational operator-(const Rational& lhs, const Rational& rhs) {
    int lcm = LCM(lhs.Denominator(), rhs.Denominator());
    return Rational{lhs.Numerator()*lcm/lhs.Denominator() - rhs.Numerator()*lcm/rhs.Denominator(), lcm};
}
Rational operator*(const Rational& lhs, const Rational& rhs) {
    return Rational{lhs.Numerator()*rhs.Numerator(), lhs.Denominator()*rhs.Denominator()};
}
Rational operator/(const Rational& lhs, const Rational& rhs) {
    return Rational{lhs.Numerator()*rhs.Denominator(), lhs.Denominator()*rhs.Numerator()};
}
bool operator==(const Rational& lhs, const Rational& rhs) {
    return (lhs.Numerator() == rhs.Numerator()) && (lhs.Denominator() == rhs.Denominator());
}

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

    cout << "OK1" << endl;

    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 1;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 2;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 3;
        }
    }

    cout << "OK2" << endl;

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK3" << endl;
    return 0;
}



