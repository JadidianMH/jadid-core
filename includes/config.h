#pragma once
#include <string>

struct window_data
{
    int width;
    int height;
    std::string title;
};


window_data ReadConfig();