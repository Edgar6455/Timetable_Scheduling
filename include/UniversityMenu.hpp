#pragma once

#include <iostream>
#include <vector>
#include <filesystem>
#include <random>

#include "BruteForceUniversity.hpp"
#include "DummyUniversity.hpp"
#include "HybridUniversity.hpp"

namespace uMenu
{
    void clearScreen();  // Clear console both for windows and unix-like systems
    
    void pause();  // Multi-platform. Wait for user to react
    
    int getRandomNumber(int left, int right);  // Get random number in range [left, right]
    
    std::vector<std::string>  // Parse the directory contents and make vector of filenames with the given extension
    fromDirectoryGetFilenamesWithExtension(const std::string& directory, const std::string& extension);
    
    // Display available options to console
    void displayOptions(const std::vector<std::string>& fileNames, const std::string& samplesPath);
    
    // You can change the contents of this function to create a dataset you want to test
    std::string makeYourOwn(const std::string& directory);
    
    // Create or update the random dataset. Parameters size is from 0 to 10 inclusive
    void createRandomDataset(const std::string& samplesPath);
    
    // User selects an options. Corresponding events occur based on option
    std::string selectOption(const std::vector<std::string>& fileNames, const std::string& samplesPath);
    
    // Ask user if they want to see the contents of the selected dataset. If yes load and show
    void askForContents(const std::string& fileName, const std::string& samplesPath);
    
    // User selects a scheduler from the provided list of available options
    int selectScheduler(const std::vector<std::string>& schedulers);
    
    // Call corresponding scheduler on the selected dataset, and display its messages
    void scheduleAndDisplay(const std::vector<std::unique_ptr<University>>& universities, int scheduler,
                            const std::string& fileName, const std::string& samplesPath);
}
