#include <PassportProcessingSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	SolveProblemAndDisplay<PassportProcessingSolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}