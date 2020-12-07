#include <HandyHaversacksSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	SolveProblemAndDisplay<HandyHaversacksSolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}