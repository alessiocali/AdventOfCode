#include <TransparentOrigamiSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	using namespace aoc2021::TransparentOrigami;
	SolveProblemAndDisplay<TransparentOrigamiSolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}