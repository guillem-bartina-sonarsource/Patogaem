#include "Engine/Game.h"
#include "Engine/Resources.h"
#include "Engine/ImguiSceneDecorator.h"
#include "SceneMenu.h"

int main()
{
  Resources::getInstance()->setPath("rsc/");

  Game game;

  game.launch(
    Window::Builder(new ImguiSceneDecorator(new SceneMenu(0)))
    .setFullscreen(1000, 800)
    .enableMultiscene()
    .setTitle("TITLE")
    .build());
  game.wait();

  return 0;
}
