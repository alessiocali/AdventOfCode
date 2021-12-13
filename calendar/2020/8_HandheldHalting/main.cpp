#include <HandheldHaltingSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	SolveProblemAndDisplay<HandheldHaltingSolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}