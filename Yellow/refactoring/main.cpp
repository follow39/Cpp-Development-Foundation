#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
    Person(string name, string type)
        : Name(name),
          Type(type) {}

    virtual void  Walk(string destination) const {
        cout << Type << ": " << Name << " walks to: " << destination << endl;
    }

    const string Name;
    const string Type;
};

class Student : public Person {
public:
    Student(string name, string favouriteSong)
        : Person(name, "Student"),
          FavouriteSong(favouriteSong) {}

    void Learn() {
        cout << "Student: " << Name << " learns" << endl;
    }

    void Walk(string destination) const override {
        cout << "Student: " << Name << " walks to: " << destination << endl;
        this->SingSong();
    }

    void SingSong() const {
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }

    const string FavouriteSong;
};


class Teacher : public Person {
public:
    Teacher(string name, string subject)
        : Person(name, "Teacher"),
          Subject(subject) {}

    void Teach() {
        cout << "Teacher: " << Name << " teaches: " << Subject << endl;
    }

private:
    string Subject;
};


class Policeman : public Person{
public:
    Policeman(string name)
        : Person(name, "Policeman") {}

    void Check(const Person& p) const {
        cout << "Policeman: " << Name << " checks " << p.Type << ". " << p.Type << "'s name is: " << p.Name << endl;
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
