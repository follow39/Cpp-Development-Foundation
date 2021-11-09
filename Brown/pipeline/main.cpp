#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <iomanip>
#include <vector>
#include <iterator>

using namespace std;


struct Email {
    string from;
    string to;
    string body;
};


class Worker {
public:
    virtual ~Worker() = default;

    virtual void Process(unique_ptr<Email> email) = 0;

    virtual void Run() {
        // только первому worker-у в пайплайне нужно это имплементировать
        throw logic_error("Unimplemented");
    }

protected:
    unique_ptr<Worker> next = nullptr;

    // реализации должны вызывать PassOn, чтобы передать объект дальше
    // по цепочке обработчиков
    void PassOn(unique_ptr<Email> email) const {
        if (next) {
            next->Process(move(email));
        }
    }

public:
    void SetNext(unique_ptr<Worker> new_next) {
        next = move(new_next);
    }
};


class Reader : public Worker {
public:
    explicit Reader(istream &new_is)
            : is(new_is) {}

    void Process(unique_ptr<Email> email) override {
        PassOn(move(email));
    }

    void Run() override {
        vector<unique_ptr<Email>> emails;
        while (is) {
            Email email;
            getline(is, email.from);
            getline(is, email.to);
            getline(is, email.body);
            emails.emplace_back(make_unique<Email>(move(email)));
        }
        for (auto &email: emails) {
            PassOn(move(email));
        }
    }

private:
    istream &is;
};


class Filter : public Worker {
public:
    using Function = function<bool(const Email &)>;

public:
    explicit Filter(Function pred)
            : predicate(move(pred)) {}

    void Process(unique_ptr<Email> email) override {
        if (predicate(*email)) {
            PassOn(move(email));
        }
    }

private:
    Function predicate;
};


class Copier : public Worker {
public:
    explicit Copier(string new_receiver)
            : receiver(move(new_receiver)) {}

    void Process(unique_ptr<Email> email) override {
        Email temp{*email};
        PassOn(move(email));
        if (temp.to != receiver) {
            temp.to = receiver;
            PassOn(make_unique<Email>(move(temp)));
        }
    }

private:
    const string receiver;
};


class Sender : public Worker {
public:
    explicit Sender(ostream &new_os)
            : os(new_os) {}

    void Process(unique_ptr<Email> email) override {
        os << email->from << '\n';
        os << email->to << '\n';
        os << email->body << endl;
        PassOn(move(email));
    }

private:
    ostream &os;
};


// реализуйте класс
class PipelineBuilder {
public:
    // добавляет в качестве первого обработчика Reader
    explicit PipelineBuilder(istream &in) {
        workers.emplace_back(make_unique<Reader>(in));
    }

    // добавляет новый обработчик Filter
    PipelineBuilder &FilterBy(Filter::Function filter) {
        workers.emplace_back(make_unique<Filter>(move(filter)));
        return *this;
    }

    // добавляет новый обработчик Copier
    PipelineBuilder &CopyTo(string recipient) {
        workers.emplace_back(make_unique<Copier>(move(recipient)));
        return *this;
    }

    // добавляет новый обработчик Sender
    PipelineBuilder &Send(ostream &out) {
        workers.emplace_back(make_unique<Sender>(out));
        return *this;
    }

    // возвращает готовую цепочку обработчиков
    unique_ptr<Worker> Build() {
        for (long i = static_cast<long>(workers.size()) - 2; i >= 0; --i) {
            workers[i]->SetNext(move(workers[i + 1]));
        }
        return move(workers[0]);
    }

private:
    vector<unique_ptr<Worker>> workers;
};


void TestSanity() {
    string input = (
            "erich@example.com\n"
            "richard@example.com\n"
            "Hello there\n"

            "erich@example.com\n"
            "ralph@example.com\n"
            "Are you sure you pressed the right button?\n"

            "ralph@example.com\n"
            "erich@example.com\n"
            "I do not make mistakes of that kind\n"
    );
    istringstream inStream(input);
    ostringstream outStream;

    PipelineBuilder builder(inStream);
    builder.FilterBy([](const Email &email) {
        return email.from == "erich@example.com";
    });
    builder.CopyTo("richard@example.com");
    builder.Send(outStream);
    auto pipeline = builder.Build();

    pipeline->Run();

    string expectedOutput = (
            "erich@example.com\n"
            "richard@example.com\n"
            "Hello there\n"

            "erich@example.com\n"
            "ralph@example.com\n"
            "Are you sure you pressed the right button?\n"

            "erich@example.com\n"
            "richard@example.com\n"
            "Are you sure you pressed the right button?\n"
    );

    ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSanity);
    return 0;
}
