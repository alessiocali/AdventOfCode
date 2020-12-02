#include <PasswordPhilosophySolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	SolveProblemAndDisplay<PasswordPhilosophySolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}