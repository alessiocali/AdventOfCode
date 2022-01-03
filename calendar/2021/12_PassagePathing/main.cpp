#include <PassagePathingSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	using namespace aoc2021::PassagePathing;
	SolveProblemAndDisplay<PassagePathingSolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}