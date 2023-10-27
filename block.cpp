#include "block.h"
//
Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    columnOffset = 0;
}

void Block::Draw(int offsetX, int offsetY)
{
    std::vector<position> tiles = GetCellPositions();
    for (position item: tiles)
    {
        DrawRectangle(item.column * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
    }
}

void Block::Move(int rows, int columns)
{
    rowOffset += rows;
    columnOffset += columns;
}

std::vector<position> Block::GetCellPositions()
{
    std::vector<position> tiles = cells[rotationState];
    std::vector<position> movedTiles;
    for(position item: tiles)
    {
        position newPos = position(item.row + rowOffset, item.column + columnOffset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}

void Block::Rotate()
{
    rotationState ++;
    if(rotationState == cells.size())
    {
        rotationState = 0;
    }
}

void Block::UndoRotation()
{
    rotationState --;
    if(rotationState == -1)
    {
        rotationState = cells.size() - 1;  // NOLINT(bugprone-narrowing-conversions)
    }
}

void Block::FlashWhite(int offsetX, int offsetY)
{
    std::vector<position> tiles = GetCellPositions();
    for (position item: tiles)
    {
        DrawRectangle(item.column * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1,WHITE);
    }
    WaitTime(0.1);
}
