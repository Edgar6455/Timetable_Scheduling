#include "../include/UniversityMenu.hpp"


int main()
{
    std::string samplesPath = std::string(SAMPLES_PATH) + "/";
    std::vector<std::string> schedulers{"Dummy", "Brute Force", "Hybrid"};
    
    std::vector<std::unique_ptr<University>> universities;
    universities.push_back(std::make_unique<DummyUniversity>());
    universities.push_back(std::make_unique<BruteForceUniversity>());
    universities.push_back(std::make_unique<HybridUniversity>());
    
    while (true)
    {
        try
        {
            std::vector<std::string> fileNames = uMenu::fromDirectoryGetFilenamesWithExtension(samplesPath, ".json");
            
            uMenu::clearScreen();
            
            uMenu::displayOptions(fileNames, samplesPath);
            std::string selectedFile = uMenu::selectOption(fileNames, samplesPath);
            
            if (selectedFile != "-1")
            {
                uMenu::askForContents(selectedFile, samplesPath);
                uMenu::clearScreen();
                
                int scheduler = uMenu::selectScheduler(schedulers);
                uMenu::clearScreen();
                
                uMenu::scheduleAndDisplay(universities, scheduler, selectedFile, samplesPath);
            }
            
            uMenu::pause();
        }
        catch (const std::invalid_argument& ex)
        {
            std::cerr << "Invalid argument: " << ex.what() << std::endl;
            uMenu::pause();
        }
    }
}
