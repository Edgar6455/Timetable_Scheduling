#include "../include/University.hpp"


void University::saveState(const std::string& filename) const
{
    nlohmann::json j;
    j["courses"] = courses;
    j["instructors"] = instructors;
    j["timeSlots"] = timeSlots;
    
    std::ofstream file(filename);
    if (!file)
        throw std::runtime_error("Unable to open file for writing: " + filename);
    
    file << j.dump(4);
    file.close();
}

void University::loadState(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file)
        throw std::runtime_error("Unable to open file for reading: " + filename);
    
    nlohmann::json j;
    file >> j;
    file.close();
    
    courses = j.at("courses").get<std::vector<Course>>();
    instructors = j.at("instructors").get<std::vector<Instructor>>();
    timeSlots = j.at("timeSlots").get<std::vector<TimeSlot>>();
}

void University::displayBriefInfo(bool _timeSlots, bool _courses, bool _instructors)
{
    if (!_courses && !_instructors && !_timeSlots)
        throw std::invalid_argument("Choose at least one thing to display.");
    
    if (_timeSlots)
        std::cout << timeSlots.size() << " time slots";
    
    if (_courses)
    {
        if (_timeSlots)
            std::cout << ", ";
        std::cout << courses.size() << " courses";
    }
    
    if (_instructors)
    {
        if (_timeSlots || _courses)
            std::cout << ", ";
        
        std::cout << instructors.size() << " instructors";
    }
    
    std::cout << std::endl << std::endl;
}

void University::displayInfo(bool _timeSlots, bool _courses, bool _instructors, int indentation)
{
    if (indentation < 0 || indentation > 10)
        throw std::invalid_argument("Indentation must be in range [1, 9].");
    
    if (!_courses && !_instructors && !_timeSlots)
        throw std::invalid_argument("Choose at least one thing to display.");
    
    std::cout << "University Data:" << std::endl;
    
    if (_timeSlots)
    {
        std::cout << std::endl << std::string(indentation, ' ') << "Time slots: " << std::endl;
        for (const auto& timeSlot : timeSlots)
            timeSlot.displayInfo(2, indentation);
    }
    
    if (_courses)
    {
        std::cout << std::endl << std::string(indentation, ' ') << "Courses: " << std::endl;
        for (const auto& course : courses)
            course.displayInfo(2, indentation);
    }
    
    if (_instructors)
    {
        std::cout << std::endl << std::string(indentation, ' ') << "Instructors: " << std::endl;
        for (const auto& instructor : instructors)
            instructor.displayInfo(2, indentation);
    }
}