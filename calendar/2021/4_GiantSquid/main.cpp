#include <GiantSquidSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	using namespace aoc2021::GiantSquid;
	SolveProblemAndDisplay<GiantSquidSolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}