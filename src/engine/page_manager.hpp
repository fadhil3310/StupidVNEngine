#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "engine_window.hpp"
#include "canvas.hpp"
#include "../pages/page.hpp"

struct Page;

struct PageSound
{
    sf::SoundBuffer *buffer;
    sf::Sound *soundPlayer;

    ~PageSound()
    {
        delete buffer;
        delete soundPlayer;
    }
};

struct PageManager
{
    EngineWindow *engineWindow;
    Canvas *canvas;

    Page *currentPage = nullptr;
    Page *pendingPage = nullptr;
    bool isTransitioningPage = false;
    bool isPendingPageHasEntered = false;
    Canvas *lastPageCanvas = nullptr;
    float pageTransitionProgress = 0.0f;

    sf::Music *musicPlaying = nullptr;
    std::vector<PageSound *> soundsPlaying;

    void (*update)(PageManager *pageMg);
};

PageManager *PageManager_Create(EngineWindow *engineWindow, sf::RenderTexture *engineRenderTexture);
void PageManager_GoToPage(PageManager *pageMg, Page *page);

// Play a music (If there's a music that is currently playing, the music will be stopped immediately)
void PageManager_PlayMusic(PageManager *pageMg, std::string filePath);
// Stop music that is currently playing
void PageManager_StopMusic(PageManager *pageMg);

// Play a sound
void PageManager_PlaySound(PageManager *pageMg, std::string filePath);