#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
    Person(const string& name, const string& type)
        : Name(name),
          Type(type) {}

    virtual void  Walk(const string& destination) const {
        cout << Type << ": " << Name << " walks to: " << destination << endl;
    }

    string Log() const {
        return Type + ": " + Name;
    }

    const string Name;
    const string Type;
};

class Student : public Person {
public:
    Student(const string& name, const string& favouriteSong)
        : Person(name, "Student"),
          FavouriteSong(favouriteSong) {}

    void Learn() const {
        cout << Log() << " learns" << endl;
    }

    void Walk(const string& destination) const override {
        this->Person::Walk(destination);
        this->SingSong();
    }

    void SingSong() const {
        cout << Log() << " sings a song: " << FavouriteSong << endl;
    }

    const string FavouriteSong;
};


class Teacher : public Person {
public:
    Teacher(const string& name, const string& subject)
        : Person(name, "Teacher"),
          Subject(subject) {}

    void Teach() const {
        cout << Log() << " teaches: " << Subject << endl;
    }

private:
    string Subject;
};


class Policeman : public Person{
public:
    Policeman(const string& name)
        : Person(name, "Policeman") {}

    void Check(const Person& p) const {
        cout << Log() << " checks " << p.Type << ". " << p.Type << "'s name is: " << p.Name << endl;
    }

public:
};

void VisitPlaces(const Person& person, const vector<string>& places) {
    for (const auto& p : places) {
        person.Walk(p);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
