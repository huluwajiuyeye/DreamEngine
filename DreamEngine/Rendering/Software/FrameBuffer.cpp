#include "FrameBuffer.h"

#include <algorithm>   // std::fill


// _buffer 里面都换成纯黑色的
void FrameBuffer::Clear(SColor color)
{
    std::fill(_buffer.begin(), _buffer.end(), color);
}

void FrameBuffer::SetPixel(int x, int y, SColor color)
{
    _buffer[y * _width + x] = color;
}
