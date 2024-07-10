#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "TimeSlot.hpp"

class Course
{
private:
    std::string courseName;
    std::vector<TimeSlot> preferredTimeSlots;

public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Course, courseName, preferredTimeSlots)
    
    Course() = default;
    
    Course(const std::string& _courseName, const std::vector<TimeSlot>& _preferredTimeSlots) : courseName(_courseName),
            preferredTimeSlots(_preferredTimeSlots)
    {
        if (_courseName.size() > 30)
            throw std::invalid_argument("Name of the course cannot be longer than 30 symbols.");
    }
    
    bool operator <(const Course& other) const { return courseName < other.courseName; }
    
    bool operator ==(const Course& rhs) const { return this->courseName == rhs.courseName; }
    
    [[nodiscard]] std::string getName() const { return courseName; }
    
    [[nodiscard]] const std::vector<TimeSlot>& getPreferredTimeSlots() const { return preferredTimeSlots; }
    
    void displayInfo(int nestedLevel = 0, int indentation = 4) const
    {
        std::cout << std::string(nestedLevel * indentation, ' ') << "Course Name: " << courseName << std::endl;
        std::cout << std::string((nestedLevel + 1) * indentation, ' ') << "Preferred Time Slots: " << std::endl;
        
        for (const auto& preferredTimeSlot : preferredTimeSlots)
            preferredTimeSlot.displayInfo(nestedLevel + 2, indentation);
    }
};
