#include "Image.h"
#include "Constants.h"
#include "Game.h"
#include <windows.h>

// Function to read IMAGE_FILE_NAME from config file
const std::string readImageFileNameFromConfig(const std::string& configFileName, Game* game) {
    std::ifstream configFile(configFileName);
    std::string imageName;
    HWND* hWnd = game->g_hWnd;
    if (configFile.is_open()) {
        std::getline(configFile, imageName);
        configFile.close();
    }
    else {
        // Default image name if config file is not found or cannot be opened
        MessageBoxA(*hWnd, "Unable to load config!", "Error", MB_OK);
    }

    return imageName;
}