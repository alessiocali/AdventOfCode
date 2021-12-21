#include <SevenSegmentSearchSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	using namespace aoc2021::SevenSegmentSearch;
	SolveProblemAndDisplay<SevenSegmentSearchSolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}