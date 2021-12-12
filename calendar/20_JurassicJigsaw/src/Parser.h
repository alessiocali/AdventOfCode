#pragma once
#include <Problem.h>

#include <optional>

namespace JurassicJigsaw
{
    class Parser final
    {
    public:
        void ParseNextLine(const std::string& line);
        Problem Finalize();

    private:
        struct State
        {
            bool IsValid() const;
            void Initialize(const TileID tileID);
            void Reset();
            void AppendLine(const std::string& line);

            ImageData m_TileData { };
            std::size_t m_Idx { 0 };
            std::optional<TileID> m_ID { };
        };

        void ConsumeState();

        State m_State;
        Problem m_Problem;
    };
}