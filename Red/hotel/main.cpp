#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <cstdint>

using namespace std;

struct BookUnit {
    string hotel_name;
    int64_t client_id;
    int64_t room_count;
    int64_t time;
};

class HotelSystem {
public:
    void Book(int64_t time, const string& hotel_name, int64_t client_id, int64_t room_count) {
        ++unique_clients[hotel_name][client_id];
        lastTime = time;
        rooms_reserved[hotel_name] += room_count;
        allBooks.push({hotel_name, client_id, room_count, time});
    }

    int64_t Clients(const string& hotel_name) {
        RefreshData();
        return unique_clients[hotel_name].size();
    }

    int64_t Rooms(const string& hotel_name) {
        RefreshData();
        return rooms_reserved[hotel_name];
    }

private:
    static const int SECONDS_IN_DAY = 86400;

    void RefreshData() {
        while(!allBooks.empty() && allBooks.front().time <= (lastTime - SECONDS_IN_DAY)) {
            auto& hotel_name = allBooks.front().hotel_name;
            auto& client_id = allBooks.front().client_id;
            auto& room_count = allBooks.front().room_count;

            --unique_clients[hotel_name][client_id];
            if(unique_clients[hotel_name][client_id] == 0) {
                unique_clients[hotel_name].erase(client_id);
            }
            rooms_reserved[hotel_name] -= room_count;
            allBooks.pop();
        }
    }

    int64_t lastTime = 0;
    queue<BookUnit> allBooks;
    map<string, map<int64_t, int64_t>> unique_clients; // map<hotel_name, map<client_id, client_books>>
    map<string, int64_t> rooms_reserved; // map<hotel_name, rooms_reserved>
};

int main()
{
    HotelSystem hs;

    int64_t client_id;
    int64_t room_count;
    string hotel_name;
    int64_t time;
    string cmd;

    int q = 0;
    cin >> q;
    while(q-- > 0) {
        cin >> cmd;
        if(cmd == "BOOK") {
            cin >> time >> hotel_name >> client_id >> room_count;
            hs.Book(time, hotel_name, client_id, room_count);
        } else if(cmd == "CLIENTS") {
            cin >> hotel_name;
            cout << hs.Clients(hotel_name) << endl;
        } else if(cmd == "ROOMS") {
            cin >> hotel_name;
            cout << hs.Rooms(hotel_name) << endl;
        }
    }

    return 0;
}
