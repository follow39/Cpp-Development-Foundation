#include <iostream>
#include <string>
#include <sstream>

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
        if(denominator == 0)
        {
            throw invalid_argument("denominator is zero");
        }
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
    long lcm = LCM(lhs.Denominator(), rhs.Denominator());
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
    if(rhs.Numerator() == 0)
    {
        throw domain_error("division by zero");
    }
    return Rational{lhs.Numerator()*rhs.Denominator(), lhs.Denominator()*rhs.Numerator()};
}
bool operator==(const Rational& lhs, const Rational& rhs) {
    return (lhs.Numerator() == rhs.Numerator()) && (lhs.Denominator() == rhs.Denominator());
}
bool operator<(const Rational& lhs, const Rational& rhs) {
    return lhs.Numerator()*rhs.Denominator() < rhs.Numerator()*lhs.Denominator();
}
istream& operator>>(istream& stream, Rational& rational) {
//    if(stream.eof())
//        return stream;

    int p = 0;
    int q = 1;
    char sym;

    if(stream >> p) {
        stream >> sym;
        if(sym == '/' && stream >> q) {
            rational = Rational{p, q};
        }
    }

    return stream;
}
ostream& operator<<(ostream& stream, const Rational& rational) {
    stream << rational.Numerator() << '/' << rational.Denominator();

    return stream;
}

int main() {
    try {
        Rational r(1, 0);
        cout << "Doesn't throw in case of zero denominator" << endl;
        return 1;
    } catch (invalid_argument&) {
    }

    try {
        auto x = Rational(1, 2) / Rational(0, 1);
        cout << "Doesn't throw in case of division by zero" << endl;
        return 2;
    } catch (domain_error&) {
    }

    cout << "OK" << endl;

    return 0;
}
