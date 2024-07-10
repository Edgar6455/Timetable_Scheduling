#pragma once

#include "DummyUniversity.hpp"
#include "BruteForceUniversity.hpp"

class HybridUniversity : public University
{
public:
    std::vector<Timetable> schedule(bool toggleMessage = true) override;
    
    ~HybridUniversity() override = default;
};
