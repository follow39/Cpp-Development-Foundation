#include "Common.h"
#include <mutex>
#include <list>
#include <unordered_map>
#include <memory>

using namespace std;

lock_guard<mutex> Lock(mutex &mtx) {
    return lock_guard<mutex>(mtx);
}

class LruCache : public ICache {
public:
    LruCache(shared_ptr<IBooksUnpacker> new_books_unpacker, const Settings &new_settings)
            : books_unpacker(move(new_books_unpacker)), settings(new_settings) {}

    BookPtr GetBook(const string &book_name) override {
        auto guard = Lock(cache_mtx);
        auto it = books.find(book_name);
        BookPtr result;
        if (it != books.end()) {
            result = move(*(it->second));
            cache.erase(it->second);
            cache.push_front(result);
            it->second = cache.begin();
        } else {
            result = books_unpacker->UnpackBook(book_name);
            cache.push_front(result);
            books[book_name] = cache.begin();
            current_size += result->GetContent().size();
            Shrink();
        }
        return result;
    }

private:
    void Shrink() {
        while (current_size > settings.max_memory) {
            current_size -= cache.back()->GetContent().size();
            books.erase(cache.back()->GetName());
            cache.pop_back();
        }
    }

    shared_ptr<IBooksUnpacker> books_unpacker;
    const Settings settings;
    size_t current_size = 0;
    mutex cache_mtx;
    list<BookPtr> cache;
    unordered_map<string, list<BookPtr>::iterator> books;
};


unique_ptr<ICache> MakeCache(shared_ptr<IBooksUnpacker> books_unpacker,
                             const ICache::Settings &settings) {
    return make_unique<LruCache>(move(books_unpacker), settings);
}
