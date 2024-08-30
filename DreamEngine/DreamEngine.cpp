
#include <iostream>

#include "Core/Object.h"
#include "Game/GameMain.h"
#include "Rendering/RenderCore/RenderMain.h"

GameMain* _GameMain;
RenderMain* _RenderMain;

void InitGame()
{
     _GameMain = new GameMain();
     _RenderMain = new RenderMain();
    
    _GameMain->Init();
    _RenderMain->Init();
}

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
    
    InitGame();
    
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
