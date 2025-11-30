#pragma once

#include <queue>
#include <functional>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "canvas.hpp"
#include "ui.hpp"
#include "graph.hpp"
#include "../scenes/scene.hpp"

struct Scene;
struct Graph;

//
// ============================
// ========== Dialog ==========
// ============================
//

// The character position in the dialog
enum class DialogPersonPosition
{
    Left,
    Center,
    Right
};
// Character animation
enum class DialogPersonAnimation
{
    None,
    Slide,
    FadeIn,
    FadeOut,
    Shake,
    Pop,
    Joget, // Translate: dance
};

struct DialogPerson
{
    std::string imageFilePath;
    DialogPersonPosition position;
    DialogPersonAnimation animation = DialogPersonAnimation::None;
};

struct DialogQuestion
{
    std::string question;

    std::function<void(Scene *)> onAnswered;
    Scene *onAnsweredParameter;
};

struct Dialog
{
    std::string name;
    std::string message;
    std::vector<DialogPerson> persons;
    std::vector<DialogQuestion> questions;

    std::function<void(Scene *)> onFinished;
    Scene *onFinishedParameter;
};

//
// =============================
// =========== Sound ===========
// =============================
//

struct SceneSound
{
    sf::SoundBuffer *buffer;
    sf::Sound *soundPlayer;

    ~SceneSound()
    {
        delete buffer;
        delete soundPlayer;
    }
};

//
// =============================
// ======= Scene Manager =======
// =============================
//

enum class SceneTransition
{
    None,
    Fade,
    FadeEnding // Only for my game purpose, forgot what does it mean
};

enum class SceneManagerState
{
    Empty,
    Navigating,
    Talking,
    Rest
};

struct SceneManager;
void SceneManager_Destroy(SceneManager *sceneManager);
struct SceneManager
{
    std::string saveName;

    Graph *graph;
    
    SceneManagerState state = SceneManagerState::Empty;
    EngineWindow *engineWindow;
    Canvas *canvas;
    
    Scene *currentScene;
    int currentSceneNumber;
    Scene *pendingScene = nullptr;
    SceneTransition sceneTransition = SceneTransition::None;
    bool isTransitioningScene = false;
    bool isPendingSceneHasEntered = false;
    float sceneTransitionProgress = 0.0f;

    sf::Texture *backgroundImage = nullptr;

    std::queue<Dialog *> dialogQueue;
    bool isFirstDialog = true;
    float dialogAnimProgress = 0.f;
    float dialogAnimProgressStep = 0.05f;
    int dialogTextProgress = -1;
    int dialogTextProgressMax = -1;
    int dialogTextWaitTime = 4;
    float dialogAnimProgressAfterText = 0.f;
    bool dialogEnterKeyPressed = false;

    bool isSaveButtonClicked;

    sf::Music *musicPlaying = nullptr;
    std::vector<SceneSound *> soundsPlaying;

    void (*update)(SceneManager *sceneMg);

    ~SceneManager()
    {
        SceneManager_Destroy(this);
    }
};

// Create SceneManager
SceneManager *SceneManager_Create(std::string saveName, Graph *graph, Canvas *canvas, EngineWindow *engineWindow);

// Navigate to other scene (using the number of the scene in the graph)
void SceneManager_GoToScene(SceneManager *sceneManager, int sceneNumber, SceneTransition transition);
// Change the background of the scene
void SceneManager_SetBackground(SceneManager *sceneMg, std::string filePath);

// Add a dialog (person max 3, fill "persons" and "questions" with empty vector if you don't want to show any persons or questions)
void SceneManager_AddDialog(SceneManager *sceneMg, std::vector<DialogPerson> persons, std::vector<DialogQuestion> questions, std::string name, std::string message);
// Same, but with a callback that will be called after the dialog has been closed
void SceneManager_AddDialog(SceneManager *sceneMg, std::vector<DialogPerson> persons, std::vector<DialogQuestion> questions, std::string name, std::string message, std::function<void(Scene *)> onFinished, Scene *onFinishedParameter);

// Play a music (If there's a music that is currently playing, the music will be stopped immediately)
void SceneManager_PlayMusic(SceneManager *sceneMg, std::string filePath);
// Stop music that is currently playing
void SceneManager_StopMusic(SceneManager *sceneMg);

// Play a sound
void SceneManager_PlaySound(SceneManager *sceneMg, std::string filePath);