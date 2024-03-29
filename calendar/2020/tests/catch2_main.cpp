#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <ReportRepairSolver.h>
#include <PasswordPhilosophySolver.h>
#include <TobogganTrajectorySolver.h>
#include <PassportProcessingSolver.h>
#include <BinaryBoardingSolver.h>
#include <CustomCustomsSolver.h>
#include <HandyHaversacksSolver.h>
#include <HandheldHaltingSolver.h>
#include <EncodingErrorSolver.h>
#include <AdapterArraySolver.h>
#include <SeatingSystemSolver.h>

template<typename Solver, typename InputType, typename SolutionAType, typename SolutionBType>
void ValidateProblem(InputType input, const SolutionAType& solutionA, const SolutionBType& solutionB)
{
    Solver solver { };
    solver.SetRunType(RunType::Test);
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

TEST_CASE("PassportProcessing")
{
    constexpr const char* input = "inputs/PassportProcessing_Input.txt";
    ValidateProblem<PassportProcessingSolver, std::string>(input, 233, 111);
}

TEST_CASE("BinaryBoarding")
{
    constexpr const char* input = "inputs/BinaryBoarding_Input.txt";
    ValidateProblem<BinaryBoardingSolver, std::string>(input, 871, 640);
}

TEST_CASE("CustomCustoms")
{
    constexpr const char* input = "inputs/CustomCustoms_Input.txt";
    ValidateProblem<CustomCustomsSolver, std::string>(input, 6885, 3550);
}

TEST_CASE("HandyHaversacks")
{
    constexpr const char* input = "inputs/HandyHaversacks_Input.txt";
    ValidateProblem<HandyHaversacksSolver, std::string>(input, 169, 82372);
}

TEST_CASE("HandheldHalting")
{
    constexpr const char* input = "inputs/HandheldHalting_Input.txt";
    ValidateProblem<HandheldHaltingSolver, std::string>(input, 1200, 1023);
}

TEST_CASE("EncodingError")
{
    constexpr const char* input = "inputs/EncodingError_Input.txt";
    ValidateProblem<EncodingErrorSolver, std::string>(input, 3199139634, 438559930);
}

TEST_CASE("AdapterArray")
{
    // TODO: Part 2
    constexpr const char* input = "inputs/AdapterArray_Input.txt";
    ValidateProblem<AdapterArraySolver, std::string>(input, 3034, 0);
}

TEST_CASE("SeatingSystem")
{
    constexpr const char* input = "inputs/SeatingSystem_Input.txt";
    ValidateProblem<SeatingSystemSolver, std::string>(input, 2344, 2076);
}