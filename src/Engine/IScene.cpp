#include "Engine/IScene.h"

IScene::IScene()
{
    request = false;
}

IScene::~IScene()
{
    if(request and scene)
    {
        delete scene;
    }
}

void IScene::pause() {}

void IScene::resume() {}

bool IScene::pollRequest(IScene*& scene, bool& replace)
{
    if(request)
    {
        scene = this->scene;
        replace = this->replace;
        request = false;
        return true;
    }
    return false;
}

void IScene::changeScene(IScene* scene, bool replace)
{
    if(request and this->scene)
    {
        delete this->scene;
    }
    this->scene = scene;
    this->replace = replace;
    request = true;
}

void IScene::closeScene()
{
    if(request and scene)
    {
        delete scene;
    }
    scene = nullptr;
    request = true;
}
