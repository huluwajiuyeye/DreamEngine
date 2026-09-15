#pragma once
#include "FrameBuffer.h"
#include "../../Core/Math/Vector2D.h"
#include "../RenderCore/RenderBase.h"

class RenderSoftWare: public RenderBase
{
public:
    void Init() override;
    void Draw() override;
    
    // 画线
    void DrawLine(Vector2D start, Vector2D end,SColor color);
    // DDA 画线法，相当于以最小像素点为单位，取长边一步一步迭代，四舍五入取对应点。
    void DrawLineDDA(Vector2D start, Vector2D end, SColor color);
    void DrawLineBresenham(Vector2D start, Vector2D end, SColor color);

    // 画三角形
    void DrawTriangle(Vector2D A, Vector2D B, Vector2D C);

    void Present();

private:
    FrameBuffer frame_buffer;
};
