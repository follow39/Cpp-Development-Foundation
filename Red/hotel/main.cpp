#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>

using namespace std;

struct Client {
    long client_id;
    int room_count;
    long long time;
};

class HotelSystem {
public:
    void Book(long client_id, int room_count, const string& hotel_name, long long time) {
        hotels[hotel_name].push({client_id, room_count, time});
        ++unique_clients[hotel_name][client_id];
        lastTime = time;
        rooms_reserved[hotel_name] += room_count;
    }
    long Clients(const string& hotel_name) {
        RefreshAllHotels();
        return unique_clients[hotel_name].size();
    }
    long Rooms(string& hotel_name) {
        auto& clients = hotels[hotel_name];
        RefreshHotel(hotel_name, clients);
        return rooms_reserved[hotel_name];
    }
private:
    static const int SECONDS_IN_DAY = 86400;

    void RefreshAllHotels() {
        for(auto& h : hotels) {
            RefreshHotel(h.first, h.second);
        }
    }

    void RefreshHotel(const string& hotel_name, queue<Client>& clients) {
        if(clients.size() == 0) {
            return;
        }
        while(clients.front().time <= (lastTime - SECONDS_IN_DAY)) {
            --unique_clients[hotel_name][clients.front().client_id];
            if(unique_clients[hotel_name][clients.front().client_id] == 0) {
                unique_clients[hotel_name].erase(clients.front().client_id);
            }
            rooms_reserved[hotel_name] -= clients.front().room_count;
            clients.pop();
        }

    }

    long long lastTime = 0;
    map<string, queue<Client>> hotels;
    map<string, map<long, int>> unique_clients;
    map<string, int> rooms_reserved;
};

int main()
{
    int q = 0;
    cin >> q;

    HotelSystem hs;

    long client_id;
    int room_count;
    string hotel_name;
    long long time;
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
