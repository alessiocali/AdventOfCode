#include <HydrothermalVentureSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	using namespace aoc2021::HydrothermalVenture;
	SolveProblemAndDisplay<HydrothermalVentureSolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}