#pragma once
#include "RenderBase.h"
#include "../../Core/Object.h"

class RenderMain:Object
{
public:
    virtual void Tick() override;

    void Init();
    
    RenderBase* Render;
};
