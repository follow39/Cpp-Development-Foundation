#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <iomanip>
#include <cmath>

using namespace std;

class Figure {
public:
    virtual string Name() const = 0;
    virtual double Perimeter () const = 0;
    virtual double Area() const = 0;
protected:
    string name;
    double perimeter;
    double area;
};

class Triangle : public Figure {
public:
    Triangle(double a, double b, double c) {
        name = "Triangle";
        perimeter = a + b + c;
        double p = perimeter / 2;
        area = sqrt(p * (p - a) * (p - b) * (p - c));
    }
    string Name() const override {
        return name;
    }
    double Perimeter() const override {
        return perimeter;
    }
    double Area() const override {
        return area;
    }
};

class Rectangle : public Figure {
public:
    Rectangle(double width, double height) {
        name = "Rectangle";
        perimeter = width * 2 + height * 2;
        area = width * height;
    }
    string Name() const override {
        return name;
    }
    double Perimeter() const override {
        return perimeter;
    }
    double Area() const override {
        return area;
    }
};

class Circle : public Figure {
public:
    Circle(double r) {
        name = "Rectangle";
        perimeter = 2 * 3.14 * r;
        area = 3.14 * pow(r, 2);
    }
    string Name() const override {
        return name;
    }
    double Perimeter() const override {
        return perimeter;
    }
    double Area() const override {
        return area;
    }
};

shared_ptr<Figure> CreateFigure(istream& is) {
    shared_ptr<Figure> result;
    string type;
    is >> type;
    if(type == "TRIANGLE") {
        int a = 0;
        int b = 0;
        int c = 0;
        is >> a >> b >> c;
        result = make_shared<Triangle>(a, b, c);
    } else if(type == "RECT") {
        int width = 0;
        int height = 0;
        is >> width >> height;
        result = make_shared<Rectangle>(width, height);
    } else if(type == "CIRCLE") {
        int r = 0;
        is >> r;
        result = make_shared<Circle>(r);
    }

    return result;
}

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            // Пропускаем "лишние" ведущие пробелы.
            // Подробнее об std::ws можно узнать здесь:
            // https://en.cppreference.com/w/cpp/io/manip/ws
            is >> ws;
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}
