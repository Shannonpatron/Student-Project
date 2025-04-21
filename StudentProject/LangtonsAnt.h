// Defines the Langton's Ant class with logic for movement and direction
#pragma once
#include <vector>

class LangtonsAnt
{
public:
    LangtonsAnt(int startRow, int startCol); // construct to set initial position

    void Step(std::vector<std::vector<bool>>& grid); // step through one iteration of Langton's ant

private:
    int row, col; // Ant's current position
    enum Direction { UP, RIGHT, DOWN, LEFT } dir; // Possible movement directions for the ant

    void TurnRight(); // Turn the ant to the right
    void TurnLeft(); // Turn the ant to the left
    void MoveForward(int gridSize); // Move the ant one step forward
};