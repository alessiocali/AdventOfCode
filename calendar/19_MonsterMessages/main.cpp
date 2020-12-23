#include <MonsterMessagesSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	SolveProblemAndDisplay<MonsterMessagesSolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}