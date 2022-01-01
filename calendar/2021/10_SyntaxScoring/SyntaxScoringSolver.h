#pragma once

#include <ProblemSolver.h>

#include <optional>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

namespace aoc2021::SyntaxScoring
{
    static const std::regex RE_OPEN_SYMBOL { R"(\(|\[|\<|\{)" };
    static const std::regex RE_CLOSE_SYMBOL { R"(\)|\]|\>|\})" };

    static const std::unordered_map<char, char> CHUNK_COUPLES
    {
        { '(', ')' },
        { '[', ']' },
        { '{', '}' },
        { '<', '>' }
    };

    static const std::unordered_map<char, std::uint32_t> ERROR_SCORES
    {
        { ')', 3        },
        { ']', 57       },
        { '}', 1197     },
        { '>', 25137    }
    };

    static const std::unordered_map<char, std::uint32_t> COMPLETION_SCORES
    {
        { ')', 1 },
        { ']', 2 },
        { '}', 3 },
        { '>', 4 }
    };

    enum class SyntaxErrorCode
    {
        None,
        Corrupted,
        Incomplete,
        UnmatchedOpenClose
    };

    struct SyntaxError final
    {
        SyntaxErrorCode m_Code { SyntaxErrorCode::None };
        std::optional<char> m_UnexpectedCharacter { };
    };

    using NavigationSubsystem = std::vector<std::string>;

    std::uint32_t ComputeLineErrorScore(const std::string& line);
    SyntaxError ValidateLine(const std::string& line);

    std::string GetCompletionString(const std::string& line);
    std::uint64_t GetCompletionStringScore(const std::string& completionString);


    class SyntaxScoringSolver : public ProblemSolver<std::string, std::uint32_t, std::uint64_t>
    {
    public:
        void Init(std::string& input) override;
        std::uint32_t SolveProblemA() const override;
        std::uint64_t SolveProblemB() const override;

    private:
        NavigationSubsystem m_NavigationSubsystem;
    };
}