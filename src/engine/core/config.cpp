#include <iostream>
#include <fstream>
#include <string>
#include "config.h"
#include "debug.h"

window_data ReadConfig() {

    window_data config;

    // Open config/config.txt
    std::ifstream configFile(std::string(DATA_DIR) + "config.txt");
    if (!configFile.is_open()) {
        AddLog("Couldn't open the config file");
        throw std::runtime_error("Could not open config file");
    }

    configFile >> config.width;
    configFile >> config.height;
    configFile >> config.title;

    AddLog(
        "window created: w="
        + std::to_string(config.width)
        + ", h=" + std::to_string(config.height)
        + ", title="
        + config.title);
    return config;

}