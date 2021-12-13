#include <RainRiskSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	SimpleProgramArgs args = SimpleGetProgramArgs(argc, argv);
	SolveProblemAndDisplay<RainRiskSolver, std::string>(args.m_InputFile, args.m_Debug);
}