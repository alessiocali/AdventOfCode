#include <CustomCustomsSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	SolveProblemAndDisplay<CustomCustomsSolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}