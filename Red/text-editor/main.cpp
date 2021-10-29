#include <string>
#include <iostream>
#include <list>
#include <algorithm>
#include "test_runner.h"
using namespace std;

class Editor {
public:
    Editor() {
        cursor = text.begin();
    }
    void Left() {
        if(cursor == text.begin()) {
            return;
        }
        --cursor;
    }
    void Right() {
        if(cursor == text.end()) {
            return;
        }
        ++cursor;
    }
    void Insert(char token) {
        text.insert(cursor, token);
    }
    void Cut(size_t tokens = 1) {
        buffer.clear();
        size_t cnt = 0;
        auto it = cursor;
        while(it != text.end() && cnt < tokens) {
            buffer.push_back(*it);
            ++it;
            ++cnt;
            text.erase(cursor);
            cursor = it;
        }
    }
    void Copy(size_t tokens = 1) {
        buffer.clear();
        size_t cnt = 0;
        auto it = cursor;
        while(it != text.end() && cnt < tokens) {
            buffer.push_back(*it);
            ++it;
            ++cnt;
        }
    }
    void Paste() {
        text.insert(cursor, buffer.begin(), buffer.end());
    }
    string GetText() const {
        string result;
        result.reserve(text.size());
        for(auto it = text.begin(); it != text.end(); ++it) {

            result+= *it;
        }
        return result;
    }
private:
    static const char CURSOR_SYMBOL = '|';
    list<char> text;
    list<char> buffer;
    list<char>::iterator cursor;
};

void TypeText(Editor& editor, const string& text) {
    for(char c : text) {
        editor.Insert(c);
    }
}

void TestEditing() {
    {
        Editor editor;

        const size_t text_len = 12;
        const size_t first_part_len = 7;
        TypeText(editor, "hello, world");
        for(size_t i = 0; i < text_len; ++i) {
            editor.Left();
        }
        editor.Cut(first_part_len);
        for(size_t i = 0; i < text_len - first_part_len; ++i) {
            editor.Right();
        }
        TypeText(editor, ", ");
        editor.Paste();
        editor.Left();
        editor.Left();
        editor.Cut(3);

        ASSERT_EQUAL(editor.GetText(), "world, hello");
    }
    {
        Editor editor;

        TypeText(editor, "misprnit");
        editor.Left();
        editor.Left();
        editor.Left();
        editor.Cut(1);
        editor.Right();
        editor.Paste();

        ASSERT_EQUAL(editor.GetText(), "misprint");
    }
}

void TestReverse() {
    Editor editor;

    const string text = "esreveR";
    for(char c : text) {
        editor.Insert(c);
        editor.Left();
    }

    ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
    Editor editor;
    ASSERT_EQUAL(editor.GetText(), "");

    editor.Left();
    editor.Left();
    editor.Right();
    editor.Right();
    editor.Copy(0);
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
    Editor editor;

    editor.Paste();
    TypeText(editor, "example");
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Right();
    editor.Paste();
    editor.Copy(0);
    editor.Paste();
    editor.Left();
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestEditing);
    RUN_TEST(tr, TestReverse);
    RUN_TEST(tr, TestNoText);
    RUN_TEST(tr, TestEmptyBuffer);
    return 0;
}
