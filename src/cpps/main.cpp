#include "raylib.h"
#include"iostream"
#include"math.h"
#include"raymath.h"

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

void CustomLine(Vector2 from, Vector2 to, float thickness, Color color)
{
    float distance = Vector2Distance(from, to);
    Vector2 direction = Vector2Normalize(Vector2Subtract(to, from));
    
    for(int x = 0; x < distance; x++)
    {
        DrawPixel(from.x + x * direction.x, from.y + from.y * direction.y, color);
    }
}

struct ScreenInfo
{
    Vector2 size;
    Vector2 center;
    Vector2 centeroffset;
    float ratio;
    Color color;
};

ScreenInfo GetScreenInfo(Color screenColor)
{
    float x = GetScreenWidth();
    float y = GetScreenHeight();

    ScreenInfo info;
    info.size = Vector2{x, y};
    info.center = Vector2{x/2, y/2};
    info.ratio = x / y;
    info.color = screenColor;

    return info;
}

void StrechLine(Vector2 direction, Vector2 startPos, float thickness, Color color)
{
    
}

float GetHypotenuse(float x, float y)
{
    return sqrt(x*x + y*y);
}


void GenerateGrid(Vector2 startPos, Vector2 direction, Vector2 offset, ScreenInfo* screenInfo)
{
    direction = Vector2Normalize(direction);

    float lineThickness = 0;
    float lineSpacing = 80;

    Color lineColor = Color{240, 240, 240, 80};

    float sizeX = screenInfo->size.x;
    float sizeY = screenInfo->size.y;
    float screenRatio = screenInfo->ratio;
    float center_x = screenInfo->center.x;
    float center_y = screenInfo->center.y;

    Vector2 stretchDirection = Vector2{-direction.x, direction.y}; // Orthogonal to moveDirection
    

    Vector2 from;
    Vector2 to;

    

    from = Vector2{startPos.x - stretchDirection.x * 5000, startPos.y - stretchDirection.y * 5000};
    to = Vector2{startPos.x + stretchDirection.x * 50000, startPos.y + stretchDirection.y * 50000};
    
    
    DrawLineV(from, to, lineColor);
    
    
    for(int i = 1; i < center_y/lineSpacing; i++)
    {

        from = Vector2{startPos.x - stretchDirection.x * 5000, startPos.y - stretchDirection.y * 5000 + lineSpacing*i};
        to = Vector2{startPos.x + stretchDirection.x * 50000, startPos.y + stretchDirection.y * 50000 + lineSpacing*i};
        DrawLineV(from, to, lineColor);


        from = Vector2{startPos.x - stretchDirection.x * 5000, startPos.y - stretchDirection.y * 5000 - lineSpacing*i};
        to = Vector2{startPos.x + stretchDirection.x * 50000, startPos.y + stretchDirection.y * 50000 - lineSpacing*i};
        DrawLineV(from, to, lineColor);
    }
}

struct Pensel
{
    int arraySize = 8000;
    Vector2 points[8000];
    int lastAddedIndex = 0;
};

void DrawForFun(Pensel *p)
{

    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Vector2 point = GetMousePosition();

        
       
        if(p->lastAddedIndex == p->arraySize-1)
        {
            p->lastAddedIndex = 0;
        }

        p->points[p->lastAddedIndex] = point;

        p->lastAddedIndex++;
    }
    else if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
         if(p->lastAddedIndex == p->arraySize-1)
        {
            p->lastAddedIndex = 0;
        }

        p->points[p->lastAddedIndex] = Vector2Zero();

        p->lastAddedIndex++;
    }


    for(int i = 1; i < p->arraySize; i++)
    {
        Vector2 from = p->points[i-1];
        Vector2 to = p->points[i];
        if(from == Vector2Zero() || to == Vector2Zero())continue;
        DrawLineEx(from, to, 2.0f, WHITE);
        // CustomLine(from, to, 2.0f, WHITE,)
    }

    

    
}


int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 450, "Graficus");
    
    int segments = 300;
    float increment = 0.01;
    
    
    Color screenColor = Color{18, 18, 18, 255};

    int drawForFun_Indexer = 0;
    Vector2 drawForFun_points[800];

    Pensel pensel;
    
    float angle = PI;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();

            ScreenInfo screenInfo = GetScreenInfo(screenColor);

            ClearBackground(screenInfo.color);
            
            if(IsKeyDown(KEY_V))
            {
                angle-= 0.01f;
            }
            
            GenerateGrid(screenInfo.center, Vector2{cos(angle), sin(angle)}, Vector2Zero(), &screenInfo);

            DrawForFun(&pensel);
            
            
        EndDrawing();
    }



    CloseWindow();

    return 0;
}