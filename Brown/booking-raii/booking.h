#pragma once

#include <iostream>
#include <memory>

namespace RAII {

    template<typename T>
    class Booking {
    public:
        Booking(T *new_provider, int new_counter)
                : provider(std::make_unique<T>(std::move(*new_provider))), counter(new_counter) {}

        Booking(const Booking &) = delete;

        Booking(Booking &&other) = default;

        Booking &operator=(const Booking &) = delete;

        Booking &operator=(Booking &&other) = default;

        ~Booking() {
//            std::cout << "I died" << std::endl;
            if (provider) {
//                std::cout << "I died safety" << std::endl;
                provider->CancelOrComplete(*this);
            }
        }

    private:
        std::unique_ptr<T> provider;
        int counter = 0;
    };

}