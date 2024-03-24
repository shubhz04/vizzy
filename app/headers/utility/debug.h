#pragma once
#include <iostream>
class Debug {
public:
    template<typename ...Args>
    static void log(Args&&... args) {
        ((std::cout << std::forward<Args>(args) << ' '), ...);
        std::cout << '\n';
    }
    static void log_texture_metadata(const char* _filename, int _width, int _height, bool _hasAlpha, int _refID) {
        std::cout << "Loaded Texture : "
            << "\n |- filename :" << _filename
            << "\n |- width : " << _width
            << "\n |- height : " << _height
            << "\n |- hasAlpha : " << _hasAlpha
            << "\n |- refID : " << _refID
            << std::endl;
    }


};