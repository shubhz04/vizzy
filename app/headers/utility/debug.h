#pragma once
#include <iostream>
class Debug {
public:
    template<typename ...Args>
    static void log(Args&&... args) {
        ((std::cout << std::forward<Args>(args) << ' '), ...);
        std::cout << '\n';
    }


};