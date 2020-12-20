#include "TicketTranslationSolver.h"

#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <regex>
#include <unordered_set>

void TicketTranslationSolver::Init(std::string& input)
{
    std::ifstream inputStream(input);
    assert(inputStream.is_open());

    std::smatch match;

    for (std::string line; std::getline(inputStream, line) && !line.empty(); )
    {
        if (std::regex_match(line, match, std::regex { R"(((?:\w|\s)+): (\d+)\-(\d+) or (\d+)\-(\d+))" }))
        {
            auto& rule = m_Problem.m_Ruleset.emplace_back();
            rule.m_Name = match[1];
            rule.m_FirstRange.first = std::stoi(match[2]);
            rule.m_FirstRange.second = std::stoi(match[3]);
            rule.m_SecondRange.first = std::stoi(match[4]);
            rule.m_SecondRange.second = std::stoi(match[5]);
        }
    }

    std::string header;
    std::getline(inputStream, header);
    assert(header == "your ticket:");

    std::string myTicketString;
    std::getline(inputStream, myTicketString);
    std::stringstream sstream(myTicketString);
    for (std::string num; std::getline(sstream, num, ',');)
    {
        m_Problem.m_Ticket.push_back(std::stoi(num));
    }

    std::getline(inputStream, header);
    std::getline(inputStream, header);
    assert(header == "nearby tickets:");

    for (std::string line; std::getline(inputStream, line); )
    {
        std::stringstream ticketStream(line);
        auto& ticket = m_Problem.m_NearbyTickets.emplace_back();
        for (std::string num; std::getline(ticketStream, num, ',');)
        {
            ticket.emplace_back(std::stoi(num));
        }
    }
}

std::uint32_t TicketTranslationSolver::SolveProblemA() const
{
    auto matchesRule = [](std::uint32_t val, const Rule& rule)
    {
        return  (rule.m_FirstRange.first <= val && val <= rule.m_FirstRange.second) ||
                (rule.m_SecondRange.first <= val && val <= rule.m_SecondRange.second);
    };

    std::uint32_t scanningErrorRate { 0 };
    for (const auto& ticket : m_Problem.m_NearbyTickets)
    {
        bool isTicketValid { true };
        for (const auto val : ticket)
        {
            const bool isValueValid = std::any_of(m_Problem.m_Ruleset.cbegin(), m_Problem.m_Ruleset.cend(), 
            [val, &matchesRule](const Rule& rule)
            {
                return matchesRule(val, rule);
            });

            if (!isValueValid) { scanningErrorRate += val; }
        }
    }

    return scanningErrorRate;
}

std::uint64_t TicketTranslationSolver::SolveProblemB() const
{
    // A CandidateList contains all rules that can match all tickets in a certain slot.
    // So, for the n-th list, it is true that for all tickets the nth position matches that rule's name
    using CandidateListPerSlot = std::vector< std::unordered_set<std::string> >;

    CandidateListPerSlot slotCandidates;

    // Start by filtering the invalid tickets
    auto matchesRule = [](std::uint32_t val, const Rule& rule)
    {
        return  (rule.m_FirstRange.first <= val && val <= rule.m_FirstRange.second) ||
                (rule.m_SecondRange.first <= val && val <= rule.m_SecondRange.second);
    };

    std::vector<Ticket> validTickets { m_Problem.m_NearbyTickets };
    validTickets.erase(std::remove_if(validTickets.begin(), validTickets.end(),
    [&matchesRule, this](const Ticket& ticket)
    {
        return std::any_of(ticket.cbegin(), ticket.cend(),
        [&matchesRule, this](const auto val)
        {
            return !std::any_of(m_Problem.m_Ruleset.cbegin(), m_Problem.m_Ruleset.cend(),
            [val, &matchesRule](const auto& rule)
            {
                return matchesRule(val, rule);
            });
        });
    }), validTickets.end());

    auto isValidRuleForSlot = [&matchesRule, &validTickets](const Rule& rule, std::size_t slot)
    {
        return std::all_of(validTickets.cbegin(), validTickets.cend(),
        [&matchesRule, &rule, slot](const auto& ticket)
        {
            const bool matches = matchesRule(ticket[slot], rule);
            return matches;
        });
    };

    // Now iterate all slots, then check which rules match all of the i-th slot, and put them in the CandidateList
    for (std::size_t i = 0; i < m_Problem.m_Ruleset.size(); i++)
    {
        auto& candidateList = slotCandidates.emplace_back();
        for (const auto& rule : m_Problem.m_Ruleset)
        {            
            if (isValidRuleForSlot(rule, i))
            {
                candidateList.insert(rule.m_Name);
            }
        }
    }

    // Now we have candidate sets with potential rules per slot.
    // Let's start by fixating all rules that have one single candidate.
    //
    // We can do this by removing the candidates that appear in a single-size list from other lists
    // We keep doing this until the list stabilizes

    bool changed { false };
    do
    {
        changed = false;
        for (std::size_t i = 0; i < slotCandidates.size(); i++)
        {
            const auto& slotList = slotCandidates[i];
            if (slotList.size() > 1)
            {
                continue;
            }

            assert(slotList.size() == 1);
            const auto& ruleToTest = *slotList.cbegin();

            for (std::size_t j = 0; j < slotCandidates.size(); j++)
            {
                if (j == i)
                {
                    // Don't change the single element list!
                    continue;
                }

                if (slotCandidates[j].count(ruleToTest) > 0)
                {
                    changed = true;
                    slotCandidates[j].erase(ruleToTest);
                }
            }
        }
    } while (changed);

    // Ensure the lists are still valid
    assert(std::all_of(slotCandidates.cbegin(), slotCandidates.cend(), [](const auto& list) { return list.size() > 0; }));

    // There are no more duplicates. This is empyrical and not generic, but we'll make do
    assert(std::all_of(slotCandidates.cbegin(), slotCandidates.cend(), [](const auto& list) { return list.size() == 1; }));

    std::uint64_t result { 1 };
    for (std::size_t i = 0; i < slotCandidates.size(); i++)
    {
        const auto& ruleName = *slotCandidates[i].cbegin();
        if (!ruleName.find("departure", 0) == 0)
        {
            continue;
        }

        result *= m_Problem.m_Ticket[i];
    }

    return result;
}
