#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "Course.hpp"
#include "TimeSlot.hpp"

class Instructor
{
private:
    std::string name;
    std::vector<TimeSlot> availability;
    std::vector<Course> preferredCourses;

public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Instructor, name, availability, preferredCourses)
    
    Instructor() = default;
    
    Instructor(const std::string& _name, const std::vector<TimeSlot>& _availability,
               const std::vector<Course>& _preferredCourses) : name(_name), availability(_availability),
            preferredCourses(_preferredCourses)
    {
        if (_name.size() > 30)
            throw std::invalid_argument("Name of the instructor cannot be longer than 30 symbols.");
    }
    
    bool operator <(const Instructor& other) const { return name < other.name; }
    
    bool operator ==(const Instructor& rhs) const { return this->name == rhs.name; }
    
    [[nodiscard]] std::string getName() const { return name; }
    
    [[nodiscard]] const std::vector<TimeSlot>& getAvailability() const { return availability; }
    
    [[nodiscard]] const std::vector<Course>& getPreferredCourses() const { return preferredCourses; }
    
    void displayInfo(int nestedLevel = 0, int indentation = 4) const
    {
        std::cout << std::string(nestedLevel * indentation, ' ') << "Instructor Name: " << name << std::endl;
        std::cout << std::string((nestedLevel + 1) * indentation, ' ') << "Availability: " << std::endl;
        
        for (const auto& slot : availability)
            slot.displayInfo(nestedLevel + 2, indentation);
        
        std::cout << std::string((nestedLevel + 1) * indentation, ' ') << "Preferred Courses: " << std::endl;
        
        for (const auto& course : preferredCourses)
        {
            std::cout << std::string((nestedLevel + 2) * indentation, ' ');
            std::cout << "Course Name: " << course.getName() << std::endl;
        }
    }
};
