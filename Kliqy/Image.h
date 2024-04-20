#pragma once
#include <string>
#include <fstream>

const int IMAGE_WIDTH = 750;

const int IMAGE_HEIGHT = 500;


class Game;

const std::string readImageFileNameFromConfig(const std::string& configFileName, Game* game);