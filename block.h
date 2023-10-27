#pragma once
//
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"


class Block
{
public:
    Block();
    void Draw(int offsetX, int offsetY); //Draws block
    int id; //Unique Identifier of each block
    std::map<int, std::vector<position>> cells;
    void Move(int rows, int columns);
    std::vector<position> GetCellPositions();
    void Rotate();
    void UndoRotation();
    void FlashWhite(int offsetX, int offsetY);

private:
    int cellSize;
    int rotationState;
    std::vector<Color> colors;
    int rowOffset;
    int columnOffset;
};