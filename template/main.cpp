#include <||PROBLEM_SOLVER||.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	using namespace ||YEAR_NAMESPACE||::||PROBLEM_NAME||;
	SolveProblemAndDisplay<||PROBLEM_SOLVER||, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}