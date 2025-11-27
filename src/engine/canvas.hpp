#pragma once

#include <map>
#include <SFML/Graphics.hpp>

#include "../utils.hpp"

enum class Alignment
{
    Left,
    Center,
    Right
};

struct Canvas
{
    bool isRenderTextureFromExternal = false;
    sf::RenderTexture *renderTexture;

    std::map<std::string, sf::Font> fontCache;
    std::map<std::string, sf::Texture> textureCache;

    ~Canvas()
    {
        if (!isRenderTextureFromExternal)
            delete renderTexture;
    }
};

// Create canvas
Canvas *Canvas_Create();
// Create canvas with the provided RenderTexture
Canvas *Canvas_Create(sf::RenderTexture *renderTexture);

// Clear canvas content
void Canvas_Clear(Canvas *canvas);
// Apply any changes to the canvas (call this after you have done any updates to the canvas)
void Canvas_Update(Canvas *canvas);

// Draw rectangle
void Canvas_DrawRect(Canvas *canvas, int x, int y, int width, int height, sf::Color color);
// Draw circle
void Canvas_DrawCircle(Canvas *canvas, int x, int y, int radius, sf::Color color);

// Draw text
void Canvas_DrawText(Canvas *canvas, int x, int y, std::string text, std::string fontPath, int fontSize, sf::Color color);
// Draw text, but you can set the alignment of the text
void Canvas_DrawText(Canvas *canvas, int x, int y, int width, int height, std::string text, std::string fontPath, Alignment alignment, int fontSize, sf::Color color);

// Draw SFML sprite (please use DrawImage if you want to draw an image)
void Canvas_DrawSprite(Canvas *canvas, int x, int y, int width, int height, bool stretch, sf::Sprite *sprite, float opacity = 1.0, float rotation = 0.0, float scale = 1.0);

// Draw SFML texture (please use DrawImage if you want to draw an image)
void Canvas_DrawTexture(Canvas *canvas, int x, int y, sf::Texture *texture, float opacity = 1.0, float rotation = 0.0, float scale = 1.0);
void Canvas_DrawTexture(Canvas *canvas, int x, int y, int width, int height, bool stretch, sf::Texture *texture, float opacity = 1.0, float rotation = 0.0, float scale = 1.0);

// Draw an image
void Canvas_DrawImage(Canvas *canvas, int x, int y, std::string filePath, float opacity = 1.0, float rotation = 0.0, float scale = 1.0);
// Draw an image, but you can set the alignment of the image
void Canvas_DrawImage(Canvas *canvas, int x, int y, Alignment alignment, std::string filePath, float opacity = 1.0, float rotation = 0.0, float scale = 1.0);

// Copy the content of the canvas to another canvas
void Canvas_Copy(Canvas *targetCanvas, Canvas *srcCanvas);
// Grab the content of the canvas as an SFML texture
sf::Texture Canvas_GetTexture(Canvas *canvas);