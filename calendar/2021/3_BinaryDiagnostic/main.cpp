#include <BinaryDiagnosticSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	using namespace aoc2021::BinaryDiagnostic;
	SolveProblemAndDisplay<BinaryDiagnosticSolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}