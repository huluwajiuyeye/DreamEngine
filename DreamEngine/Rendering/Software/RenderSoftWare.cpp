#include "RenderSoftWare.h"

#include "../../Core/Color/SColor.h"
#include "../../Core/Image/ImageUtil.h"

// CPU版软光栅器

void RenderSoftWare::Init()
{
    frame_buffer = FrameBuffer(Width,Height);
}

void RenderSoftWare::Draw()
{
    
    // 清屏幕
    frame_buffer.Clear(SColor::Black());
    
    // 画一个线
    DrawLine(Vector2D(0,0),Vector2D(100,100),SColor::White());

    //把 Framebuffer 展示到窗口
    Present(); 
    
    // // 画一个三角形
    // DrawTriangle(Vector2D(0,0),Vector2D(100,100),Vector2D(100,0));
    //
    // // 画一个小房子
    // DrawTriangle(Vector2D(0,0),Vector2D(0,100),Vector2D(100,0));
    // DrawTriangle(Vector2D(0,100),Vector2D(100,100),Vector2D(100,0));
    // DrawTriangle(Vector2D(0,100),Vector2D(100,0),Vector2D(50,180));
    //
    // 让小房子可以翻转
    
    
    // 画一个三位的正方体
    
}

void RenderSoftWare::DrawLine(Vector2D start, Vector2D end,SColor color)
{

    // 1. 使用DDA方法， SetPixel
    DrawLineDDA(start,end,color);
    
    // 2. 使用Bresenham方法， SetPixel

    
}


void RenderSoftWare::DrawLineDDA(Vector2D start, Vector2D end,SColor color)
{
    int x1 = start.X;
    int x2 = end.X;
    int deltaX = std::abs(x1 - x2);

    int y1 = start.Y;
    int y2 = end.Y;
    int deltaY = std::abs(y1 - y2);

    int MaxDel = std::max(deltaX,deltaY);

    for (int i = 0; i < MaxDel; ++i)
    {
        int x = x1 + i * deltaX / MaxDel;
        int y = y1 + i * deltaY / MaxDel;
        frame_buffer.SetPixel(x, y, color);
    }
}

void RenderSoftWare::DrawLineBresenham(Vector2D start, Vector2D end,SColor color)
{
    
}



void RenderSoftWare::DrawTriangle(Vector2D a, Vector2D b, Vector2D c)
{
    
}

void RenderSoftWare::Present()
{
    // frame_buffer 转化为PNG
    const int width  = frame_buffer.GetWidth();
    const int height = frame_buffer.GetHeight();
    const SColor* src = frame_buffer.GetData();

    if (!src || width <= 0 || height <= 0)
    {
        return;
    }

    // SColor 的内存布局就是 R,G,B,A，与 stb 要求的字节序完全一致，可直接输出无需转换
    ImageUtil::SaveImage("Saved/Software/Frame.png", src, width, height, 4);
}
