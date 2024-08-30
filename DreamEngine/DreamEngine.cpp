
#include <iostream>

#include "Core/Object.h"
#include "Game/GameMain.h"
#include "Rendering/RenderCore/RenderMain.h"

// 获取用户数据
void GetUserInput()
{
    
}

// 是否退出游戏
bool Exit()
{
    return false;
}

int main(int argc, char* argv[])
{

    GameMain* _GameMain = new GameMain();
    RenderMain* _RenderMain = new RenderMain();
    
    while (true)
    {
        // 获取用户输入
        GetUserInput();

        // 是否退出游戏
        if(Exit())
        {
            break;
        }

        // 游戏主循环
        _GameMain->Tick();

        // 渲染主循环
        _RenderMain->Tick();
        
    }
    
    return 0;
}
