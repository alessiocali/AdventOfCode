#include <DiveSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	using namespace aoc2021::Dive;
	SolveProblemAndDisplay<DiveSolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}