// Defines Langton's Ant behavior and movement logic
#pragma once
#include <vector>

class LangtonsAnt
{
public:
    // Constructor: sets the ant's starting position on the grid
    LangtonsAnt(int startRow, int startCol);

    // Runs one step of the simulation: moves the ant and flips the cell color
    void Step(std::vector<std::vector<bool>>& grid);

private:
    int row, col;  // Current position of the ant on the grid

    // Directions the ant can face and move
    enum Direction { UP, RIGHT, DOWN, LEFT } dir;

    void TurnRight();     // Turn ant 90 degrees right
    void TurnLeft();      // Turn ant 90 degrees left
    void MoveForward(int gridSize);  // Move ant forward one cell, respecting grid boundaries
};
