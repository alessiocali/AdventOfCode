#include "OperationOrderSolver.h"

#include <fstream>
#include <string>
#include <cassert>
#include <optional>
#include <regex>

void OperationOrderSolver::Init(std::string& input)
{
    std::ifstream inputStream(input);
    assert(inputStream.is_open());
    for (std::string line; std::getline(inputStream, line); )
    {
        m_Problem.emplace_back(std::move(line));
    }
}

std::int64_t OperationOrderSolver::SolveProblemA() const
{
    std::int64_t result { 0 };
    for (const Expression& expression : m_Problem)
    {
        result += EvaluateA(expression);
    }
    return result;
}

std::int64_t OperationOrderSolver::SolveProblemB() const
{
    std::int64_t result { 0 };
    for (const Expression& expression : m_Problem)
    {
        result += EvaluateB(expression);
    }
    return result;
}

std::int64_t OperationOrderSolver::EvaluateA(const Expression& expression) const
{
    OperandStack operandStack;
    OperatorStack operatorStack;

    std::optional<std::int64_t> currentOperand { };
    for (const auto c : expression)
    {
        if (c == ' ') { continue; }
        else if (c == '*') { operatorStack.push(std::make_unique<Multiply>()); }
        else if (c == '+') { operatorStack.push(std::make_unique<Add>()); }
        else if (c == '(')
        {
            if (currentOperand.has_value()) 
            { 
                operandStack.push(*currentOperand); 
                currentOperand.reset(); 
            }
            else
            {
                // Add null-opt to preserve stack operations
                operandStack.push(0);
                operatorStack.push(std::make_unique<Add>());
            }
        }
        else if (c == ')')
        {
            assert(currentOperand.has_value());
            if (operandStack.size() > 0)
            {
                assert(operatorStack.size() > 0);
                currentOperand = operatorStack.top()->Apply(operandStack.top(), *currentOperand);
                operatorStack.pop();
                operandStack.pop();
            }
        }
        else
        {
            // Must be digit at this point
            assert(c >= '0' && c <= '9');

            if (currentOperand.has_value())
            {
                assert(operatorStack.size() > 0);
                currentOperand = operatorStack.top()->Apply(*currentOperand, c - '0');
                operatorStack.pop();
            }
            else
            {
                currentOperand = c - '0';
            }
        }
    }

    assert(currentOperand.has_value());
    return *currentOperand;
}

std::int64_t OperationOrderSolver::EvaluateB(const Expression& expression) const
{
    std::stack<ParsingContext> contexts { };
    ParsingContext* currentContext { nullptr };

    currentContext = &contexts.emplace();
    for (const auto c : expression)
    {
        if (c == ' ') { continue; }
        else if (c == '*') { currentContext->m_Operators.emplace_back(std::make_unique<Multiply>()); }
        else if (c == '+') { currentContext->m_Operators.emplace_back(std::make_unique<Add>()); }
        else if (c == '(') { currentContext = &contexts.emplace(); }
        else if (c == ')')
        {
            std::int64_t contextVal = CollapseContext(*currentContext);
            contexts.pop();
            currentContext = &contexts.top();
            currentContext->m_Operands.emplace_back(contextVal);
        }
        else
        {
            // Must be digit at this point
            assert(c >= '0' && c <= '9');
            currentContext->m_Operands.emplace_back(c - '0');
        }
    }

    assert(contexts.size() == 1);
    return CollapseContext(*currentContext);
}

std::int64_t OperationOrderSolver::CollapseContext(ParsingContext& context) const
{
    assert(context.m_Operands.size() == context.m_Operators.size() + 1);

    for (std::uint8_t priorityVal = 0; priorityVal < static_cast<std::uint8_t>(OperatorPriority::MAX); priorityVal++)
    {
        OperatorPriority priority = static_cast<OperatorPriority>(priorityVal);
        for (std::size_t i = 0; i < context.m_Operators.size(); )
        {
            if (context.m_Operators[i]->GetPriority() != priority) 
            { 
                i++;
                continue; 
            }

            context.m_Operands[i] = context.m_Operators[i]->Apply(context.m_Operands[i], context.m_Operands[i + 1]);
            context.m_Operands.erase(context.m_Operands.begin() + i + 1);
            context.m_Operators.erase(context.m_Operators.begin() + i);
        }
    }

    assert(context.m_Operands.size() == 1);
    return context.m_Operands[0];
}