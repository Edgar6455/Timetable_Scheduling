#include "../include/UniversityMenu.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>


void processFile(const std::string& filePath) {
    std::ifstream file(filePath.c_str(), std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return;
    }

    std::string samplesPath = std::string(SAMPLES_PATH) + "/";
    std::vector<std::string> schedulers{"Dummy", "Brute Force", "Hybrid"};

    std::vector<std::unique_ptr<University>> universities;
    universities.push_back(std::make_unique<DummyUniversity>());
    universities.push_back(std::make_unique<BruteForceUniversity>());
    universities.push_back(std::make_unique<HybridUniversity>());

    int scheduler = 2;

    try
    {
        uMenu::scheduleAndDisplay(universities, scheduler, filePath, samplesPath);
    }
    catch (const std::invalid_argument& ex)
    {
        std::cerr << "Invalid argument: " << ex.what() << std::endl;
        uMenu::pause();
    }
}


bool isRegularFile(const std::string& path) {
    struct stat path_stat;
    if (stat(path.c_str(), &path_stat) != 0) {
        return false;
    }
    return S_ISREG(path_stat.st_mode);
}


int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <corpus_directory>" << std::endl;
        return 1;
    }

    std::string corpusDir = argv[1];
    DIR* dir = opendir(corpusDir.c_str());
    if (!dir) {
        std::cerr << "Invalid corpus directory: " << corpusDir << std::endl;
        return 1;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_REG || isRegularFile(corpusDir + "/" + entry->d_name)) {
            processFile(corpusDir + "/" + entry->d_name);
        }
    }
    closedir(dir);

    return 0;
}
