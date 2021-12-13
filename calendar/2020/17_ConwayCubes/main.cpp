#include <ConwayCubesSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	SolveProblemAndDisplay<ConwayCubesSolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}