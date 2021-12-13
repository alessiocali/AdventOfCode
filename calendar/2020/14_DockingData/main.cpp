#include <DockingDataSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	SolveProblemAndDisplay<DockingDataSolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}