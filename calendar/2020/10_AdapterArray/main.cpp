#include <AdapterArraySolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	SolveProblemAndDisplay<AdapterArraySolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}