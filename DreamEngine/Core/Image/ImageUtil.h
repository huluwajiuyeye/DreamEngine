#pragma once
#include <string>

class ImageUtil
{
public:
    // IamgePath: RelativePath /Save/Iamge.png
    // 与ReleaseImageData成对调用，ImageData需要手动释放
    static unsigned char* LoadImage(std::string ImagePath, int &width, int &height, int &nrChannels);

    static void ReleaseImageData(unsigned char* ImageData);
};
