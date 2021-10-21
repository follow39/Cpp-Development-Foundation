#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Figure {
public:
    virtual string Name() const = 0;
    virtual int Perimeter () const = 0;
    virtual int Area() const = 0;
protected:
    string name;
    int perimeter;
    double area;
};

class Triangle : public Figure {
public:
    Triangle(int a, int b, int c) {
        name = "Triangle";
        perimeter = a + b + c;
        double p = static_cast<double>(perimeter) / 2;
        area = sqrt(p) * (p - a) * (p - b) * (p - c);
    }
    string Name() const override {
        return name;
    }
    int Perimeter() const {
        return perimeter;
    }
    int Area() const {
        return area;
    }
};

class Rectangle : public Figure {
public:
    Rectangle(int width, int height) {
        name = "Rectangle";
        perimeter = width * 2 + height * 2;
        area = width * height;
    }
    string Name() const override {
        return name;
    }
    int Perimeter() const {
        return perimeter;
    }
    int Area() const {
        return area;
    }
};

class Circle : public Figure {
public:
    Circle(int r) {
        name = "Rectangle";
        perimeter = 2 * 3.14 * r;
        area = 3.14 * pow(r, 2);
    }
    string Name() const override {
        return name;
    }
    int Perimeter() const {
        return perimeter;
    }
    int Area() const {
        return area;
    }
};


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
