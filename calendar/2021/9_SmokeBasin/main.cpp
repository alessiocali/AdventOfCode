#include <SmokeBasinSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	using namespace aoc2021::SmokeBasin;
	SolveProblemAndDisplay<SmokeBasinSolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}