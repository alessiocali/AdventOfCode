#include "CustomCustomsSolver.h"

#include <string>
#include <fstream>
#include <numeric>

void CustomCustomsSolver::Init(std::string& input)
{
    Group* current = nullptr;
    std::ifstream inputStream(input);
    std::string temp;
    bool doAllSetInit = true;
    std::bitset<QUESTION_COUNT> tempSetForUser;
    while (std::getline(inputStream, temp))
    {
        if (temp.size() == 0)
        {
            current = nullptr;
            continue;
        }
        
        if (current == nullptr)
        {
            current = &m_Problem.emplace_back();
            doAllSetInit = true;
        }

        for (const char question : temp)
        {
            std::size_t idx = question - 'a';
            current->m_AnyAnswered.set(idx);
            tempSetForUser.set(idx);
        }

        if (doAllSetInit)
        {
            // First user, do initialization
            current->m_AllAnswered = tempSetForUser;
        }
        else
        {
            // Next users, AND with current set
            current->m_AllAnswered &= tempSetForUser;
        }

        doAllSetInit = false;
        tempSetForUser.reset();
    }
}

std::size_t CustomCustomsSolver::SolveProblemA() const
{
    return std::accumulate(m_Problem.cbegin(), m_Problem.cend(), std::size_t { 0 },
    [](std::size_t current, const Group& group) -> std::size_t
    {
        return current + group.m_AnyAnswered.count();
    });
}

std::size_t CustomCustomsSolver::SolveProblemB() const
{
    return std::accumulate(m_Problem.cbegin(), m_Problem.cend(), std::size_t { 0 },
    [](std::size_t current, const Group& group) -> std::size_t
    {
        return current + group.m_AllAnswered.count();
    });
}
