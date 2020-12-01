#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

template<typename Solver, typename InputType, typename SolutionAType, typename SolutionBType>
void ValidateProblem(InputType input, const SolutionAType& solutionA, const SolutionBType& solutionB)
{
	Solver solver;
	solver.Init(input);

	REQUIRE(solver.SolveProblemA() == solutionA);
	REQUIRE(solver.SolveProblemB() == solutionB);
}