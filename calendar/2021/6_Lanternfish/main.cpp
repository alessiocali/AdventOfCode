#include <LanternfishSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	using namespace aoc2021::Lanternfish;
	SolveProblemAndDisplay<LanternfishSolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}