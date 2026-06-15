#pragma once
#pragma once
#include <iostream>

// Klasa generyczna
template <typename T>
class Counter {
private:
    T value;

public:
    Counter(T v = 0) : value(v) {}

    // Przeciążenie operatora
    Counter& operator+=(const T& rhs) { value += rhs; return *this; }
    Counter& operator-=(const T& rhs) { value -= rhs; return *this; }
    Counter& operator=(const T& rhs) { value = rhs; return *this; }
    Counter& operator++() { ++value; return *this; }
    Counter operator++(int) { Counter temp = *this; ++value; return temp; }
    // Konwersja na typ bazowy
    operator T() const { return value; }

    // Przeciążenie operatorów strumienia
    friend std::ostream& operator<<(std::ostream& os, const Counter<T>& c) {
        os << c.value;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Counter<T>& c) {
        is >> c.value;
        return is;
    }
};