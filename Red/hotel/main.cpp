#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <cstdint>

using namespace std;

struct Client {
    int64_t client_id;
    int room_count;
    int64_t time;
};

class HotelSystem {
public:
    void Book(int64_t client_id, int room_count, const string& hotel_name, int64_t time) {
        hotels[hotel_name].push({client_id, room_count, time});
        ++unique_clients[hotel_name][client_id];
        lastTime = time;
        rooms_reserved[hotel_name] += room_count;
        isUpdated = false;
        update_hotels.insert(hotel_name);
    }
    int64_t Clients(const string& hotel_name) {
        if(!isUpdated) {
            RefreshAllHotels();
        }
        return unique_clients[hotel_name].size();
    }
    int64_t Rooms(string& hotel_name) {
        auto& clients = hotels[hotel_name];
        RefreshHotel(hotel_name, clients);
        return rooms_reserved[hotel_name];
    }
private:
    static const int SECONDS_IN_DAY = 86400;

    void RefreshAllHotels() {
        isUpdated = true;
        for(auto& hotel : update_hotels) {
            RefreshHotel(hotel, hotels[hotel]);
        }
        update_hotels.clear();
    }

    void RefreshHotel(const string& hotel_name, queue<Client>& clients) {
        while(!clients.empty() && clients.front().time <= (lastTime - SECONDS_IN_DAY)) {
            auto& uc = unique_clients[hotel_name][clients.front().client_id];
            --uc; // O(1)
            if(uc == 0) {
                unique_clients[hotel_name].erase(clients.front().client_id);
            }
            rooms_reserved[hotel_name] -= clients.front().room_count;
            clients.pop();
        }
    }

    bool isUpdated = false;
    int64_t lastTime = 0;
    map<string, queue<Client>> hotels;
    map<string, map<int64_t, int>> unique_clients;
    map<string, int> rooms_reserved;
    set<string> update_hotels;
};

int main()
{
    int q = 0;
    cin >> q;

    HotelSystem hs;

    int64_t client_id;
    int room_count;
    string hotel_name;
    int64_t time;
    string cmd;
    while(q-- > 0) {
        cin >> cmd;
        if(cmd == "BOOK") {
            cin >> time >> hotel_name >> client_id >> room_count;
            hs.Book(client_id, room_count, hotel_name, time);
        } else if(cmd == "CLIENTS") {
            cin >> hotel_name;
            cout << hs.Clients(hotel_name) << '\n';
        } else if(cmd == "ROOMS") {
            cin >> hotel_name;
            cout << hs.Rooms(hotel_name) << '\n';
        }

    }


    return 0;
}
