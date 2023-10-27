#pragma once
#include "blocks.cpp"
#include "grid.h"
//
class Game
{
public:
    Game();
    
    void Draw();
    void HandleInput();
    void MoveBlockDown();
    void MoveBlockUp();
    bool GameOver;
    int score;

private:
    
    Grid grid;
    Block GetRandomBlock();
    void MoveBlockLeft();
    void MoveBlockRight();
    std::vector<Block> GetAllBlocks();
    bool IsBlockOutside();
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    void RotateBlock();
    void LockBlock();
    bool BlockFits();
    void Reset();
    void UpdateScore(int LinesCleared, int movedDownPoints);
};
