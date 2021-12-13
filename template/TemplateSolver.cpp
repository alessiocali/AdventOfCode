#include <||PROBLEM_SOLVER||.h>

#include <cassert>
#include <fstream>
#include <string>

namespace ||YEAR_NAMESPACE||::||PROBLEM_NAME||
{
    void ||PROBLEM_SOLVER||::Init(std::string& inputFileName)
    {
        std::ifstream input { inputFileName };
        assert(input.is_open());

        for (std::string line; std::getline(input, line); )
        {
            // Do stuff
        }
    }

    std::uint32_t ||PROBLEM_SOLVER||::SolveProblemA() const
    {
        return 0;
    }

    std::uint32_t ||PROBLEM_SOLVER||::SolveProblemB() const
    {
        return 0;
    }
}