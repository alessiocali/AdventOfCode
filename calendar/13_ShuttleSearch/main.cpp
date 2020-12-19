#include <ShuttleSearchSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	SolveProblemAndDisplay<ShuttleSearchSolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}