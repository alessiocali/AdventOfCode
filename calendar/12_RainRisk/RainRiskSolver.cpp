#include "RainRiskSolver.h"

#include <fstream>
#include <regex>
#include <cassert>
#include <unordered_map>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <MathHelpers.h>
#include <SimpleControllableView.h>

void RainRiskSolver::Init(std::string& input)
{
    static const std::regex INPUT_REGEX { R"((N|S|W|E|R|L|F)(\d+))" };
    static const std::unordered_map<char, sf::Vector2i> DIRECTION_MAPPING =
    {
        { 'N', {  0,  1 } },
        { 'S', {  0, -1 } },
        { 'E', {  1,  0 } },
        { 'W', { -1,  0 } }
    };

    std::smatch inputMatch;
    std::ifstream inputStream(input);
    std::string temp;

    assert(inputStream.is_open());
    while (std::getline(inputStream, temp))
    {
        if (std::regex_match(temp, inputMatch, INPUT_REGEX))
        {
            Instruction& instruction = m_Problem.emplace_back();
            instruction.m_Value = std::stoi(inputMatch[2]);

            std::string instructionString = inputMatch[1];
            if (std::regex_match(instructionString, std::regex(R"(N|S|W|E)")))
            {
                instruction.m_Type = InstructionType::MoveCardinal;
                instruction.m_Direction = DIRECTION_MAPPING.at(instructionString[0]);
            }
            else if (std::regex_match(instructionString, std::regex(R"(L|R)")))
            {
                instruction.m_Type = InstructionType::Rotate;
                if (instructionString == "R")
                {
                    instruction.m_Value *= -1;
                }
            }
            else
            {
                assert(instructionString == "F");
                instruction.m_Type = InstructionType::Forward;
            }
        }
        else
        {
            assert(false && "Input doesn't match regex");
        }
    }
}

std::uint32_t RainRiskSolver::SolveProblemA() const
{
    struct PreviousData
    {
        sf::Vector2i m_Position;
        sf::Vector2i m_Direction;
    };

    std::vector<PreviousData> previousData;
    previousData.reserve(m_Problem.size());

    sf::Vector2i currentPosition    { 0, 0 };
    sf::Vector2i currentDirection   { 0, 1 };

    auto display = [&previousData](sf::RenderWindow& window)
    {
        constexpr const float LINE_WIDTH = 0.025f;

        sf::CircleShape baseTriangle { 0.025f, 3 }; // Yes a triangle is a circle with 3 vertices. Don't ask.
        baseTriangle.setFillColor(sf::Color::Red);

        sf::RectangleShape baseRect { };
        baseRect.setFillColor(sf::Color::Black);

        sf::Vertex baseLine[2];

        const sf::Vector2i* previousPosition { nullptr };
        for (const auto& toDraw : previousData)
        {
            baseTriangle.setRotation(-90.f + RadiansToDegrees(std::atan2f(toDraw.m_Direction.y, toDraw.m_Direction.x)) );
            baseTriangle.setPosition(toDraw.m_Position.x, toDraw.m_Position.y);
            window.draw(baseTriangle);

            if (previousPosition != nullptr)
            {
                baseLine[0] = sf::Vector2f { *previousPosition };
                baseLine[0].color = sf::Color::Black;
                baseLine[1] = sf::Vector2f { toDraw.m_Position };
                baseLine[1].color = sf::Color::Black;
                window.draw(baseLine, 2, sf::Lines );
            }

            previousPosition = &toDraw.m_Position;
        }
    };

    static const std::vector<sf::Vector2i> ROTATION_SEQUENCE { { 0, 1 }, { 1, 0 }, { -1, 0 }, { 0, -1} };

    int rotationIdx { 0 };
    std::size_t idx { 0 };
    auto update = [&](sf::RenderWindow& window)
    {
        previousData.emplace_back(PreviousData { currentPosition, currentDirection });

        const auto& instruction = m_Problem[idx++];
        switch (instruction.m_Type)
        {
        case InstructionType::MoveCardinal:
            currentPosition += instruction.m_Value * instruction.m_Direction;
            break;
        case InstructionType::Rotate:
            rotationIdx += instruction.m_Value / 90;
            rotationIdx = rotationIdx % 4;
            if (rotationIdx < 0) { assert(rotationIdx > -4); rotationIdx = 4 + rotationIdx; }
            currentDirection = ROTATION_SEQUENCE[rotationIdx];
            break;
        case InstructionType::Forward:
            currentPosition += instruction.m_Value * currentDirection;
            break;
        }
    };

    auto isClosed = [&idx, this]() { return idx >= m_Problem.size(); };

    SimpleControllableView debugView { sf::VideoMode { 1280, 720 }, "Seating System", 0, SimpleControllableView::SpeedParameters { 0.1f, 2.f } };

    if (IsDebugging())
    {
        debugView.RunUntilClosed(display, update, isClosed);
    }
    else
    {
        sf::RenderWindow dummy { };
        while (!isClosed()) { update(dummy); }
    }

    return std::abs(currentPosition.x) + std::abs(currentPosition.y);
}

std::uint32_t RainRiskSolver::SolveProblemB() const
{
    return 0;
}
