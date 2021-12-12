#pragma once
#include <ProblemSolver.h>
#include <Problem.h>
#include <ImageMatcher.h>

namespace JurassicJigsaw
{
    class Solver final : public ProblemSolver<std::string, std::uint64_t, std::uint32_t>
    {
    public:
        void Init(std::string& input) override;

        std::uint64_t SolveProblemA() const override;
        std::uint32_t SolveProblemB() const override;

        virtual void DebugDisplay() const override;

    private:
        Problem m_Problem;
        ImageMatcher m_ImageMatcher;
    };
}