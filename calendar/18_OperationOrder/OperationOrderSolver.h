#pragma once

#include <ProblemSolver.h>

#include <stack>
#include <vector>

class OperationOrderSolver : public ProblemSolver<std::string, std::int64_t, std::int64_t>
{
public:
    void Init(std::string& input) override;
    std::int64_t SolveProblemA() const override;
    std::int64_t SolveProblemB() const override;

private:
    enum class OperatorPriority : std::uint8_t
    {
        Add = 0,
        Mul = 1,
        MAX = 2
    };

    struct Operator
    {
        virtual std::int64_t Apply(std::int64_t lh, std::int64_t rh) const = 0;
        virtual OperatorPriority GetPriority() const = 0;
    };

    struct Add : public Operator
    {
        virtual std::int64_t Apply(std::int64_t lh, std::int64_t rh) const override { return lh + rh; }
        OperatorPriority GetPriority() const override { return OperatorPriority::Add; }
    };

    struct Multiply : public Operator
    {
        virtual std::int64_t Apply(std::int64_t lh, std::int64_t rh) const override { return lh * rh; }
        OperatorPriority GetPriority() const override { return OperatorPriority::Mul; }
    };

    using OperandStack = std::stack<std::int64_t>;
    using OperatorStack = std::stack< std::unique_ptr<Operator> >;

    struct ParsingContext
    {
        std::vector<std::int64_t> m_Operands;
        std::vector< std::unique_ptr<Operator> > m_Operators;
    };

    using Expression = std::string;
    using Problem = std::vector<Expression>;

    Problem m_Problem;

    std::int64_t EvaluateA(const Expression& expression) const;
    std::int64_t EvaluateB(const Expression& expression) const;

    std::int64_t CollapseContext(ParsingContext& context) const;
};