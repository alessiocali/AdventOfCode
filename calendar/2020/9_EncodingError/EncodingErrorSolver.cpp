#include "EncodingErrorSolver.h"

#include <cassert>
#include <fstream>
#include <string>
#include <unordered_set>
#include <algorithm>

void EncodingErrorSolver::Init(std::string& input)
{
    std::ifstream inputStream(input);
    std::string temp;

    while (std::getline(inputStream, temp))
    {
        m_Problem.push_back(std::stoll(temp));
    }
}

std::int64_t EncodingErrorSolver::SolveProblemA() const
{
    std::unordered_set<std::int64_t> backlist;

    auto firstInBacklist = m_Problem.begin();
    auto lastInBacklist = m_Problem.begin() + BACKLIST_SIZE - 1;

    for (const std::int64_t number : m_Problem)
    {
        if (backlist.size() < BACKLIST_SIZE)
        {
            backlist.insert(number);
            continue;
        }

        bool isValid = false;
        for (const std::int64_t backlistEntry : backlist)
        {
            const std::int64_t entryCompanion = number - backlistEntry;
            if (entryCompanion == backlistEntry)
            {
                // Skip doubles
                continue;
            }

            if (backlist.count(entryCompanion) > 0)
            {
                isValid = true;
                break;
            }
        }

        if (!isValid)
        {
            // No matching sum, return
            return number;
        }

        if (lastInBacklist == m_Problem.end())
        {
            break;
        }

        lastInBacklist++;
        backlist.erase(*firstInBacklist);
        backlist.insert(*lastInBacklist);
        firstInBacklist++;
    }

    assert(false && "No solution found");
    return 0;
}

std::int64_t EncodingErrorSolver::SolveProblemB() const
{
    std::int64_t currentSum { 0 };

    auto listBegin = m_Problem.begin();
    auto listEnd = m_Problem.begin();

    while (listEnd != m_Problem.end())
    {
        if (currentSum < WEAK_NUMBER)
        {
            currentSum += *listEnd;
            listEnd++;
        }
        else if (currentSum > WEAK_NUMBER)
        {
            currentSum -= *listBegin;
            listBegin++;
        }
        else
        {
            assert(false && "Current sum is WEAK_NUMBER but should have been detected in previous iteration");
        }

        if (currentSum == WEAK_NUMBER)
        {
            auto min = std::min_element(listBegin, listEnd);
            auto max = std::max_element(listBegin, listEnd);

            assert(min != listEnd);
            assert(max != listEnd);

            return *min + *max;
        }
    }

    assert(false && "No solution found");
    return 0;
}
