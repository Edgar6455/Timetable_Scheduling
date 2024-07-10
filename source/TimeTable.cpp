#include "../include/TimeTable.hpp"


void Timetable::display_one()
{
    // Sort the timetable. Sort mainly by time slots
    this->sort();
    
    // If timetable is not empty, and it is not measured for penalty, measure then start to display
    if (!assignments.empty() && std::get<3>(assignments[0]) < 0)
        measurePenalty();
    
    // Iterate through every assignment, get values and print
    for (const auto& assignment : assignments)
    {
        std::string _timeSlot = std::get<0>(assignment).getFull();
        std::string _courseName = std::get<1>(assignment).getName();
        std::string _instructorName = std::get<2>(assignment).getName();
        int penalty = std::get<3>(assignment);
        
        // I know, there are magic numbers here, sorry for this. I didn't parametrize this
        std::cout << "|  " << _timeSlot << std::string(26 - _timeSlot.size(), ' ') << "|  ";
        std::cout << _courseName << std::string(33 - _courseName.size(), ' ') << "|  ";
        std::cout << _instructorName << std::string(33 - _instructorName.size(), ' ') << "|     ";
        
        if (penalty > 0)
            std::cout << penalty << "     |";
        else
            std::cout << "      |";
        
        std::cout << std::endl;
    }
}

void Timetable::displayInfo(std::vector<Timetable>& timetables)
{
    for (auto& timetable : timetables)
    {
        std::cout << "__________________________________________________________________________________________________________________\n";
        std::cout << "|         Time Slot          |            Course Name            |             Instructor            |  Penalty  |\n";
        std::cout << "|----------------------------|-----------------------------------|-----------------------------------|-----------|\n";
        
        timetable.display_one();
        
        std::cout << "|____________________________|___________________________________|___________________________________|___________|\n";
        std::cout << std::endl << std::endl;
    }
}

bool Timetable::operator ==(const Timetable& rhs) const
{
    if (assignments.size() != rhs.assignments.size())
        return false;
    
    for (int i = 0; i < assignments.size(); ++i)
    {
        if (!(std::get<0>(assignments[i]) == std::get<0>(rhs.assignments[i]) &&
              std::get<1>(assignments[i]) == std::get<1>(rhs.assignments[i]) &&
              std::get<2>(assignments[i]) == std::get<2>(rhs.assignments[i]) &&
              std::get<3>(assignments[i]) == std::get<3>(rhs.assignments[i])))
        {
            return false;
        }
    }
    
    return true;
}

int Timetable::measurePenalty()
{
    int totalPenalty = 0;
    
    // Iterate through all assignments and calculate penalty of each. Accumulate all penalties
    for (auto& assignment : assignments)
    {
        // Get data from each assignment
        TimeSlot timeSlot = std::get<0>(assignment);
        Course course = std::get<1>(assignment);
        Instructor instructor = std::get<2>(assignment);
        
        bool found = false;
        int penaltyForThisAssignment = 0;
        
        // Iterate through all preferred time slots of the course, check if selected time slot matches it
        for (const auto& preferredTimeSlot : course.getPreferredTimeSlots())
        {
            if (timeSlot.getFull() == preferredTimeSlot.getFull())
            {
                found = true;
                break;
            }
        }
        if (!found)
            penaltyForThisAssignment += 1;  // Penalty for having a course not in it's preferred time slot
        
        found = false;
        // Iterate through all preferred courses of the instructor, check if selected one matches it
        for (const auto& preferredCourse : instructor.getPreferredCourses())
        {
            if (preferredCourse.getName() == course.getName())
            {
                found = true;
                break;
            }
        }
        if (!found)
            penaltyForThisAssignment += 2;  // Penalty for having an instructor to teach not a preferred course
        
        // Change the current assignment with the measured penalty
        assignment = {timeSlot, course, instructor, penaltyForThisAssignment};
        totalPenalty += penaltyForThisAssignment;
    }
    
    return totalPenalty;
}
