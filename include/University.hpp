#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <nlohmann/json.hpp>

#include "Course.hpp"
#include "Instructor.hpp"
#include "TimeSlot.hpp"
#include "TimeTable.hpp"
#include "Timer.hpp"


class University
{
protected:
    std::vector<Course> courses;
    std::vector<Instructor> instructors;
    std::vector<TimeSlot> timeSlots;

public:
    void addCourse(const std::vector<Course>& _courses)
    { courses.insert(courses.begin(), _courses.begin(), _courses.end()); }
    
    void addInstructor(const std::vector<Instructor>& _instructors)
    { instructors.insert(instructors.begin(), _instructors.begin(), _instructors.end()); }
    
    void addTimeSlot(const std::vector<TimeSlot>& _timeSlots)
    { timeSlots.insert(timeSlots.begin(), _timeSlots.begin(), _timeSlots.end()); }
    
    bool operator ==(const University& other) const
    { return courses == other.courses && instructors == other.instructors && timeSlots == other.timeSlots; }
    
    void saveState(const std::string& filename) const;
    
    void loadState(const std::string& filename);
    
    void displayBriefInfo(bool _timeSlots = true, bool _courses = true, bool _instructors = true);
    
    void displayInfo(bool _courses = true, bool _instructors = true, bool _timeSlots = true, int indentation = 4);
    
    virtual std::vector<Timetable> schedule(bool toggleMessage = true) = 0;
    
    virtual ~University() = default;
};
