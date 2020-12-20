#include <TicketTranslationSolver.h>
#include <CommonHelpers.h>

int main(int argc, char** argv)
{
	SolveProblemAndDisplay<TicketTranslationSolver, std::string>(SimpleGetInputFileFromArgs(argc, argv));
}