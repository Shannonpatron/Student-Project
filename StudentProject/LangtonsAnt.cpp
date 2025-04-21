// Implements the Langton's Ant class logic
#include "LangtonsAnt.h"

LangtonsAnt::LangtonsAnt(int startRow, int startCol)
    : row(startRow), col(startCol), dir(UP) {} // initialize the ant at the specified position

void LangtonsAnt::Step(std::vector<std::vector<bool>>& grid)
{
    // Directly access the grid element at [row][col] instead of using a reference
    bool cell = grid[row][col]; // Get the current cell's state (true = black, false = white)

    if (cell) // if the cell is black
    {
        TurnLeft(); // turn left
        grid[row][col] = false;  // Set the cell to false (white) // flip the cell to white
    }
    else // if the cell is white
    {
        TurnRight(); // turn right
        grid[row][col] = true;   // flip the cell to black
    }

    MoveForward(grid.size()); // move the ant one step forward
}

void LangtonsAnt::TurnRight()
{
    dir = static_cast<Direction>((dir + 1) % 4); // turn the ant 90 degrees to the right
}

void LangtonsAnt::TurnLeft()
{
    dir = static_cast<Direction>((dir + 3) % 4); // turn the ant 90 degress to the left
}

void LangtonsAnt::MoveForward(int gridSize)
{
    switch (dir)
    {
    case UP:    row = (row - 1 + gridSize) % gridSize; break; // move up, wrapping around
    case DOWN:  row = (row + 1) % gridSize; break; // move down, wrapping around
    case LEFT:  col = (col - 1 + gridSize) % gridSize; break; // move left, wrapping around
    case RIGHT: col = (col + 1) % gridSize; break; // move right, wrapping around
    }
}