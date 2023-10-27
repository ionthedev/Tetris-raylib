#include <iostream>
#include <raylib.h>
#include "game.h"
//

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

using namespace std;

int main()
{
    Color darkBlue = {44,44,128,255};
    InitWindow(500, 620, "Tetris");
    SetTargetFPS(60);

    Font font = LoadFontEx("Font/Nonchalance_Regular.otf", 64, 0, 0);

    Game game = Game();
    
    while(WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(darkBlue);
        DrawTextEx(font, "Score", {365, 15}, 24, 2, WHITE);
        DrawTextEx(font, "Next", {370, 175}, 24, 2, WHITE);
        if(game.GameOver)
        {
            DrawTextEx(font, "GAME OVER", {320, 450}, 24, 2, WHITE);
        }
        DrawRectangleRounded({320, 55, 170, 60}, 0.3f, 6, cyan);

        char scoreText[10];
        sprintf_s(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 24, 2);
        
        DrawTextEx(font, scoreText, {320+ (170 - textSize.x)/2, 65}, 24, 2, WHITE);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3f, 6, cyan);
        
        game.Draw();
        game.HandleInput();
        if(EventTriggered(0.2f))
        {
            game.MoveBlockDown();
        }
        DrawFPS(10,10);
        EndDrawing();
        
    }

    CloseWindow();
}