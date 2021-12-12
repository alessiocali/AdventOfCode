#include <Parser.h>

#include <cassert>
#include <regex>

namespace JurassicJigsaw
{
    void Parser::ParseNextLine(const std::string& line)
    {
        std::smatch match;
        if (line.empty())
        {
            ConsumeState();
        }
        else if (std::regex_search(line, match, std::regex { R"(\d+)" }))
        {
            m_State.Initialize(std::stoi(match[0]));
        }
        else
        {
            m_State.AppendLine(line);
        }
    }

    Problem Parser::Finalize()
    {
        if (m_State.IsValid())
        {
            ConsumeState();
        }

        return m_Problem;
    }

    void Parser::ConsumeState()
    {
        m_Problem.AddTile(*m_State.m_ID, m_State.m_TileData);
        m_State.Reset();
    }

    bool Parser::State::IsValid() const
    {
        return m_ID.has_value();
    }

    void Parser::State::Initialize(const TileID tileID)
    {
        assert(!m_ID.has_value());
        m_ID = tileID;
    }

    void Parser::State::Reset()
    {
        m_ID.reset();
        m_TileData.clear();
        m_Idx = 0;
    }

    void Parser::State::AppendLine(const std::string& line)
    {
        m_TileData.emplace_back(line);
    }
}