#include <gtest/gtest.h>
#include "HybridUniversity.hpp"

#include "../TestContents.hpp"

TEST(HybridUniversity, schedule1)
{
    HybridUniversity university;
    Timetable result, answer;
    
    testContents::schedule1(&university, result, answer);
    
    EXPECT_EQ(result, answer);
}

TEST(HybridUniversity, schedule2)
{
    HybridUniversity university;
    Timetable result, answer;
    
    testContents::schedule2(&university, result, answer);
    
    EXPECT_EQ(result, answer);
}

TEST(HybridUniversity, schedule3)
{
    HybridUniversity university;
    Timetable result, answer;
    
    testContents::schedule3(&university, result, answer);
    
    EXPECT_EQ(result, answer);
}

TEST(HybridUniversity, schedule4)
{
    HybridUniversity university;
    Timetable result, answer;
    
    testContents::schedule4(&university, result, answer);
    
    EXPECT_EQ(result, answer);
}

TEST(HybridUniversity, schedule5)
{
    HybridUniversity university;
    Timetable result, answer;
    
    testContents::schedule5(&university, result, answer);
    
    EXPECT_EQ(result, answer);
}

TEST(HybridUniversity, schedule6)
{
    HybridUniversity university;
    Timetable result, answer;
    
    testContents::schedule6(&university, result, answer);
    
    EXPECT_EQ(result, answer);
}

TEST(HybridUniversity, schedule7)
{
    HybridUniversity university;
    Timetable result, answer;
    
    testContents::schedule7(&university, result, answer);
    
    EXPECT_EQ(result, answer);
}

TEST(HybridUniversity, schedule8)
{
    HybridUniversity university;
    Timetable result, answer;
    
    testContents::schedule8(&university, result, answer);
    
    EXPECT_EQ(result, answer);
}

TEST(HybridUniversity, schedule9)
{
    HybridUniversity university;
    Timetable result, answer;
    
    testContents::schedule9(&university, result, answer);
    
    EXPECT_EQ(result, answer);
}


TEST(HybridUniversity, persistence1)
{
    HybridUniversity university, other;
    
    testContents::persistence1(&university, &other);
    
    EXPECT_EQ(university, other);
}

TEST(HybridUniversity, persistence2)
{
    HybridUniversity university, other;
    
    testContents::persistence2(&university, &other);
    
    EXPECT_EQ(university, other);
}