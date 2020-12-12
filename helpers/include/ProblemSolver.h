#pragma once

#include <iostream>

enum class RunType
{
    Debug, // Development
    Run,   // Fast-execution, no debug display
    Test   // Testing only, no need to display anything
};

template<typename Solver, typename InputType>
void SolveProblemAndDisplay(InputType input, bool doDebug = false)
{
    Solver solver { };
    solver.SetRunType(doDebug ? RunType::Debug : RunType::Run);
    solver.Init(input);
    solver.OutputResult();

    if (solver.IsDebugging())
    {
        solver.DebugDisplay();
    }
}

template<typename InputType, typename SolutionAType, typename SolutionBType>
class ProblemSolver
{
public:
	virtual void Init(InputType& input) = 0;
	virtual SolutionAType SolveProblemA() const = 0;
	virtual SolutionBType SolveProblemB() const = 0;

	virtual void DebugDisplay() const { };

    void OutputResult() const
    {
		SolutionAType solutionA = SolveProblemA();
		SolutionBType solutionB = SolveProblemB();

        std::cout << "Solution of Problem A: " << solutionA << std::endl;
        std::cout << "Solution of Problem B: " << solutionB << std::endl;
    }

    inline void SetRunType(RunType runType) { m_RunType = runType; }
    inline bool IsDebugging() const { return m_RunType == RunType::Debug; }

private:
    RunType m_RunType;
};