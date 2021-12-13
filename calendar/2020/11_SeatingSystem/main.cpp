#include <SeatingSystemSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	SimpleProgramArgs args = SimpleGetProgramArgs(argc, argv);
	SolveProblemAndDisplay<SeatingSystemSolver, std::string>(args.m_InputFile, args.m_Debug);
}