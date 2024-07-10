#include <gtest/gtest.h>
#include "BruteForceUniversity.hpp"

#include "../TestContents.hpp"

TEST(BruteForceUniversity, schedule1)
{
    BruteForceUniversity university;
    Timetable result, answer;
    
    testContents::schedule1(&university, result, answer);
    
    EXPECT_EQ(result, answer);
}

TEST(BruteForceUniversity, schedule2)
{
    BruteForceUniversity university;
    Timetable result, answer;
    
    testContents::schedule2(&university, result, answer);
    
    EXPECT_EQ(result, answer);
}

TEST(BruteForceUniversity, schedule3)
{
    BruteForceUniversity university;
    Timetable result, answer;
    
    testContents::schedule3(&university, result, answer);
    
    EXPECT_EQ(result, answer);
}

TEST(BruteForceUniversity, schedule4)
{
    BruteForceUniversity university;
    Timetable result, answer;
    
    testContents::schedule4(&university, result, answer);
    
    EXPECT_EQ(result, answer);
}

TEST(BruteForceUniversity, schedule5)
{
    BruteForceUniversity university;
    Timetable result, answer;
    
    testContents::schedule5(&university, result, answer);
    
    EXPECT_EQ(result, answer);
}

TEST(BruteForceUniversity, schedule6)
{
    BruteForceUniversity university;
    Timetable result, answer;
    
    testContents::schedule6(&university, result, answer);
    
    EXPECT_EQ(result, answer);
}

TEST(BruteForceUniversity, schedule7)
{
    BruteForceUniversity university;
    Timetable result, answer;
    
    testContents::schedule7(&university, result, answer);
    
    EXPECT_EQ(result, answer);
}

TEST(BruteForceUniversity, schedule8)
{
    BruteForceUniversity university;
    Timetable result, answer;
    
    testContents::schedule8(&university, result, answer);
    
    EXPECT_EQ(result, answer);
}

TEST(BruteForceUniversity, schedule9)
{
    BruteForceUniversity university;
    Timetable result, answer;
    
    testContents::schedule9(&university, result, answer);
    
    EXPECT_EQ(result, answer);
}


TEST(BruteForceUniversity, persistence1)
{
    BruteForceUniversity university, other;
    
    testContents::persistence1(&university, &other);
    
    EXPECT_EQ(university, other);
}

TEST(BruteForceUniversity, persistence2)
{
    BruteForceUniversity university, other;
    
    testContents::persistence2(&university, &other);
    
    EXPECT_EQ(university, other);
}