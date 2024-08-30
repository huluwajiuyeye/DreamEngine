#pragma once
#include <windows.h>

#include "../Core/Object.h"

class GameMain:Object
{
public:
    virtual void Tick() override;

    void Init();
};
