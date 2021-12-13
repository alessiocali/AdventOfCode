#include "PasswordPhilosophySolver.h"

#include <fstream>
#include <regex>

void PasswordPhilosophySolver::Init(std::string& input)
{
    m_Problem.clear();

    std::ifstream inputStream(input);
    std::string temp;
    while (std::getline(inputStream, temp))
    {
        m_Problem.emplace_back(Parse(temp));
    }
}

std::size_t PasswordPhilosophySolver::SolveProblemA() const
{
    return std::count_if(m_Problem.cbegin(), m_Problem.cend(), [](const PolicyPassword& passPolicy) { return passPolicy.IsValidA(); });
}

std::size_t PasswordPhilosophySolver::SolveProblemB() const
{
    return std::count_if(m_Problem.cbegin(), m_Problem.cend(), [](const PolicyPassword& passPolicy) { return passPolicy.IsValidB(); });
}

PasswordPhilosophySolver::Policy::Policy(std::string policyString)
{
    const std::regex POLICY_REGEX(R"(([0-9]+)\-([0-9]+) ([a-z]))");
    std::smatch regexMatch;
    std::regex_match(policyString, regexMatch, POLICY_REGEX);

    m_Min = std::stoi(regexMatch[1].str());
    m_Max = std::stoi(regexMatch[2].str());
    m_Character = regexMatch[3].str()[0];
}

PasswordPhilosophySolver::PolicyPassword PasswordPhilosophySolver::Parse(std::string& inputString)
{
    const std::regex INPUT_REGEX(R"((.*): (.*))");
    std::smatch regexMatch;
    std::regex_match(inputString, regexMatch, INPUT_REGEX);
    return PolicyPassword { Policy(regexMatch[1].str()), regexMatch[2].str() };
}

bool PasswordPhilosophySolver::PolicyPassword::IsValidA() const
{
    std::size_t charCount = std::count(m_Password.cbegin(), m_Password.cend(), m_Policy.m_Character);
    return m_Policy.m_Min <= charCount && charCount <= m_Policy.m_Max;
}

bool PasswordPhilosophySolver::PolicyPassword::IsValidB() const
{
    const bool isFirstPosValid = m_Policy.m_Min - 1 < m_Password.size() && m_Password[m_Policy.m_Min - 1] == m_Policy.m_Character;
    const bool isSecondPosValid = m_Policy.m_Max - 1 < m_Password.size() && m_Password[m_Policy.m_Max - 1] == m_Policy.m_Character;

    return isFirstPosValid ^ isSecondPosValid;
}