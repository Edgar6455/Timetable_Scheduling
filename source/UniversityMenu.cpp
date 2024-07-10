#include "UniversityMenu.hpp"

namespace uMenu
{
    void clearScreen()
    {
        #if defined(_WIN32) || defined(_WIN64)
        system("cls");
        #elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
        system("clear");
        #else
        #error "Unknown operating system"
        #endif
    }
    
    void pause()
    {
        #if defined(_WIN32) || defined(_WIN64)
        system("pause");
        #elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
        std::cout << "Press Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        #else
        #error "Unknown operating system"
        #endif
    }
    
    int getRandomNumber(int left, int right)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        
        std::uniform_int_distribution<> dist(left, right);
        
        return dist(gen);
    }
    
    std::vector<std::string>
    fromDirectoryGetFilenamesWithExtension(const std::string& directory, const std::string& extension)
    {
        std::vector<std::string> result;
        
        // Iterate through each entry, check if it is a file and has extension we are looking, accumulate in result
        for (const auto& entry : std::filesystem::directory_iterator(directory))
            if (entry.is_regular_file() && entry.path().extension() == extension)
                result.push_back(entry.path().filename().string());
        
        return result;
    }
    
    void displayOptions(const std::vector<std::string>& fileNames, const std::string& samplesPath)
    {
        std::cout << "Select an option to demonstrate the functionality of the schedulers" << std::endl << std::endl;
        
        int filenameIndex;
        
        // Part of displaying file names as options
        for (filenameIndex = 1; filenameIndex <= fileNames.size(); ++filenameIndex)
        {
            DummyUniversity university;
            university.loadState(samplesPath + fileNames[filenameIndex - 1]);
            std::cout << filenameIndex << ") " << fileNames[filenameIndex - 1] << std::endl;
            std::cout << "Brief: ";
            university.displayBriefInfo();
        }
        
        std::cout << filenameIndex << ") Make your own dataset" << std::endl;
        std::cout << "Brief: run UniversityMenu::makeYourOwn() function and create a new dataset";
        std::cout << std::endl << std::endl;
        
        std::cout << filenameIndex + 1 << ") Random dataset" << std::endl;
        std::cout << "Brief: create a random dataset or update the current one with parameters with size 0 to 10";
        std::cout << std::endl << std::endl;
        
        std::cout << filenameIndex + 2 << ") Exit program" << std::endl << std::endl;
    }
    
    std::string makeYourOwn(const std::string& directory)
    {
        // In this part you can only change {fileName}. Select one with json extension
        std::string fileName = "user_dataset.json";
        
        // Don't change this. This will check if user dataset already exists in the list
        // This will help to avoid loading same dataset again and again
        std::filesystem::path dirPath(directory);
        std::filesystem::path filePath = dirPath / fileName;
        if (std::filesystem::exists(filePath) && std::filesystem::is_regular_file(filePath))
            return "-1";
        
        // You can freely change everything below
        DummyUniversity university;
        
        TimeSlot ts11("Monday", "09:00", "10:35");
        TimeSlot ts12("Monday", "10:45", "12:20");
        TimeSlot ts13("Monday", "12:50", "14:25");
        TimeSlot ts14("Monday", "14:35", "16:10");
        
        TimeSlot ts21("Tuesday", "09:00", "10:35");
        TimeSlot ts22("Tuesday", "10:45", "12:20");
        TimeSlot ts23("Tuesday", "12:50", "14:25");
        TimeSlot ts24("Tuesday", "14:35", "16:10");
        
        Course course1("Course 1", {ts11, ts12});
        Course course2("Course 2", {ts13});
        Course course3("Course 3", {ts11, ts12, ts21, ts22});
        Course course4("Course 4", {ts23, ts24});
        
        Instructor instructor1("Instructor 1", {ts11, ts12}, {course1});
        Instructor instructor2("Instructor 2", {ts13, ts14, ts23, ts24}, {course2});
        Instructor instructor3("Instructor 3", {ts21, ts22}, {course3});
        Instructor instructor4("Instructor 4", {ts11}, {course4});
        
        university.addTimeSlot({ts11, ts12, ts13, ts14, ts21, ts22, ts23, ts24});
        university.addCourse({course1, course2, course3, course4});
        university.addInstructor({instructor1, instructor2, instructor3, instructor4});
        
        university.saveState(directory + fileName);
        
        return fileName;
    }
    
    void createRandomDataset(const std::string& samplesPath)
    {
        std::string fileName = "random_dataset.json";
        DummyUniversity university;
        
        // List of available timeslots with size 10
        std::vector<TimeSlot> timeSlots = {TimeSlot("Monday", "09:00", "10:35"), TimeSlot("Monday", "10:45", "12:20"),
                                           TimeSlot("Monday", "12:50", "14:25"), TimeSlot("Monday", "14:35", "16:10"),
                                           TimeSlot("Tuesday", "09:00", "10:35"), TimeSlot("Tuesday", "10:45", "12:20"),
                                           TimeSlot("Tuesday", "12:50", "14:25"), TimeSlot("Tuesday", "14:35", "16:10"),
                                           TimeSlot("Wednesday", "09:00", "10:35"),
                                           TimeSlot("Wednesday", "10:45", "12:20")};
        
        int timeSlotsCount = getRandomNumber(0, 10);
        
        // Add timeslots from 0 to {timeSlotsCount}
        for (int i = 0; i < timeSlotsCount; ++i)
            university.addTimeSlot({timeSlots[i]});
        
        int coursesCount = getRandomNumber(0, 10);
        std::vector<Course> courses;
        
        for (int i = 0; i < coursesCount; ++i)
        {
            std::vector<TimeSlot> preferredTimeSlots{};
            
            // 33% chance that a time slot will be preferred by {Course {i + 1}}
            for (int j = 0; j < timeSlotsCount; ++j)
                if (getRandomNumber(0, 2) == 2)
                    preferredTimeSlots.push_back(timeSlots[j]);
            
            Course course("Course " + std::to_string(i + 1), preferredTimeSlots);
            courses.push_back(course);
            university.addCourse({course});
        }
        
        int instructorsCount = getRandomNumber(0, 10);
        
        for (int i = 0; i < instructorsCount; ++i)
        {
            std::vector<TimeSlot> availableTimeSlots{};
            std::vector<Course> preferredCourses{};
            
            // 33% chance that a time slot will be preferred by {Instructor {i + 1}}
            for (int j = 0; j < timeSlotsCount; ++j)
                if (getRandomNumber(0, 2) == 2)
                    availableTimeSlots.push_back(timeSlots[j]);
            
            // 33% chance that a course will be preferred by {Instructor {i + 1}}
            for (int j = 0; j < coursesCount; ++j)
                if (getRandomNumber(0, 2) == 2)
                    preferredCourses.push_back(courses[j]);
            
            Instructor instructor("Instructor " + std::to_string(i + 1), availableTimeSlots, preferredCourses);
            university.addInstructor({instructor});
        }
        
        // Save dataset in path {samplesPath} with name {fileName}
        university.saveState(samplesPath + fileName);
    }
    
    std::string selectOption(const std::vector<std::string>& fileNames, const std::string& samplesPath)
    {
        int filesCount = static_cast<int>(fileNames.size());
        
        std::cout << std::endl << "Your option: ";
        
        // Get user input and check for its validity
        std::string userInput;
        std::getline(std::cin, userInput);
        int option;
        
        std::stringstream ss(userInput);
        if (!(ss >> option && ss.eof()))
            throw std::invalid_argument("Not a valid input option.");
        
        if (option < 1 || option > filesCount + 3)
            throw std::invalid_argument("Not a valid input option.");
        
        // Display selected option and clear the screen
        std::cout << std::endl << std::endl << "Selected option " << option << std::endl << std::endl;
        pause();
        clearScreen();
        
        if (option == filesCount + 1)  // Option "Make your own dataset"
        {
            std::cout << "Creating new dataset..." << std::endl << std::endl;
            std::string fileName = makeYourOwn(samplesPath);
            
            if (fileName == "-1")
                std::cout << "File with the given name already exists in the given directory";
            else
                std::cout << "Dataset " << fileName << " has been created.";
            
            std::cout << std::endl << std::endl;
        }
        else if (option == filesCount + 2)  // Option "Create/update the random dataset"
        {
            std::cout << "Creating random dataset..." << std::endl << std::endl;
            createRandomDataset(samplesPath);
            std::cout << "Dataset created / updated." << std::endl << std::endl;
        }
        else if (option == filesCount + 3)  // Option "Exit the program"
        {
            std::cout << "Exiting program..." << std::endl << std::endl;
            pause();
            exit(0);
        }
        else  // If selected one of file names
            return fileNames[option - 1];
        
        return "-1";  // If no dataset has been selected
    }
    
    void askForContents(const std::string& fileName, const std::string& samplesPath)
    {
        std::cout << "Do you want to see contents of the file " << fileName << " ?" << std::endl << std::endl;
        
        // Get user option as a 'y'/'Y' or 'n'/'N'
        std::cout << "y/n : ";
        std::string userInput;
        std::getline(std::cin, userInput);
        std::cout << std::endl << std::endl;
        
        // If user selected yes, load contents from the file and display information
        if (userInput[0] == 'y' || userInput[0] == 'Y')
        {
            DummyUniversity university;
            university.loadState(samplesPath + fileName);
            university.displayInfo();
        }
            // In case user selected something else then no
        else if (userInput[0] != 'n' && userInput[0] != 'N')
            std::cout << "I will count that as a no";
        
        std::cout << std::endl << std::endl;
        pause();
    }
    
    int selectScheduler(const std::vector<std::string>& schedulers)
    {
        std::cout << "Select scheduler: " << std::endl << std::endl;
        
        // Display scheduler options
        for (int i = 1; i <= schedulers.size(); ++i)
            std::cout << i << ") " << schedulers[i - 1] << " Scheduler" << std::endl;
        
        std::cout << std::endl << "Your option: ";
        
        // Get user option
        std::string userInput;
        std::getline(std::cin, userInput);
        int option;
        
        std::stringstream ss(userInput);
        if (!(ss >> option && ss.eof()))
            throw std::invalid_argument("Not a valid input option.");
        
        if (option < 1 || option > schedulers.size())
            throw std::invalid_argument("Not a valid input option.");
        
        // Display selected option
        std::cout << std::endl << "Selected: " << schedulers[option - 1] << " Scheduler" << std::endl << std::endl;
        pause();
        
        return option - 1;
    }
    
    void scheduleAndDisplay(const std::vector<std::unique_ptr<University>>& universities, int scheduler,
                            const std::string& fileName, const std::string& samplesPath)
    {
        std::cout << "Scheduling selected timetable (this may take a while)..." << std::endl << std::endl;
        // Load data of the selected file {fileName} from the {samplesPath} into the selected scheduler data structure
        universities[scheduler]->loadState(samplesPath + fileName);
        auto timetables = universities[scheduler]->schedule();  // Call the scheduler
        Timetable::displayInfo(timetables);  // Display timetable(s) as the scheduler result
    }
}
