#pragma once

#include <iostream>
#include <exception>
#include <regex>
#include <string>
#include <set>
#include <unordered_map>
#include <nlohmann/json.hpp>

class TimeSlot
{
private:
    std::string day;
    std::string startTime;
    std::string endTime;

public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(TimeSlot, day, startTime, endTime)
    
    TimeSlot() = default;
    
    TimeSlot(const std::string& _day, const std::string& _startTime, const std::string& _endTime) : day(_day),
            startTime(_startTime), endTime(_endTime)
    {
        // Checking for validity
        std::set<std::string> days{"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
        
        if (days.find(_day) == days.end())
            throw std::invalid_argument("Not a valid day of the week. Day of the week must start with uppercase.");
        
        std::regex timePattern(R"(^([01][0-9]):([0-5][0-9])$)");
        if (!std::regex_match(_startTime, timePattern) || !std::regex_match(_endTime, timePattern))
            throw std::invalid_argument("Not a valid time value or format. Format must be \"nn:nn\".");
    }
    
    [[nodiscard]] std::string getFull() const { return day + ", " + startTime + " - " + endTime; }
    
    bool operator <(const TimeSlot& other) const
    {
        // Map days of the week to their corresponding number
        std::vector<std::string> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
        std::unordered_map<std::string, int> dayMatcher;
        
        for (int i = 0; i < days.size(); ++i)
            dayMatcher.insert({days[i], i});
        
        if (day != other.day)
            return dayMatcher[day] < dayMatcher[other.day];
        
        if (startTime != other.startTime)
        {
            // Count total minutes of left operand
            std::string hours = startTime.substr(0, 2);
            std::string minutes = startTime.substr(3, 2);
            int totalMinutes = 60 * stoi(hours) + stoi(minutes);
            
            // Count total minutes of right operand
            std::string other_hours = other.startTime.substr(0, 2);
            std::string other_minutes = other.startTime.substr(3, 2);
            int other_totalMinutes = 60 * stoi(other_hours) + stoi(other_minutes);
            
            return totalMinutes < other_totalMinutes;
        }
        
        // In case they are equal
        return false;
    }
    
    bool operator ==(const TimeSlot& rhs) const
    { return this->day == rhs.day && this->startTime == rhs.startTime && this->endTime == rhs.endTime; }
    
    void displayInfo(int nestedLevel = 0, int indentation = 4) const
    {
        std::cout << std::string(nestedLevel * indentation, ' ');
        std::cout << "Day: " << day << ", Start Time: " << startTime << ", End Time: " << endTime << std::endl;
    }
};
