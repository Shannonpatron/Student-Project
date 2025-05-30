// Implements the ant's movement and turning logic
#include "LangtonsAnt.h"

LangtonsAnt::LangtonsAnt(int startRow, int startCol)
    : row(startRow), col(startCol), dir(UP)
{
    // Initialize the ant at the starting position, facing UP by default
}

void LangtonsAnt::Step(std::vector<std::vector<bool>>& grid)
{
    // Check the current cell color: true means black, false means white
    bool cell = grid[row][col];

    if (cell) // If on a black cell
    {
        TurnLeft();          // Turn left 90 degrees
        grid[row][col] = false; // Flip the cell to white
    }
    else // If on a white cell
    {
        TurnRight();         // Turn right 90 degrees
        grid[row][col] = true;  // Flip the cell to black
    }

    // Move forward one step in the current direction, wrapping around edges
    MoveForward(grid.size());
}

void LangtonsAnt::TurnRight()
{
    // Change direction clockwise (UP->RIGHT->DOWN->LEFT->UP)
    dir = static_cast<Direction>((dir + 1) % 4);
}

void LangtonsAnt::TurnLeft()
{
    // Change direction counter-clockwise
    // Adding 3 modulo 4 is same as -1 modulo 4
    dir = static_cast<Direction>((dir + 3) % 4);
}

void LangtonsAnt::MoveForward(int gridSize)
{
    // Move the ant one cell forward based on current direction
    // Uses modulo for wrap-around (toroidal grid)
    switch (dir)
    {
    case UP:
        row = (row - 1 + gridSize) % gridSize;
        break;
    case DOWN:
        row = (row + 1) % gridSize;
        break;
    case LEFT:
        col = (col - 1 + gridSize) % gridSize;
        break;
    case RIGHT:
        col = (col + 1) % gridSize;
        break;
    }
}