#include <Solver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	SimpleProgramArgs args = SimpleGetProgramArgs(argc, argv);
	SolveProblemAndDisplay<JurassicJigsaw::Solver, std::string>(args.m_InputFile, args.m_Debug);
}