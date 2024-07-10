#pragma once

#include "University.hpp"

class DummyUniversity : public University
{
public:
    std::vector<Timetable> schedule(bool toggleMessage = true) override;
    
    ~DummyUniversity() override = default;
};