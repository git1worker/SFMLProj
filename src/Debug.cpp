#include "Debug.hpp"

template <typename T> void Do(T v) { std::cout << v << ' '; }

void Print() { std::cout << std::endl; }

template <typename Head, typename... Tail> void Print(Head h, Tail... t) {
    Do(h);
    Print(t...);
}
