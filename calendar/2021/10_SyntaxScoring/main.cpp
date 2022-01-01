#include <SyntaxScoringSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	using namespace aoc2021::SyntaxScoring;
	SolveProblemAndDisplay<SyntaxScoringSolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}