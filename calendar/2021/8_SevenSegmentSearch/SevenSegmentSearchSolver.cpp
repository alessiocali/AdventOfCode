#include <SevenSegmentSearchSolver.h>

#include <algorithm>
#include <cassert>
#include <format>
#include <fstream>
#include <functional>
#include <numeric>
#include <ranges>
#include <regex>
#include <string>

namespace aoc2021::SevenSegmentSearch
{
    std::string GetPatternIntersection(const std::string& pattern1, const std::string& pattern2)
    {
        std::string intersection;
        std::set_intersection(pattern1.begin(), pattern1.end(), pattern2.begin(), pattern2.end(), std::back_inserter(intersection));
        return intersection;
    }

    SizeToPatternAmbiguityMap BuildPatternAmbiguityMap(const PatternArray& patternArray)
    {
        SizeToPatternAmbiguityMap patternAmbiguityMap;
        for (const std::string& pattern : patternArray)
        {
            patternAmbiguityMap[pattern.size()].emplace_back(pattern);
        }
        return patternAmbiguityMap;
    }

    void AmbiguityGroup::RecomputeCommonSegmentIndices(const NumberToIndicesMapping& indexMapping)
    {
        auto numberIt = m_PotentialNumbers.begin();
        m_CommonSegmentIndices = indexMapping[*numberIt];

        auto numberToSegments = [&](const std::size_t num) -> const std::vector<std::size_t>& { return indexMapping[num]; };
        auto segmentsView = m_PotentialNumbers | std::views::transform(numberToSegments);
        auto intersectSegments = [](std::vector<std::size_t> intersectingSegments, const std::vector<std::size_t>& next)
        {
            std::vector<std::size_t> nextIntersection;
            std::set_intersection(intersectingSegments.begin(), intersectingSegments.end(), next.begin(), next.end(), std::back_inserter(nextIntersection));
            return nextIntersection;
        };

        m_CommonSegmentIndices = std::accumulate(segmentsView.begin() + 1, segmentsView.end(), *segmentsView.begin(), intersectSegments);
    }

    SizeToAmbiguityGroupMap BuildAmbiguityGroupMap(const NumberToIndicesMapping& mapping)
    {
        SizeToAmbiguityGroupMap ambiguityGroups;

        for (std::size_t n = 0; n < mapping.size(); n++)
        {
            const std::size_t segmentsCount = mapping[n].size();
            ambiguityGroups[segmentsCount].m_PotentialNumbers.emplace_back(n);
        }

        for (auto& [segmentsCount, group] : ambiguityGroups)
        {
            group.RecomputeCommonSegmentIndices(mapping);
        }

        return ambiguityGroups;
    }

    MappingDeductor::MappingDeductor(const NumberToIndicesMapping& mapping)
        : m_NumberToIndices(mapping)
        , m_AmbiguityGroups(BuildAmbiguityGroupMap(mapping))
    { }

    SignalMapping MappingDeductor::DeduceMapping(const PatternArray& patterns) const
    {
        PotentialSymbolsPerSegment potentialSymbolsPerSegment = InitPotentialSymbolsPerSegment();
        SizeToPatternAmbiguityMap patternAmbiguityMap = BuildPatternAmbiguityMap(patterns);
        
        DeducePotentialSymbolsFromAmbiguityMap(patternAmbiguityMap, potentialSymbolsPerSegment);
        EliminateConflictingSymbols(potentialSymbolsPerSegment);

        return ConvertToSignalMapping(potentialSymbolsPerSegment);
    }

    PotentialSymbolsPerSegment MappingDeductor::InitPotentialSymbolsPerSegment() const
    {
        PotentialSymbolsPerSegment potentialSymbolsPerSegment;
        for (std::string& potentialSymbols : potentialSymbolsPerSegment)
        {
            potentialSymbols = "abcdefg";
        }
        return potentialSymbolsPerSegment;
    }

    void MappingDeductor::DeducePotentialSymbolsFromAmbiguityMap(const SizeToPatternAmbiguityMap& patternAmbiguityMap, PotentialSymbolsPerSegment& potentialSymbolsPerSegment) const
    {
        for (const auto& [patternSize, ambiguousPatterns] : patternAmbiguityMap)
        {
            std::string commonPattern = std::accumulate(ambiguousPatterns.begin() + 1, ambiguousPatterns.end(), ambiguousPatterns[0], &GetPatternIntersection);
            const AmbiguityGroup& ambiguityGroup = m_AmbiguityGroups.at(patternSize);
            for (std::size_t segment : ambiguityGroup.m_CommonSegmentIndices)
            {
                std::string& potentialSymbols = potentialSymbolsPerSegment[segment];
                potentialSymbols = GetPatternIntersection(potentialSymbols, commonPattern);
            }
        }
    }

    void MappingDeductor::EliminateConflictingSymbols(PotentialSymbolsPerSegment& potentialSymbolsPerSegment) const
    {
        auto isMappingAmbiguous = [](const std::string& segmentMapping) { return segmentMapping.size() > 1; };

        bool changed { true };
        while (changed)
        {
            changed = false;
            auto nonAmbiguousMappingView = potentialSymbolsPerSegment | std::views::filter(std::not_fn(isMappingAmbiguous)) | std::views::join;
            std::string nonAmbiguousCharacters(nonAmbiguousMappingView.begin(), nonAmbiguousMappingView.end());
            std::sort(nonAmbiguousCharacters.begin(), nonAmbiguousCharacters.end());

            for (std::string& potentialSymbols : potentialSymbolsPerSegment | std::views::filter(isMappingAmbiguous))
            {
                std::string updatedSymbols;
                std::set_difference(
                    potentialSymbols.begin(), potentialSymbols.end(),
                    nonAmbiguousCharacters.begin(), nonAmbiguousCharacters.end(),
                    std::back_inserter(updatedSymbols)
                );

                potentialSymbols = updatedSymbols;
                changed = true;
            }
        }
    }

    SignalMapping MappingDeductor::ConvertToSignalMapping(const PotentialSymbolsPerSegment& potentialSymbolsPerSegment) const
    {
        SignalMapping mapping(7, 'a');
        for (std::size_t i = 0; i < potentialSymbolsPerSegment.size(); i++)
        {
            assert(potentialSymbolsPerSegment[i].size() == 1);
            mapping[i] = potentialSymbolsPerSegment[i][0];
        }
        return mapping;
    }

    SignalDecoder::SignalDecoder(const NumberToIndicesMapping& numberMapping, const SignalMapping& signalMapping)
        : m_Mapping(signalMapping)
    { 
        assert(signalMapping.size() == m_Mapping.size());

        for (std::size_t num = 0; num < numberMapping.size(); num++)
        {
            const std::vector<std::size_t>& segments = numberMapping[num];
            auto segmentRepresentationView = segments | std::views::transform([&](const std::size_t segment) { return m_Mapping[segment]; });
            std::string segmentRepresentation(segmentRepresentationView.begin(), segmentRepresentationView.end());
            std::sort(segmentRepresentation.begin(), segmentRepresentation.end());
            m_Dictionary[segmentRepresentation] = num;
        }
    }

    std::uint32_t SignalDecoder::DecodeOutput(const OutputArray& outputArray)
    {
        std::uint32_t tens { 1 };

        auto accumulateDigits = [&](const std::uint32_t current, const std::string& next)
        {
            std::uint32_t nextValue = tens * m_Dictionary[next] + current;
            tens *= 10;
            return nextValue;
        };

        return std::accumulate(outputArray.rbegin(), outputArray.rend(), std::uint32_t { 0 }, accumulateDigits);
    }

    NoteEntry::NoteEntry(const std::string& noteEntryRepresentation)
    {
        static const std::regex ENTRY_REGEX { R"(((?:[a-z]| )+) \| ((?:[a-z]| )+))" };
        std::smatch regexMatch;
        
        auto splitStringToArray = [](const std::string& str, auto& array)
        {
            auto splitView = str 
                | std::views::split(' ')
                // *sigh* https://stackoverflow.com/questions/48402558/how-to-split-a-stdstring-into-a-range-v3-of-stdstring-views
                | std::views::transform([](auto&& range) { return std::string_view(&*range.begin(), std::ranges::distance(range)); });
            
            std::ranges::copy(std::ranges::begin(splitView), std::ranges::end(splitView), std::begin(array));
        };

        if (std::regex_search(noteEntryRepresentation, regexMatch, ENTRY_REGEX))
        {
            splitStringToArray(regexMatch[1], m_UniquePatterns);
            splitStringToArray(regexMatch[2], m_Output);
        }
        else
        {
            assert(false && std::format("String '{}' doesn't match entry regex", noteEntryRepresentation).c_str());
        }

        auto sortArrayStrings = [](auto& array)
        {
            for (std::string& str : array) { std::sort(str.begin(), str.end()); }
        };

        sortArrayStrings(m_UniquePatterns);
        sortArrayStrings(m_Output);
    }

    void SevenSegmentSearchSolver::Init(std::string& inputFileName)
    {
        std::ifstream input { inputFileName };
        assert(input.is_open());

        for (std::string line; std::getline(input, line); )
        {
            m_Notes.emplace_back(line);
        }
    }

    std::uint32_t SevenSegmentSearchSolver::SolveProblemA() const
    {
        SizeToAmbiguityGroupMap ambiguityGroupMap = BuildAmbiguityGroupMap(DEFAULT_NUMBER_TO_INDICES);

        auto entryToOutputs = [](const NoteEntry& noteEntry) -> const OutputArray& { return noteEntry.m_Output; };
        auto isOutputUnambiguous = [&](const std::string& output) 
        {
            const std::size_t segmentsCount = output.size();
            return ambiguityGroupMap.at(segmentsCount).IsUnambiguous();
        };

        auto unambiguousOutputs = m_Notes | std::views::transform(entryToOutputs) | std::views::join | std::views::filter(isOutputUnambiguous);
        return std::ranges::distance(unambiguousOutputs);
    }

    std::uint32_t SevenSegmentSearchSolver::SolveProblemB() const
    {
        MappingDeductor deductor { DEFAULT_NUMBER_TO_INDICES };

        auto decodeNoteEntry = [&](const NoteEntry& entry)
        {
            SignalMapping mapping = deductor.DeduceMapping(entry.m_UniquePatterns);
            SignalDecoder decoder { DEFAULT_NUMBER_TO_INDICES, mapping };
            return decoder.DecodeOutput(entry.m_Output);
        };

        auto noteOutputsView = m_Notes | std::views::transform(decodeNoteEntry);
        return std::accumulate(noteOutputsView.begin(), noteOutputsView.end(), std::uint32_t { 0 });
    }
}