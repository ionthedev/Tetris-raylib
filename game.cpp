#include "game.h"
//
Game::Game()
{
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    GameOver = false;
    score = 0;
}

Block Game::GetRandomBlock()
{
    if(blocks.empty()|| BlockFits() == false)
    {
        blocks = GetAllBlocks();
    }
    int randomIndex;
    randomIndex = rand() % blocks.size();  // NOLINT(bugprone-narrowing-conversions)
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks()
{
    return {IBlock(), JBlock(),LBlock(),OBlock(),SBlock(),TBlock(),ZBlock()};
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw(11, 11);
    switch(nextBlock.id)
    {
    case 3:
        nextBlock.Draw(255, 290);
        break;
    case 4:
        nextBlock.Draw(255, 280);
        break;
    default:
        nextBlock.Draw(270, 270);
        break;
        
    }
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();
    if(GameOver && keyPressed != 0)
    {
        GameOver = false;
        Reset();
    }
    switch(keyPressed)
    {
    case KEY_LEFT:
        MoveBlockLeft();
        break;
    case KEY_RIGHT:
        MoveBlockRight();
        break;
    case KEY_DOWN:
        MoveBlockDown();
        UpdateScore(0, 1);
        break;
    case KEY_UP:
        RotateBlock();
        break;
    default:
        break;
    }
}

void Game::MoveBlockLeft()
{
    if(!GameOver)
    {
        currentBlock.Move(0, -1);
        if(IsBlockOutside() || BlockFits() == false)
        {
            MoveBlockRight();
        }
    }
}
void Game::MoveBlockRight()
{
    if(!GameOver)
    {
        currentBlock.Move(0, 1);
        if(IsBlockOutside() || BlockFits() == false)
        {
            MoveBlockLeft();
        }
    }
}
void Game::MoveBlockDown()
{
    if(!GameOver)
    {
        currentBlock.Move(1,0);
        if(IsBlockOutside() || BlockFits() == false)
        {
            MoveBlockUp();
            LockBlock();
        }
    }
    
}
void Game::MoveBlockUp()
{
    if(!GameOver)
    {
        currentBlock.Move(-1,0);
        if(IsBlockOutside())
        {
            MoveBlockDown();
        }
    }
}

bool Game::IsBlockOutside()
{
    std::vector<position> tiles = currentBlock.GetCellPositions();
    for(position item: tiles)
    {
        if(grid.IsCellOutside(item.row, item.column))
        {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock()
{
    currentBlock.Rotate();
    if(IsBlockOutside() || BlockFits() == false)
    {
        currentBlock.UndoRotation();
    }
}

void Game::LockBlock()
{
    std::vector<position> tiles = currentBlock.GetCellPositions();
    for(position item: tiles)
    {
        currentBlock.FlashWhite(item.row, item.column);
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if(BlockFits() == false)
    {
        GameOver = true;
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    UpdateScore(rowsCleared, 0);
}

bool Game::BlockFits()
{
    std::vector<position> tiles = currentBlock.GetCellPositions();
    for(position item: tiles)
    {
        if(grid.IsCellEmpty(item.row, item.column) == false)
        {
            return false;
        }
    }
    return true;
}

void Game::Reset()
{
    grid.Init();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

void Game::UpdateScore(int LinesCleared, int movedDownPoints)
{
    switch (LinesCleared)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 200;
        break;
    case 3:
        score += 300;
        break;
        default:
            break;
    }

    score += movedDownPoints;
}