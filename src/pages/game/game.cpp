#include "game.hpp"

#include <iostream>
#include <fstream>

// Note: this code only serves as an example on how to create scenes,
// connect it to other scene, and start the scene

// #include "../../scenes/scene_1/scene_1.hpp"
// #include "../../scenes/scene_1/scene_2.hpp"
// #include "../../scenes/scene_2/scene_3.hpp"

void GamePG_Start(Page *page)
{
    GamePageData *data = (GamePageData *)page->data;

    Graph *graph = Graph_Create({
        // Scene1_Create(),
        // Scene2_Create(),
        // Scene3_Create(),
    });

    // Scene 1 [Connect to Scene 2]
    // Graph_AddConnection(graph, 0, 1);
    // Scene 2 [Connect to Scene 3]
    // Graph_AddConnection(graph, 1, 2);

    Canvas *canvas = Canvas_Create();
    SceneManager *sceneMg = SceneManager_Create(data->saveName, graph, canvas, page->pageManager->engineWindow);
    data->sceneMg = sceneMg;

    // Navigate to the first scene in the graph
    SceneManager_GoToScene(sceneMg, data->loadFromScene, SceneTransition::None);
    // Set default background for the scene
    data->sceneImage = UI_AddImage(page->ui, nullptr, 0, 0, 1000, 550, false, "");
}

void GamePG_Update(Page *page)
{
    GamePageData *data = (GamePageData *)page->data;
    SceneManager *sceneMg = data->sceneMg;

    sceneMg->update(sceneMg);
    UI_CopyCanvasToImage(page->ui, (Image *)data->sceneImage->properties, sceneMg->canvas);
}

void GamePG_Destroy(Page *page)
{
    GamePageData *data = (GamePageData *)page->data;
    delete data->sceneImage;
    delete data->sceneMg;
}

Page *GamePG_Create()
{
    GamePageData *data = new GamePageData{};
    Page *page = new Page{
        .data = data,
        .start = GamePG_Start,
        .update = GamePG_Update,
        .destroy = GamePG_Destroy};
    return page;
}

Page *GamePG_CreateFromSave(std::string saveName)
{
    GamePageData *data = new GamePageData{};

    // Load game logic
    // Example:
    //
    // std::ifstream inFile("./saves/" + saveName);
    // // Check if the file is open
    // if (!inFile)
    // {
    //     throw std::invalid_argument("Failed opening save file");
    // }

    // int loadFromScene = -1;
    // inFile >> loadFromScene;
    // if (inFile.fail()) {
    //     inFile.close();
    //     throw std::invalid_argument("Failed loading save file");
    // }

    data->saveName = saveName;
    data->loadFromScene = loadFromScene;

    Page *page = new Page{
        .data = data,
        .start = GamePG_Start,
        .update = GamePG_Update,
        .destroy = GamePG_Destroy};
    return page;
}