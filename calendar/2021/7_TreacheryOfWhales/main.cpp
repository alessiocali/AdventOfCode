#include <TreacheryOfWhalesSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	using namespace aoc2021::TreacheryOfWhales;
	SolveProblemAndDisplay<TreacheryOfWhalesSolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}