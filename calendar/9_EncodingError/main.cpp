#include <EncodingErrorSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	SolveProblemAndDisplay<EncodingErrorSolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}