#include <gtest/gtest.h>
#include "DummyUniversity.hpp"

#include "../TestContents.hpp"

TEST(DummyUniversity, schedule1)
{
    DummyUniversity university;
    Timetable result, answer;
    
    testContents::schedule1(&university, result, answer);
    
    EXPECT_EQ(result, answer);
}

TEST(DummyUniversity, schedule2)
{
    DummyUniversity university;
    Timetable result, answer;
    
    testContents::schedule2(&university, result, answer);
    
    EXPECT_EQ(result, answer);
}

TEST(DummyUniversity, schedule3)
{
    DummyUniversity university;
    Timetable result, answer;
    
    testContents::schedule3(&university, result, answer);
    
    EXPECT_EQ(result, answer);
}

TEST(DummyUniversity, schedule4)
{
    DummyUniversity university;
    Timetable result, answer;
    
    testContents::schedule4(&university, result, answer);
    
    EXPECT_EQ(result, answer);
}

TEST(DummyUniversity, schedule5)
{
    DummyUniversity university;
    Timetable result, answer;
    
    testContents::schedule5(&university, result, answer);
    
    EXPECT_EQ(result, answer);
}

TEST(DummyUniversity, schedule6)
{
    DummyUniversity university;
    Timetable result, answer;
    
    testContents::schedule6(&university, result, answer);
    
    EXPECT_EQ(result, answer);
}

TEST(DummyUniversity, schedule7)
{
    DummyUniversity university;
    Timetable result, answer;
    
    testContents::schedule7(&university, result, answer);
    
    EXPECT_EQ(result, answer);
}

TEST(DummyUniversity, schedule8)
{
    DummyUniversity university;
    Timetable result, answer;
    
    testContents::schedule8(&university, result, answer);
    
    EXPECT_EQ(result, answer);
}

TEST(DummyUniversity, schedule9)
{
    DummyUniversity university;
    Timetable result, answer;
    
    testContents::schedule9(&university, result, answer);
    
    EXPECT_EQ(result, answer);
}


TEST(DummyUniversity, persistence1)
{
    DummyUniversity university, other;
    
    testContents::persistence1(&university, &other);
    
    EXPECT_EQ(university, other);
}

TEST(DummyUniversity, persistence2)
{
    DummyUniversity university, other;
    
    testContents::persistence2(&university, &other);
    
    EXPECT_EQ(university, other);
}