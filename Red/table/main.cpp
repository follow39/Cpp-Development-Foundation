#include "test_runner.h"
#include <vector>
#include <utility>

using namespace std;

template <typename Unit>
class Table {
public:
    Table(size_t new_height, size_t new_width) {
        Resize(new_height, new_width);
    }
    void Resize(size_t new_height, size_t new_width) {
        if(new_height == 0 || new_width == 0) {
            table.clear();
            return;
        }
        table.resize(new_height, {});
        for(vector<Unit>& w : table) {
            w.resize(new_width, {});
        }
    }
    pair<size_t, size_t> Size() const {
        if(table.size() == 0) {
            return {0, 0};
        }
        return {table.size(), table[0].size()};
    }
    const vector<Unit>& operator[](size_t i) const {
        return table[i];
    }
    vector<Unit>& operator[](size_t i) {
        return table[i];
    }

private:
    vector<vector<Unit>> table;
};


void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  ASSERT_EQUAL(t[0][0], 0);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
