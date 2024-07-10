#include "../include/DummyUniversity.hpp"


std::vector<Timetable> DummyUniversity::schedule(bool toggleMessage)
{
    // Start measuring time
    Timer timer;
    timer.start();
    
    Timetable timetable;
    
    // Map timeslots to numbers from 0 to timeSlots.size()
    std::unordered_map<std::string, int> timeSlotMatching;
    for (int i = 0; i < timeSlots.size(); ++i)
        timeSlotMatching.insert({timeSlots[i].getFull(), i});
    
    // Construct an adjacency list for every time slot to their available instructors
    std::vector<std::vector<int>> adjList(timeSlots.size());
    for (int i = 0; i < instructors.size(); ++i)
        for (const auto& available : instructors[i].getAvailability())
            adjList[timeSlotMatching[available.getFull()]].push_back(i);
    
    // Map courses to numbers from 0 to courses.size()
    std::unordered_map<std::string, int> courseMatching;
    for (int i = 0; i < courses.size(); ++i)
        courseMatching.insert({courses[i].getName(), i});
    
    // Construct a set of course ids that are not picked in timetable yet
    // Initialize it with numbers from 0 to courses.size()
    std::set<int> availableCourseIds;
    for (int i = 0; i < courses.size(); ++i)
        availableCourseIds.insert(i);
    
    // Iterate through time slots
    // Stop when we pick maximum number of courses
    int coursesPicked = 0;
    for (int i = 0; i < adjList.size() && coursesPicked < courses.size(); ++i)
    {
        // Boolean to check if we did found if one of instructors for that time slot
        // prefers a course that is not yet picked
        bool found = false;
        
        // Iterate through every instructor, who is available for that time slot
        for (int j = 0; j < adjList[i].size(); ++j)
        {
            int instructor_id = adjList[i][j];
            
            // Iterate through all preferred courses for that instructor
            // Pick the first preferred course, which is not picked yet
            for (const auto& preferredCourse : instructors[instructor_id].getPreferredCourses())
            {
                int courseId = courseMatching[preferredCourse.getName()];
                
                if (availableCourseIds.find(courseId) != availableCourseIds.end())
                {
                    timetable.pushAssignment(timeSlots[i], courses[courseId], instructors[instructor_id]);
                    availableCourseIds.erase(courseId);
                    found = true;
                    coursesPicked++;
                    break;
                }
            }
            
            if (found)
                break;
        }
        
        // If we didn't find an instructor with available preferred course, pick the first available instructor
        // with the first available course if time slot has at least one instructor
        if (!found && !adjList[i].empty())
        {
            int courseId = *availableCourseIds.begin();
            int instructor_id = adjList[i][0];
            timetable.pushAssignment(timeSlots[i], courses[courseId], instructors[instructor_id]);
            availableCourseIds.erase(courseId);
            coursesPicked++;
        }
    }
    
    timer.stop();
    
    // Measure penalty for that one timetable
    int penalty = timetable.measurePenalty();
    
    if (toggleMessage)
    {
        std::cout << "A timetable was chosen with penalty: " << penalty << std::endl;
        timer.display();
    }
    
    return {timetable};
}
