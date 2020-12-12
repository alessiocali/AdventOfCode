#include <SeatingSystemSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	SolveProblemAndDisplay<SeatingSystemSolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}