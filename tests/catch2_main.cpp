#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <ReportRepairSolver.h>

template<typename Solver, typename InputType, typename SolutionAType, typename SolutionBType>
void ValidateProblem(InputType input, const SolutionAType& solutionA, const SolutionBType& solutionB)
{
	Solver solver;
	solver.Init(input);

	REQUIRE(solver.SolveProblemA() == solutionA);
	REQUIRE(solver.SolveProblemB() == solutionB);
}

TEST_CASE("ReportRepair")
{
    constexpr const char* input = "inputs/ReportRepair_Input.txt";
    ValidateProblem<ReportRepairSolver, std::string>(input, 866436, 276650720);
}