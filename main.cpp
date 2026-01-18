#include<raylib.h>

float TheFunction(float x)
{
    return x*x;
}

int main(void)
{
    InitWindow(800, 450, "raylib [core] example - basic window");
    int segments = 300;
    float increment = 0.01;
    float lineThickness = 0.5;
    Color lineColor = WHITE;


    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(DARKGRAY);
            for(float x = 0; x < segments; x+=increment)
            {
                
                Vector2 startPos = {x, TheFunction(x) - GetScreenHeight()};
                Vector2 endPos = {x+increment, TheFunction(x+increment) - GetScreenHeight()};
                DrawLineEx(startPos, endPos, lineThickness, lineColor);
            }
            
        EndDrawing();
    }

    CloseWindow();

    return 0;
}