#pragma once
#include <string>

class FileUtil
{
public:

    static std::string LoadFileToString(const char* FilePath);

    static std::string ConvertToAbsolutePath(const char* RelativePath);
};
