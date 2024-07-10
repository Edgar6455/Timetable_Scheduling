#include "../include/HybridUniversity.hpp"

std::vector<Timetable> HybridUniversity::schedule(bool toggleMessage)
{
    // Start the timers
    Timer fullTimer, dummyTimer;
    fullTimer.start();
    dummyTimer.start();
    
    // Prepare and call the Dummy Scheduler
    DummyUniversity dummyUniversity;
    dummyUniversity.addCourse(courses);
    dummyUniversity.addInstructor(instructors);
    dummyUniversity.addTimeSlot(timeSlots);
    auto dummyResults = dummyUniversity.schedule(false);
    
    if (dummyResults[0].getAssignments().empty())
    {
        if (toggleMessage)
            std::cout << "Dummy Scheduler could not found any valid timetable. Stopping." << std::endl;
        
        return dummyResults;
    }
    
    auto dummyResult = dummyResults[0];
    int dummyPenalty = dummyResult.measurePenalty();
    
    dummyTimer.stop();
    
    if (toggleMessage)
    {
        std::cout << "Dummy Scheduler finished its work and found a timetable with penalty: ";
        std::cout << dummyPenalty << "." << std::endl;
        dummyTimer.display();
        
        std::cout << "This is the timetable:" << std::endl;
        Timetable::displayInfo(dummyResults);
    }
    
    // Construct the same Time table data structure, but with starting of the penalty
    // The goal is to sort the assignments by penalty
    std::vector<std::tuple<int, TimeSlot, Course, Instructor>> assignmentsByPenalty;
    
    for (const auto& [timeSlot, course, instructor, penalty] : dummyResult.getAssignments())
        assignmentsByPenalty.emplace_back(penalty, timeSlot, course, instructor);
    
    std::sort(assignmentsByPenalty.begin(), assignmentsByPenalty.end());
    
    
    // Get the {assignmentsByPenalty.size() / 5} - th assignment. {threshold} is its penalty points number
    // This will ensure that we will keep at least 1/5 of assignments, which will improve performance of Brute Force
    auto thresholdAssignment = assignmentsByPenalty[assignmentsByPenalty.size() / 5];
    int threshold = std::get<0>(thresholdAssignment);
    
    // We keep the best assignments here to combine them with the Brute Force Scheduler results
    Timetable base;
    
    // Construct set of courses and timeSlots
    std::set<Course> coursesSet;
    for (const auto& course : courses)
        coursesSet.insert(course);
    
    std::set<TimeSlot> timeSlotsSet;
    for (const auto& timeSlot : timeSlots)
        timeSlotsSet.insert(timeSlot);
    
    // Iterate through each assignment, if its penalty is less or equal to threshold, keep it to the base
    // Also erase course and timeSlot used in that assignment, because these resources are used only once
    for (const auto& [timeSlot, course, instructor, penalty] : dummyResult.getAssignments())
    {
        if (penalty <= threshold)
        {
            base.pushAssignment(timeSlot, course, instructor, penalty);
            coursesSet.erase(course);
            timeSlotsSet.erase(timeSlot);
        }
    }
    
    if (toggleMessage)
        std::cout << "It was decided to keep assignments with penalty " << threshold << " or less." << std::endl;
    
    // Case, where we keep everything from the Dummy Scheduler's result. This means nothing to improve
    if (base.getAssignments().size() == dummyResult.getAssignments().size())
    {
        if (toggleMessage)
        {
            fullTimer.stop();
            std::cout << "There is nothing to improve here. Stopping algorithm." << std::endl;
            fullTimer.display();
        }
        
        return {dummyResult};
    }
    
    if (toggleMessage)
    {
        std::cout << "Trying to improve the given timetable with the Brute Force Scheduler ";
        std::cout << "(this may take a while)..." << std::endl << std::endl;
    }
    
    // Prepare the Brute Force Scheduler, start the timer
    Timer bruteForceTimer;
    bruteForceTimer.start();
    
    // Get all elements of courses and time slots sets to the vectors
    std::vector<Course> newCourses;
    newCourses.reserve(coursesSet.size());
    for (const auto& course : coursesSet)
        newCourses.push_back(course);
    
    std::vector<TimeSlot> newTimeslots;
    newTimeslots.reserve(timeSlotsSet.size());
    for (const auto& timeSlot : timeSlotsSet)
        newTimeslots.push_back(timeSlot);
    
    // Feed all the data to the Brute Force Scheduler and start it
    BruteForceUniversity bruteForceUniversity;
    bruteForceUniversity.addTimeSlot(newTimeslots);
    bruteForceUniversity.addInstructor(instructors);
    bruteForceUniversity.addCourse(newCourses);
    
    std::vector<Timetable> result = bruteForceUniversity.schedule(false);
    
    // Add contents of the {base} timetable to each result
    for (auto& timetable : result)
        for (const auto& [timeSlot, course, instructor, penalty] : base.getAssignments())
            timetable.pushAssignment(timeSlot, course, instructor, penalty);
    
    // Stop both timers, display messages and return the final result
    bruteForceTimer.stop();
    fullTimer.stop();
    
    if (toggleMessage)
    {
        int finalPenalty = result[0].measurePenalty();
        std::cout << "The Brute Force Scheduler has chosen timetables with penalty: " << finalPenalty;
        std::cout << "." << std::endl;
        
        std::cout << "Found " << result.size() << " timetables with that minimum penalty." << std::endl;
        bruteForceTimer.display();
        std::cout << "Full ";
        fullTimer.display();
    }
    
    return result;
}