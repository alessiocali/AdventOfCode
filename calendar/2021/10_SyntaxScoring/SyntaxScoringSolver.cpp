#include <SyntaxScoringSolver.h>

#include <cassert>
#include <fstream>
#include <numeric>
#include <ranges>
#include <stack>
#include <string>

#include <range/v3/all.hpp>

namespace aoc2021::SyntaxScoring
{
    std::uint32_t ComputeLineErrorScore(const std::string& line)
    {
        const SyntaxError error = ValidateLine(line);
        return error.m_Code == SyntaxErrorCode::Corrupted ? ERROR_SCORES.at(*error.m_UnexpectedCharacter) : 0;
    }

    SyntaxError ValidateLine(const std::string& line)
    {
        assert(!line.empty());

        std::stack<char> parsingStack;
        for (auto it = std::begin(line); it != std::end(line); it++)
        {
            if (std::regex_match(it, it + 1, RE_OPEN_SYMBOL))
            {
                parsingStack.push(*it);
            }
            else if (std::regex_match(it, it + 1, RE_CLOSE_SYMBOL))
            {
                if (parsingStack.empty())
                {
                    return { SyntaxErrorCode::UnmatchedOpenClose, *it };
                }

                const char expected = CHUNK_COUPLES.at(parsingStack.top());
                if (expected == *it)
                {
                    parsingStack.pop();
                }
                else
                {
                    return { SyntaxErrorCode::Corrupted, *it };
                }
            }
        }

        if (parsingStack.empty())
        {
            return { SyntaxErrorCode::None, std::nullopt };
        }
        else
        {
            return { SyntaxErrorCode::Incomplete, std::nullopt };
        }
    }

    std::string GetCompletionString(const std::string& line)
    {
        std::stack<char> parsingStack;
        for (auto it = std::begin(line); it != std::end(line); it++)
        {
            if (std::regex_match(it, it + 1, RE_OPEN_SYMBOL))
            {
                parsingStack.push(*it);
            }
            else if (std::regex_match(it, it + 1, RE_CLOSE_SYMBOL))
            {
                assert(!parsingStack.empty() && CHUNK_COUPLES.at(parsingStack.top()) == *it);
                parsingStack.pop();
            }
        }

        std::string completionString;
        while (!parsingStack.empty())
        {
            completionString += CHUNK_COUPLES.at(parsingStack.top());
            parsingStack.pop();
        }

        return completionString;
    }

    std::uint64_t GetCompletionStringScore(const std::string& completionString)
    {
        auto scoreAccumulator = [](std::uint64_t score, const char character)
        {
            return score * 5u + COMPLETION_SCORES.at(character);
        };

        return std::accumulate(std::begin(completionString), std::end(completionString), std::uint64_t { 0 }, scoreAccumulator);
    }

    void SyntaxScoringSolver::Init(std::string& inputFileName)
    {
        std::ifstream input { inputFileName };
        assert(input.is_open());

        for (std::string line; std::getline(input, line); )
        {
            m_NavigationSubsystem.emplace_back(std::move(line));
        }
    }

    std::uint32_t SyntaxScoringSolver::SolveProblemA() const
    {
        auto scores = m_NavigationSubsystem | std::views::transform(&ComputeLineErrorScore);
        return std::accumulate(std::begin(scores), std::end(scores), 0u);
    }

    std::uint64_t SyntaxScoringSolver::SolveProblemB() const
    {
        auto isIncomplete = [](const std::string& line) { return ValidateLine(line).m_Code == SyntaxErrorCode::Incomplete; };
        
        std::vector<std::uint64_t> scores = m_NavigationSubsystem 
            | std::views::filter(isIncomplete) 
            | std::views::transform(&GetCompletionString)
            | std::views::transform(&GetCompletionStringScore)
            | ranges::to_vector;

        std::size_t middle = std::size(scores) / 2;
        std::nth_element(std::begin(scores), std::begin(scores) + middle, std::end(scores));
        return scores[middle];
    }
}