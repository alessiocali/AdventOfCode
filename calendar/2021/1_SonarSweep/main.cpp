#include <SonarSweepSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	using namespace aoc2021::SonarSweep;
	SolveProblemAndDisplay<SonarSweepSolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}