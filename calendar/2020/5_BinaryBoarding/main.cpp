#include <BinaryBoardingSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	SolveProblemAndDisplay<BinaryBoardingSolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}