#include <RambunctiousRecitationSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	SolveProblemAndDisplay<RambunctiousRecitationSolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}