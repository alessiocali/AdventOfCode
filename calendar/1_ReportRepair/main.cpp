#include <ReportRepairSolver.h>

int main(int argc, char** argv)
{
	if (argc <= 1)
	{
		std::cout << "Usage: " << argv[0] << " <input_file>" << std::endl;
		return 0;
	}

	SolveProblemAndDisplay<ReportRepairSolver, std::string>(argv[1]);
}