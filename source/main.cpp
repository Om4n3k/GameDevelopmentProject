#include "Game.h"
#include <eng.h>

int main()
{
    const auto game = new Game();
    eng::Engine& engine = eng::Engine::GetInstance();
    engine.SetApplication(game);
    if (!engine.Init(1280, 720)) {
        return -1;
    }
    engine.Run();
    engine.Destroy();
    return 0;
}
