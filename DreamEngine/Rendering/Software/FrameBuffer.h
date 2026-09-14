#pragma once
#include <vector>

#include "../../Core/Color/SColor.h"

class FrameBuffer
{

private:
    std::vector<SColor> _buffer;
    int _width = 0;
    int _height = 0;

public:
    FrameBuffer() = default;

    FrameBuffer(int width, int height)
    {
        Init(width, height);
    }

    void Init(int width, int height)
    {
        _width = width;
        _height = height;
        _buffer.assign(static_cast<size_t>(width) * height, SColor());
    }

    // 清空buffer,恢复为全黑
    void Clear(SColor color = SColor::Black());

    void SetPixel(int x, int y, SColor color);

    int GetWidth()  const { return _width; }
    int GetHeight() const { return _height; }

    // 返回只读像素数据，供 Present 读取
    const SColor* GetData() const { return _buffer.data(); }
};
