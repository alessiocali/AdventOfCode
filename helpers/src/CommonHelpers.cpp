#include <CommonHelpers.h>

#include <iostream>

#include <boost/program_options.hpp>

namespace bpo = boost::program_options;

Position Position::IntNormalize() const
{
	int mcd = GetMCD(m_X, m_Y);
	return { m_X / mcd, m_Y / mcd };
}

std::string SimpleGetInputFileFromArgs(int argc, char** argv)
{
	return SimpleGetProgramArgs(argc, argv).m_InputFile;
}

SimpleProgramArgs SimpleGetProgramArgs(int argc, char** argv)
{
	constexpr const char* AD_Input = "input,i";
	constexpr const char* AN_Input = "input";

	constexpr const char* AD_Debug = "debug,d";
	constexpr const char* AN_Debug = "debug";

	SimpleProgramArgs args;

	bpo::options_description optionsDescription("Allowed options");
	optionsDescription.add_options()
		(AD_Input, bpo::value<std::string>(&args.m_InputFile)->required(), "Problem input")
		(AD_Debug, bpo::bool_switch(&args.m_Debug), "Debug Run");

	bpo::variables_map varMap;
	bpo::store(bpo::parse_command_line(argc, argv, optionsDescription), varMap);
	bpo::notify(varMap);

	return args;
}

std::vector<uint> DecomposeInDigits(uint value)
{
	std::vector<uint> digits;
	
	do 
	{
		digits.push_back(value % 10);
		value /= 10;
	} 
	while (value > 0);
	
	return digits;
}