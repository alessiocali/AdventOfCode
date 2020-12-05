#include "BinaryBoardingSolver.h"

#include <fstream>
#include <string>
#include <cassert>
#include <algorithm>
#include <optional>

void BinaryBoardingSolver::Init(std::string& input)
{
    std::ifstream inputStream(input);
    std::string temp;
    while (std::getline(inputStream, temp))
    {
        std::uint8_t rowMin { 0 };
        std::uint8_t rowMax { 127 };
        std::uint8_t colMin { 0 };
        std::uint8_t colMax { 7 };

        auto binaryPartition = 
        [&temp](std::uint8_t min, std::uint8_t max, std::uint8_t toTest, std::size_t offset, char lowerHalfChar, char upperHalfChar)
        {
            std::uint8_t range = max - min + 1;
            for (std::size_t i = 0; i < toTest; i++)
            {
                if (temp[i + offset] == lowerHalfChar)
                {
                    max -= range / 2;
                }
                else 
                {
                    assert(temp[i + offset] == upperHalfChar);
                    min += range / 2;
                }

                range /= 2;
            }

            assert(min == max);
            return min;
        };

        m_Problem.emplace_back(Seat { binaryPartition(0, 127, 7, 0, 'F', 'B'), binaryPartition(0, 7, 3, 7, 'L', 'R') });
    }

    std::sort(m_Problem.begin(), m_Problem.end());
}

std::uint32_t BinaryBoardingSolver::SolveProblemA() const
{
    auto maxElement = std::max_element(m_Problem.begin(), m_Problem.end());
    if (maxElement == m_Problem.end())
    {
        return 0;
    }

    return maxElement->m_Id;
}

std::uint32_t BinaryBoardingSolver::SolveProblemB() const
{
    constexpr std::size_t MIN_ID = 8;
    std::optional<std::uint32_t> previousId;
    for (std::size_t i = 0; i < m_Problem.size(); i++)
    {
        std::uint32_t id = m_Problem[i].m_Id;

        if (id < MIN_ID)
        {
            continue;
        }

        if (!previousId.has_value())
        {
            previousId = id;
            continue;
        }

        if (id != *previousId + 1)
        {
            assert(id == *previousId + 2);
            return id - 1;
        }

        previousId = id;
    }

    assert(false);
    return 0;
}
