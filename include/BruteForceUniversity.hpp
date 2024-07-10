#pragma once

#include "University.hpp"

class BruteForceUniversity : public University
{
private:
    void  // Get all possible combinations for non-empty time slots with size {pickOptionCount}
    generateTimeSlotPermutations(std::vector<std::vector<TimeSlot>>& result, std::vector<TimeSlot>& current, int index,
                                 std::vector<TimeSlot>& nonEmptyTimeSlots, int pickOptionCount, int nonPickOptionCount);
    
    // Get all possible instructor combinations for a specific time slot list
    void generateInstructorPermutations(std::vector<std::vector<Instructor>>& result,
                                        const std::vector<TimeSlot>& _timeSlots,
                                        std::unordered_map<std::string, int>& nonEmptyTimeSlotMatching, int index,
                                        std::vector<Instructor>& currentPermutation,
                                        std::vector<std::vector<int>>& adjList);
    
    // Get all possible course combinations with size {stopIndex}
    void generateCoursePermutations(std::vector<std::vector<Course>>& result, std::vector<Course>& currentPermutation,
                                    int index, int stopIndex);
    
    // Get a list of time slots, which have at least one instructor available during it
    std::vector<TimeSlot> getNonEmptyTimeslots();

public:
    std::vector<Timetable> schedule(bool toggleMessage = true) override;
    
    ~BruteForceUniversity() override = default;
};
