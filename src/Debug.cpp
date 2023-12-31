#include "Debug.hpp"

template <typename T> void Do(T v) { std::cout << v << ' '; }

void Print() { std::cout << std::endl; }

template <typename Head, typename... Tail> void Print(Head h, Tail... t) {
    Do(h);
    Print(t...);
}

Timer::Timer() { start = sc::now(); }

std::chrono::microseconds Timer::GetTime() { return std::chrono::duration_cast<std::chrono::microseconds>(sc::now() - start); }

Timer::~Timer() { 
    // std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(sc::now() - start) << ' '; 
}
