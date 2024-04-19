#pragma once
#include <string>
#include <fstream>

const int IMAGE_WIDTH = 750;

const int IMAGE_HEIGHT = 500;

const std::string readImageFileNameFromConfig(const std::string& configFileName);

const std::string IMAGE_FILE_NAME = readImageFileNameFromConfig("config.txt");