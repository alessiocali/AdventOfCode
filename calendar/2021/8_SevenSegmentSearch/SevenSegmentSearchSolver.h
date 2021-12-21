#pragma once

#include <ProblemSolver.h>

#include <array>
#include <unordered_map>
#include <vector>

namespace aoc2021::SevenSegmentSearch
{
    // Assume the following indexing:
    //   0
    // 1   2
    //   3
    // 4   5
    //   6
    using NumberToIndicesMapping = std::vector<std::vector<std::size_t>>;

    using PatternArray = std::array<std::string, 10>;
    using OutputArray = std::array<std::string, 4>;

    using PatternAmbiguityGroup = std::vector<std::string>;
    using SizeToPatternAmbiguityMap = std::unordered_map<std::size_t, PatternAmbiguityGroup>;

    using SignalMapping = std::string; // In the form that mapping[i] = a|b|c...
    using SignalDictionary = std::unordered_map<std::string, std::uint32_t>;
    using PotentialSymbolsPerSegment = std::array<std::string, 7>;

    static const NumberToIndicesMapping DEFAULT_NUMBER_TO_INDICES
    {
        { 0, 1, 2, 4, 5, 6 },       // 0
        { 2, 5 },                   // 1
        { 0, 2, 3, 4, 6 },          // 2
        { 0, 2, 3, 5, 6 },          // 3
        { 1, 2, 3, 5 },             // 4
        { 0, 1, 3, 5, 6 },          // 5
        { 0, 1, 3, 4, 5, 6 },       // 6
        { 0, 2, 5 },                // 7
        { 0, 1, 2, 3, 4, 5, 6 },    // 8
        { 0, 1, 2, 3, 5, 6 }        // 9
    };

    std::string GetPatternIntersection(const std::string& pattern1, const std::string& pattern2);
    SizeToPatternAmbiguityMap BuildPatternAmbiguityMap(const PatternArray& patternArray);

    struct AmbiguityGroup
    {
        inline bool IsUnambiguous() const { return m_PotentialNumbers.size() == 1; }

        void RecomputeCommonSegmentIndices(const NumberToIndicesMapping& indexMapping);

        std::vector<std::size_t> m_PotentialNumbers;
        std::vector<std::size_t> m_CommonSegmentIndices;
    };

    using SizeToAmbiguityGroupMap = std::unordered_map<std::size_t, AmbiguityGroup>;
    SizeToAmbiguityGroupMap BuildAmbiguityGroupMap(const NumberToIndicesMapping& mapping);

    class MappingDeductor final
    {
    public:
        MappingDeductor(const NumberToIndicesMapping& mapping);
        SignalMapping DeduceMapping(const PatternArray& patterns) const;

    private:
        NumberToIndicesMapping m_NumberToIndices;
        SizeToAmbiguityGroupMap m_AmbiguityGroups;

        PotentialSymbolsPerSegment InitPotentialSymbolsPerSegment() const;
        void DeducePotentialSymbolsFromAmbiguityMap(const SizeToPatternAmbiguityMap& patternAmbiguityMap, PotentialSymbolsPerSegment& potentialSymbolsPerSegment) const;
        void EliminateConflictingSymbols(PotentialSymbolsPerSegment& potentialSymbolsPerSegment) const;
        SignalMapping ConvertToSignalMapping(const PotentialSymbolsPerSegment& potentialSymbolsPerSegment) const;
    };

    class SignalDecoder
    {
    public:
        SignalDecoder(const NumberToIndicesMapping& numberMapping, const SignalMapping& signalMapping);
        std::uint32_t DecodeOutput(const OutputArray& outputArray);

    private:
        SignalMapping m_Mapping;
        SignalDictionary m_Dictionary;
    };

    struct NoteEntry
    {
        NoteEntry(const std::string& noteEntryRepresentation);

        PatternArray m_UniquePatterns;
        OutputArray m_Output;
    };

    using Notes = std::vector<NoteEntry>;

    class SevenSegmentSearchSolver : public ProblemSolver<std::string, std::uint32_t, std::uint32_t>
    {
    public:
        void Init(std::string& input) override;
        std::uint32_t SolveProblemA() const override;
        std::uint32_t SolveProblemB() const override;

    private:
        Notes m_Notes;
    };
}