#pragma once

#include "DummyUniversity.hpp"
#include "BruteForceUniversity.hpp"
#include "HybridUniversity.hpp"

namespace testContents
{
    // 2 timeslots, 2 courses, 2 instructors
    void schedule1(University* university, Timetable& result, Timetable& answer);
    
    // 1 timeslot, 2 courses, 2 instructors
    void schedule2(University* university, Timetable& result, Timetable& answer);
    
    // 2 timeslots, 1 course, 2 instructors
    void schedule3(University* university, Timetable& result, Timetable& answer);
    
    // 2 timeslots, 2 courses, 1 instructor
    void schedule4(University* university, Timetable& result, Timetable& answer);
    
    // 2 timeslots, 1 course, 1 instructor, 1 penalty
    void schedule5(University* university, Timetable& result, Timetable& answer);
    
    // 2 timeslots, 1 course, 1 instructor, 2 penalty
    void schedule6(University* university, Timetable& result, Timetable& answer);
    
    // 0 timeslots, 1 course, 1 instructor. Empty answer
    void schedule7(University* university, Timetable& result, Timetable& answer);
    
    // 1 timeslots, 0 courses, 1 instructor. Empty answer
    void schedule8(University* university, Timetable& result, Timetable& answer);
    
    // 1 timeslot, 1 course, 0 instructors. Empty answer
    void schedule9(University* university, Timetable& result, Timetable& answer);
    
    
    // Test data saving and loading in json
    void persistence1(University* university, University* other);
    
    void persistence2(University* university, University* other);
    
}
