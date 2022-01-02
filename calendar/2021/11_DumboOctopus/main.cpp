#include <DumboOctopusSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	using namespace aoc2021::DumboOctopus;
	SolveProblemAndDisplay<DumboOctopusSolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}