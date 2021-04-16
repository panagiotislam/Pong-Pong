#include "graphics.h"
#include "fixed.h"
#include "game.h"



void update(float ms)
{
    Game* game = reinterpret_cast <Game*>(graphics::getUserData());
    game->update();
}


void draw()
{
    Game* game = reinterpret_cast <Game*>(graphics::getUserData());
    game->draw();
}

int main()
{
    Game myGame;
    
    graphics::createWindow(WINDOW_SIZE, WINDOW_SIZE, "Pong-pong");
      
    graphics::setUserData(&myGame);

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(CANVAS_SIZE, CANVAS_SIZE);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
    

    myGame.initialize();
    myGame.setDebugMode(false);
    graphics::startMessageLoop();

    return 0;
}