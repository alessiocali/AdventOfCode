#include <OperationOrderSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	SolveProblemAndDisplay<OperationOrderSolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}