#pragma once
#include <raylib.h>
#include <vector>
//
class Grid
{
public:
    Grid(); //Defines Grid
    void Init(); //Initialize Function
    void Print(); //Print Debug Function
    void Draw (); // Draws things onto the screen
    bool IsCellOutside(int row, int column);
    bool IsCellEmpty(int row, int column);
    int grid[20][10];
    int ClearFullRows();
private:
    int numRows;
    int numColumns;
    int cellSize;
    std::vector<Color> colors;
    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowDown(int row, int numRows);
};