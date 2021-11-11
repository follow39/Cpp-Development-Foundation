#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <unordered_set>

#include "profile.h"

using namespace std;


class ReadingManager {
public:
    ReadingManager()
            : users(MAX_USER_COUNT_ + 1, 0) {}

    void Read(int user_id, int page_count) {
        if (page_count == 0) {
            return;
        }

        int temp = users[user_id];
        if (temp != 0) {
            --puc_map[temp];
            if (puc_map[temp] == 0) {
                puc_map.erase(temp);
            }
        }
        users[user_id] = page_count;
        ++puc_map[page_count];
        users_set.insert(user_id);
    }

    double Cheer(int user_id) const {
        int currentUserPageCount = users[user_id];
        if (currentUserPageCount == 0 || users_set.empty()) {
            return 0;
        }
        if (users_set.size() == 1) {
            return 1;
        }

        int sum = 0;
        for (const auto &p: puc_map) {
            if (p.first >= currentUserPageCount) {
                break;
            }
            sum += p.second;
        }

        return static_cast<double>(sum) / (users_set.size() - 1);
    }

private:
    static const int MAX_USER_COUNT_ = 100'000;

    vector<int> users;
    map<int, int> puc_map;
    unordered_set<int> users_set;
};

int main() {
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    LOG_DURATION("Total");
    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}