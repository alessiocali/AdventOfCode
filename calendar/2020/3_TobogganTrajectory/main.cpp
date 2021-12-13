#include <TobogganTrajectorySolver.h>

#include "CommonHelpers.h"

int main(int argc, char** argv)
{
	SolveProblemAndDisplay<TobogganTrajectorySolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}