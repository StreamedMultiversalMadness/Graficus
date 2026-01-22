#include "raylib.h"
#include"iostream"
#include"math.h"

float TheFunction(float x)
{
    return x*x;
}

float RiemannSum()
{
    float sum = 0;
    float increment = 0.00001f;
    float previousX = 0;

    float interval[] = {0, PI};

    for (float x = interval[0]; x < interval[1]; x += increment)
    {
        float deltaX = (x-previousX);
        sum += sin(x) * deltaX;
        previousX = x;
    }

    return sum;
}

int main(void)
{
    // InitWindow(800, 450, "raylib [core] example - basic window");
    // int segments = 300;
    // float increment = 0.01;
    // float lineThickness = 0.5;
    // Color lineColor = WHITE;


    // while (!WindowShouldClose())
    // {
    //     BeginDrawing();
    //         ClearBackground(DARKGRAY);
    //         for(float x = 0; x < segments; x+=increment)
    //         {
                
    //             Vector2 startPos = {x, TheFunction(x) - GetScreenHeight()};
    //             Vector2 endPos = {x+increment, TheFunction(x+increment) - GetScreenHeight()};
    //             DrawLineEx(startPos, endPos, lineThickness, lineColor);
    //         }
            
    //     EndDrawing();
    // }



    // CloseWindow();

    return 0;
}