#include "../include/BruteForceUniversity.hpp"


void BruteForceUniversity::generateTimeSlotPermutations(std::vector<std::vector<TimeSlot>>& result,
                                                        std::vector<TimeSlot>& current, int index,
                                                        std::vector<TimeSlot>& nonEmptyTimeSlots, int pickOptionCount,
                                                        int nonPickOptionCount)
{
    if (pickOptionCount == 0) // Base case
    {
        result.push_back(current);
        return;
    }
    
    if (pickOptionCount > 0)
    {
        current.push_back(nonEmptyTimeSlots[index]);
        generateTimeSlotPermutations(result, current, index + 1, nonEmptyTimeSlots, pickOptionCount - 1,
                                     nonPickOptionCount);
        current.pop_back(); // Backtrack
    }
    if (nonPickOptionCount > 0)
    {
        generateTimeSlotPermutations(result, current, index + 1, nonEmptyTimeSlots, pickOptionCount,
                                     nonPickOptionCount - 1);
    }
}

void BruteForceUniversity::generateInstructorPermutations(std::vector<std::vector<Instructor>>& result,
                                                          const std::vector<TimeSlot>& _timeSlots,
                                                          std::unordered_map<std::string, int>& nonEmptyTimeSlotMatching,
                                                          int index, std::vector<Instructor>& currentPermutation,
                                                          std::vector<std::vector<int>>& adjList)
{
    if (index == _timeSlots.size()) // Base case
    {
        result.push_back(currentPermutation);
        return;
    }
    
    int timeSlotIndex = nonEmptyTimeSlotMatching[_timeSlots[index].getFull()];
    const std::vector<int>& availableInstructorIndexes = adjList[timeSlotIndex];
    
    // Generate permutation for each instructor available in that timeslot
    for (int availableInstructorIndex : availableInstructorIndexes)
    {
        currentPermutation.push_back(instructors[availableInstructorIndex]);
        generateInstructorPermutations(result, _timeSlots, nonEmptyTimeSlotMatching, index + 1, currentPermutation,
                                       adjList);
        currentPermutation.pop_back(); // Backtrack
    }
}

void BruteForceUniversity::generateCoursePermutations(std::vector<std::vector<Course>>& result,
                                                      std::vector<Course>& currentPermutation, int index, int stopIndex)
{
    if (index == stopIndex)
    {
        result.emplace_back(currentPermutation.begin(), currentPermutation.begin() + stopIndex);
        return;
    }
    
    // Recursive case: swap each element with the current index and recurse
    for (int i = index; i < courses.size(); ++i)
    {
        std::swap(currentPermutation[index], currentPermutation[i]);
        generateCoursePermutations(result, currentPermutation, index + 1, stopIndex);
        std::swap(currentPermutation[index], currentPermutation[i]);  // Backtrack
    }
}

std::vector<TimeSlot> BruteForceUniversity::getNonEmptyTimeslots()
{
    std::vector<TimeSlot> nonEmptyTimeSlots;
    // Iterate through each timeslot
    for (const auto& timeSlot : timeSlots)
    {
        bool hasAvailableInstructor = false;
        // Iterate through each instructor with their availability
        for (const auto& instructor : instructors)
        {
            for (const auto& available : instructor.getAvailability())
            {
                // If there is an at least one instructor who is available in that timeslot, pick it and move forward
                if (available.getFull() == timeSlot.getFull())
                {
                    hasAvailableInstructor = true;
                    break;
                }
            }
            if (hasAvailableInstructor)
            {
                nonEmptyTimeSlots.push_back(timeSlot);
                break;
            }
        }
    }
    
    return nonEmptyTimeSlots;
}

std::vector<Timetable> BruteForceUniversity::schedule(bool toggleMessage)
{
    // Start measuring time
    Timer timer;
    timer.start();
    
    // Get a vector of non-empty timeslots
    // Timeslot is considered empty if there is no instructor who is available in that timeslot
    std::vector<TimeSlot> nonEmptyTimeSlots = getNonEmptyTimeslots();
    
    // Map timeslots to numbers from 0 to timeSlots.size()
    std::unordered_map<std::string, int> nonEmptyTimeSlotMatching;
    for (int i = 0; i < nonEmptyTimeSlots.size(); ++i)
        nonEmptyTimeSlotMatching.insert({nonEmptyTimeSlots[i].getFull(), i});
    
    // Construct an adjacency list for every non-empty time slot to their available instructors
    std::vector<std::vector<int>> adjList(nonEmptyTimeSlots.size());
    for (int i = 0; i < instructors.size(); ++i)
        for (const auto& available : instructors[i].getAvailability())
            adjList[nonEmptyTimeSlotMatching[available.getFull()]].push_back(i);
    
    
    std::vector<Timetable> bestTimetables;
    Timetable currentTimetable;
    int minimumPenalty = std::numeric_limits<int>::max();
    int timetableCombinations = 0;
    
    int pickOptionCount = static_cast<int>(std::min(courses.size(), nonEmptyTimeSlots.size()));
    int nonPickOptionCount = ((courses.size() > nonEmptyTimeSlots.size()) ? (0) : static_cast<int>(
            nonEmptyTimeSlots.size() - courses.size()));
    
    // Get all possible combinations for picking {pickOptionCount} timeslots
    std::vector<std::vector<TimeSlot>> timeSlotPermutations;
    std::vector<TimeSlot> currentTimeSlotPermutation;
    generateTimeSlotPermutations(timeSlotPermutations, currentTimeSlotPermutation, 0, nonEmptyTimeSlots,
                                 pickOptionCount, nonPickOptionCount);
    
    // Iterate through every permutation of timeslots
    for (const auto& nextTimeSlots : timeSlotPermutations)
    {
        // Get all possible instructors lists for current timeslot
        std::vector<std::vector<Instructor>> instructorPermutations{};
        std::vector<Instructor> currentInstructorPermutation{};
        generateInstructorPermutations(instructorPermutations, nextTimeSlots, nonEmptyTimeSlotMatching, 0,
                                       currentInstructorPermutation, adjList);
        
        // Iterate through each instructors' set
        for (const auto& nextInstructors : instructorPermutations)
        {
            int stopIndex = std::min(static_cast<int>(courses.size()), static_cast<int>(nonEmptyTimeSlots.size()));
            
            std::vector<std::vector<Course>> coursePermutations{};
            std::vector<Course> currentCoursePermutation = courses;
            generateCoursePermutations(coursePermutations, currentCoursePermutation, 0, stopIndex);
            
            // Iterating through every generated course list
            for (const auto& nextCourses : coursePermutations)
            {
                // Assign i-th course to i-th instructor in i-th timeslot
                for (int i = 0; i < nextCourses.size(); ++i)
                    currentTimetable.pushAssignment(nextTimeSlots[i], nextCourses[i], nextInstructors[i]);
                
                // Measure penalty of that timetable and increment total timetable combinations count
                int currentPenalty = currentTimetable.measurePenalty();
                timetableCombinations += 1;
                
                // Pick the one with less penalty
                if (currentPenalty < minimumPenalty)
                {
                    minimumPenalty = currentPenalty;
                    bestTimetables.clear();
                    bestTimetables.push_back(currentTimetable);
                }
                else if (currentPenalty == minimumPenalty)
                    bestTimetables.push_back(currentTimetable);
                
                // Reset current timetable
                currentTimetable = Timetable();
            }
        }
    }
    
    timer.stop();
    
    if (toggleMessage)
    {
        std::cout << timetableCombinations << " timetable combinations were considered." << std::endl;
        std::cout << "The best timetables were chosen with penalty: " << minimumPenalty << "." << std::endl;
        std::cout << "Found " << bestTimetables.size() << " timetables with that minimum penalty." << std::endl;
        timer.display();
    }
    
    return bestTimetables;
}
