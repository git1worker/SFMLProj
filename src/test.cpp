#include <memory>
#include <iostream>
#include <vector>

class Base{
public:
    virtual void foo() = 0;
};

class MyClass : public Base{
public:
    static int num;

    void foo(){
        std::cout << num++ << std::endl; 
    };

};

int MyClass::num {};

int main(){

    std::vector<std::shared_ptr<Base>> v;
    for (int i = 0; i < 5; ++i){
        v.emplace_back(std::make_shared<MyClass>());
    }

    for (auto& i : v){
        i->foo();
    }

    unsigned int c = 10;
    float a = 1.11;
    std::cout << a + c << std::endl;

    return 0;
}