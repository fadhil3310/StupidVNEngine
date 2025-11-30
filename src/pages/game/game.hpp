#pragma once


#include "../page.hpp"
#include "../../engine/scene_manager.hpp"

struct GamePageData
{
    SceneManager* sceneMg;

    std::string saveName;
    int loadFromScene = 0;
    UIElement *sceneImage;
};

Page* GamePG_Create();
Page* GamePG_CreateFromSave(std::string saveName);
