#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>

#include "TimeSlot.hpp"
#include "Course.hpp"
#include "Instructor.hpp"

class Timetable
{
private:
    std::vector<std::tuple<TimeSlot, Course, Instructor, int>> assignments;
    
    void display_one();

public:
    void pushAssignment(const TimeSlot& timeSlot, const Course& course, const Instructor& instructor, int penalty = -1)
    { assignments.emplace_back(timeSlot, course, instructor, penalty); }
    
    void sort() { std::sort(assignments.begin(), assignments.end()); }
    
    static void displayInfo(std::vector<Timetable>& timetables);
    
    bool operator ==(const Timetable& rhs) const;
    
    [[nodiscard]] std::vector<std::tuple<TimeSlot, Course, Instructor, int>> getAssignments() const
    { return assignments; }
    
    int measurePenalty();
    
};