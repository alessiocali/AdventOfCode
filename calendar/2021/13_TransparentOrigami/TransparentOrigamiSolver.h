#pragma once

#include <CommonHelpers.h>
#include <ProblemSolver.h>

#include <functional>
#include <memory>
#include <ranges>
#include <unordered_set>
#include <vector>

#include <range/v3/all.hpp>

namespace aoc2021::TransparentOrigami
{
    using HoledSheet = std::unordered_set<Position>;

    template<typename Filter>
    concept FoldFilter = requires (Filter f, Position p)
    {
        { f(p) } -> std::convertible_to<bool>;
    };

    template<typename Function>
    concept FoldFunction = requires(Function f, Position p)
    {
        { f(p) } -> std::convertible_to<Position>;
    };

    HoledSheet FilterAndTransform(const HoledSheet& sheet, FoldFilter auto foldFilter, FoldFunction auto foldFunction)
    {
        auto holesKept = sheet | std::views::filter(foldFilter);
        auto flippedHoles = sheet | std::views::filter(std::not_fn(foldFilter)) | std::views::transform(foldFunction);
        auto allHoles = ranges::view::concat(holesKept, flippedHoles);

        HoledSheet foldedSheet { std::begin(allHoles), std::end(allHoles) };
        return foldedSheet;
    }

    std::string MakePrintable(const HoledSheet& sheet);

    class IFoldInstruction
    {
    public:
        virtual ~IFoldInstruction() = default;
        virtual HoledSheet ApplyTo(const HoledSheet& sheet) const = 0;
    };

    class FoldUp final : public IFoldInstruction
    {
    public:
        FoldUp(const int y);
        HoledSheet ApplyTo(const HoledSheet& sheet) const override;

    private:
        int m_Y { 0 };
    };

    class FoldLeft final : public IFoldInstruction
    {
    public:
        FoldLeft(const int x);
        HoledSheet ApplyTo(const HoledSheet& sheet) const override;

    private:
        int m_X { 0 };
    };

    using Instructions = std::vector<std::unique_ptr<IFoldInstruction>>;

    class TransparentOrigamiSolver : public ProblemSolver<std::string, std::uint32_t, std::string>
    {
    public:
        void Init(std::string& input) override;
        std::uint32_t SolveProblemA() const override;
        std::string SolveProblemB() const override;

    private:
        HoledSheet m_InitialSheet;
        Instructions m_Instructions;
    };
}