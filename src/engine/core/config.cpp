#include <iostream>
#include <fstream>
#include <string>
#include "config.h"

window_data ReadConfig() {

    window_data config;

    // Open data/config.txt
    std::ifstream configFile(std::string(DATA_DIR) + "config.txt");
    if (!configFile.is_open()) {
        throw std::runtime_error("Could not open config file");
    }

    configFile >> config.width;
    configFile >> config.height;
    std::getline(configFile, config.title);

    std::cout << "Config loaded: "
        << "Width: " << config.width
        << ", Height: " << config.height
        << ", Title: " << config.title << std::endl;
    return config;

}