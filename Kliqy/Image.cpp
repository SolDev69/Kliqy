#include "Image.h"

// Function to read IMAGE_FILE_NAME from config file
const std::string readImageFileNameFromConfig(const std::string& configFileName) {
    std::ifstream configFile(configFileName);
    std::string imageName;

    if (configFile.is_open()) {
        std::getline(configFile, imageName);
        configFile.close();
    }
    else {
        // Default image name if config file is not found or cannot be opened
        imageName = "ERROR: CONFIG FILE NOT FOUND";
    }

    return imageName;
}