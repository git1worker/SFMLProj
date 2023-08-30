#include "Debug.hpp"

template<typename T>
void Do(T v){
    std::cout << v << ' ';
}

void Print(){
    std::cout << std::endl;
}

template<typename Head, typename... Tail>
void Print(Head h, Tail... t){
    Do(h);
    Print(t...);
}

// inline void RTDrawing(sf::RenderWindow *window, sf::Drawable& sprite){
//     static int cnt = 0;
//     int a;
//     window->draw(sprite);
//     window->display();
//     std::cout << "Line: " << __LINE__ << " File: " << __FILE__ << "Cnt: " << cnt++ << std::endl;
//     std::cin >> a;
// }