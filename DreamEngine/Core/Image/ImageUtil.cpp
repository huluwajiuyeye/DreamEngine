#include "ImageUtil.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "../Plugin/stb_Image/stb_image.h"

unsigned char* ImageUtil::LoadImage(std::string ImagePath, int &width, int &height, int &nrChannels)
{
    unsigned char *data = stbi_load(ImagePath.c_str(), &width, &height, &nrChannels, 0);
    if(!data)
    {
        std::cout<<"ImageUtil::LoadImage error ImagePath:"<< ImagePath << std::endl;
    }
    return data;
}

void ImageUtil::ReleaseImageData(unsigned char* ImageData)
{
    stbi_image_free(ImageData);
}
