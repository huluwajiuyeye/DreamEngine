
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

        // Tick可以使用一个优先队列，不同模块的优先级可配置，这样方便后期调整
        // 值同步如何同步，不是一整个Struct一起同步， 而是将Struct展开，展成最基本的变量，哪个有改变，同步哪个。这样就天然支持增量同步
        
        // 游戏主循环
        _GameMain->Tick();

        // 渲染主循环
        _RenderMain->Tick();
        
    }
    
    return 0;
}
