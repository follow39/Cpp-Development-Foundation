#include "test_runner.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <string_view>

using namespace std;

class Translator {
public:
    void Add(string_view source, string_view target) {
        auto it_source = words.insert(string{source.begin(), source.end()});
        auto it_target = words.insert(string{target.begin(), target.end()});

        string_view sv_source{*it_source.first};
        string_view sv_target{*it_target.first};

        words_forward[sv_source] = sv_target;
        words_backward[sv_target] = sv_source;
    }
    string_view TranslateForward(string_view source) const {
        if(words_forward.count(source) == 0) {
            return {};
        }
        return words_forward.at(source);
    }
    string_view TranslateBackward(string_view target) const {
        if(words_backward.count(target) == 0) {
            return {};
        }
        return words_backward.at(target);
    }

private:
    set<string> words;
    map<string_view, string_view> words_forward;
    map<string_view, string_view> words_backward;
};

void TestSimple() {
    Translator translator;
    translator.Add(string("okno"), string("window"));
    translator.Add(string("stol"), string("table"));

    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSimple);
    return 0;
}
