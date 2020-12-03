#include "TobogganTrajectorySolver.h"

#include <string>
#include <fstream>

void TobogganTrajectorySolver::Init(std::string& input)
{
    m_Problem.clear();

    std::ifstream inputStream(input);
    std::string temp;
    while (std::getline(inputStream, temp))
    {
        auto& line = m_Problem.emplace_back();
        for (const char c : temp)
        {
            line.push_back(c == '#' ? Tile::Tree : Tile::Space);
        }
    }

    m_Width = m_Problem[0].size();
    m_Height = m_Problem.size();
}

std::size_t TobogganTrajectorySolver::SolveProblemA() const
{
    auto treeCount = Traverse(3, 1);
    return treeCount;
}

std::size_t TobogganTrajectorySolver::SolveProblemB() const
{
    return  Traverse(1, 1) *
            Traverse(3, 1) *
            Traverse(5, 1) *
            Traverse(7, 1) *
            Traverse(1, 2);
}

std::size_t TobogganTrajectorySolver::Traverse(std::size_t right, std::size_t down) const
{
    std::size_t trees { 0 };
    std::size_t spaces { 0 };

    std::size_t row { 0 };
    std::size_t col { 0 };
    while (row + down < m_Height)
    {
        row = row + down;
        col = (col + right) % m_Width;
        Tile currentTile = m_Problem[row][col];

        if (currentTile == Tile::Tree) 
        {
            trees++;
        }
    }

    return trees;
}

