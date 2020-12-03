#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <ReportRepairSolver.h>
#include <PasswordPhilosophySolver.h>
#include <TobogganTrajectorySolver.h>

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

TEST_CASE("PasswordPhilosophy")
{
    constexpr const char* input = "inputs/PasswordPhilosophy_Input.txt";
    ValidateProblem<PasswordPhilosophySolver, std::string>(input, 556, 605);
}

TEST_CASE("TobogganTrajectory")
{
    constexpr const char* input = "inputs/TobogganTrajectory_Input.txt";
    ValidateProblem<TobogganTrajectorySolver, std::string>(input, 153, 2421944712);
}