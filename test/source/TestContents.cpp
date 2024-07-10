#include "../TestContents.hpp"

void testContents::schedule1(University* university, Timetable& result, Timetable& answer)
{
    TimeSlot ts11("Monday", "09:00", "10:35");
    TimeSlot ts12("Monday", "10:45", "12:20");
    
    Course course1("Mathematical statistics", {ts12});
    Course course2("Calculus", {ts11});
    
    Instructor instructor1("Dr. Smith", {ts11}, {course2});
    Instructor instructor2("Dr. Johnson", {ts12}, {course1});
    
    university->addTimeSlot({ts11, ts12});
    university->addCourse({course1, course2});
    university->addInstructor({instructor1, instructor2});
    
    result = (university->schedule(false))[0];
    
    // Same answer in both cases
    if (dynamic_cast<DummyUniversity*>(university) || dynamic_cast<BruteForceUniversity*>(university) ||
        dynamic_cast<HybridUniversity*>(university))
    {
        answer.pushAssignment(ts11, course2, instructor1, 0);
        answer.pushAssignment(ts12, course1, instructor2, 0);
    }
    
    result.sort();
    answer.sort();
}

void testContents::schedule2(University* university, Timetable& result, Timetable& answer)
{
    TimeSlot ts11("Monday", "09:00", "10:35");
    
    Course course1("Mathematical statistics", {});
    Course course2("Calculus", {ts11});
    
    Instructor instructor1("Dr. Smith", {ts11}, {course2});
    Instructor instructor2("Dr. Johnson", {}, {course1});
    
    university->addTimeSlot({ts11});
    university->addCourse({course1, course2});
    university->addInstructor({instructor1, instructor2});
    
    result = (university->schedule(false))[0];
    
    // Same answer in both cases
    if (dynamic_cast<DummyUniversity*>(university) || dynamic_cast<BruteForceUniversity*>(university) ||
        dynamic_cast<HybridUniversity*>(university))
        answer.pushAssignment(ts11, course2, instructor1, 0);
}

void testContents::schedule3(University* university, Timetable& result, Timetable& answer)
{
    TimeSlot ts11("Monday", "09:00", "10:35");
    TimeSlot ts12("Monday", "10:45", "12:20");
    
    Course course1("Mathematical statistics", {ts12});
    
    Instructor instructor1("Dr. Smith", {ts11}, {});
    Instructor instructor2("Dr. Johnson", {ts12}, {course1});
    
    university->addTimeSlot({ts11, ts12});
    university->addCourse({course1});
    university->addInstructor({instructor1, instructor2});
    
    result = (university->schedule(false))[0];
    
    // Different answers
    if (dynamic_cast<DummyUniversity*>(university) || dynamic_cast<HybridUniversity*>(university))
        answer.pushAssignment(ts11, course1, instructor1, 3);
    else if (dynamic_cast<BruteForceUniversity*>(university))
        answer.pushAssignment(ts12, course1, instructor2, 0);
}

void testContents::schedule4(University* university, Timetable& result, Timetable& answer)
{
    TimeSlot ts11("Monday", "09:00", "10:35");
    TimeSlot ts12("Monday", "10:45", "12:20");
    
    Course course1("Mathematical statistics", {ts12});
    Course course2("Calculus", {ts11});
    
    Instructor instructor1("Dr. Smith", {ts11, ts12}, {course2});
    
    university->addTimeSlot({ts11, ts12});
    university->addCourse({course1, course2});
    university->addInstructor({instructor1});
    
    result = (university->schedule(false))[0];
    
    // Same answer in both cases
    if (dynamic_cast<DummyUniversity*>(university) || dynamic_cast<BruteForceUniversity*>(university) ||
        dynamic_cast<HybridUniversity*>(university))
    {
        answer.pushAssignment(ts11, course2, instructor1, 0);
        answer.pushAssignment(ts12, course1, instructor1, 2);
    }
    
    result.sort();
    answer.sort();
}

void testContents::schedule5(University* university, Timetable& result, Timetable& answer)
{
    TimeSlot ts11("Monday", "09:00", "10:35");
    TimeSlot ts12("Monday", "10:45", "12:20");
    
    Course course1("Mathematical statistics", {ts12});
    
    Instructor instructor1("Dr. Smith", {ts11}, {course1});
    
    university->addTimeSlot({ts11, ts12});
    university->addCourse({course1});
    university->addInstructor({instructor1});
    
    result = (university->schedule(false))[0];
    
    // Same answer in all cases
    answer.pushAssignment(ts11, course1, instructor1, 1);
}

void testContents::schedule6(University* university, Timetable& result, Timetable& answer)
{
    TimeSlot ts11("Monday", "09:00", "10:35");
    TimeSlot ts12("Monday", "10:45", "12:20");
    
    Course course1("Mathematical statistics", {ts12});
    
    Instructor instructor1("Dr. Smith", {ts12}, {});
    
    university->addTimeSlot({ts11, ts12});
    university->addCourse({course1});
    university->addInstructor({instructor1});
    
    result = (university->schedule(false))[0];
    
    // Same answer in all cases
    answer.pushAssignment(ts12, course1, instructor1, 2);
}

void testContents::schedule7(University* university, Timetable& result, Timetable& answer)
{
    Course course1("Mathematical statistics", {});
    
    Instructor instructor1("Dr. Smith", {}, {});
    
    university->addCourse({course1});
    university->addInstructor({instructor1});
    
    result = (university->schedule(false))[0];
}

void testContents::schedule8(University* university, Timetable& result, Timetable& answer)
{
    TimeSlot ts11("Monday", "09:00", "10:35");
    
    Instructor instructor1("Dr. Smith", {ts11}, {});
    
    university->addTimeSlot({ts11});
    university->addInstructor({instructor1});
    
    result = (university->schedule(false))[0];
}

void testContents::schedule9(University* university, Timetable& result, Timetable& answer)
{
    TimeSlot ts11("Monday", "09:00", "10:35");
    
    Course course1("Mathematical statistics", {});
    
    university->addTimeSlot({ts11});
    university->addCourse({course1});
    
    result = (university->schedule(false))[0];
}


void testContents::persistence1(University* university, University* other)
{
    TimeSlot ts11("Monday", "09:00", "10:35");
    TimeSlot ts12("Monday", "10:45", "12:20");
    
    Course course1("Mathematical statistics", {ts12});
    Course course2("Calculus", {ts11});
    
    Instructor instructor1("Dr. Smith", {ts11}, {course2});
    Instructor instructor2("Dr. Johnson", {ts12}, {course1});
    
    university->addTimeSlot({ts11, ts12});
    university->addCourse({course1, course2});
    university->addInstructor({instructor1, instructor2});
    
    university->saveState(std::string(TEST_PATH) + "/test_dataset.json");
    other->loadState(std::string(TEST_PATH) + "/test_dataset.json");
}

void testContents::persistence2(University* university, University* other)
{
    TimeSlot ts11("Monday", "09:00", "10:35");
    
    Course course1("Mathematical statistics", {});
    Course course2("Calculus", {ts11});
    
    Instructor instructor1("Dr. Smith", {ts11}, {course2});
    
    university->addTimeSlot({ts11});
    university->addCourse({course1, course2});
    university->addInstructor({instructor1});
    
    university->saveState(std::string(TEST_PATH) + "/test_dataset.json");
    other->loadState(std::string(TEST_PATH) + "/test_dataset.json");
}