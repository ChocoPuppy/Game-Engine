#pragma once
#include "Renderer.h"
#include "Vector2D.h"
#include "Coordinates.h"
#include "SDLBase.h"
struct Transform2D;
class Texture;
class RenderEngine : public SDL::Renderer
{
	SDL::Window & _window;
	Coordinates _cameraClip = { 1024,1024 };

public:
	RenderEngine( SDL::Window * window );

	SDL::Window const & getWindow() const noexcept;

	Vector2D worldPosToScreenPos( Vector2D worldPos ) const;
	Vector2D worldPosToSubPixelPos( Vector2D worldPos ) const;
	Coordinates worldPosToPixelPos( Vector2D worldPos ) const;
	Vector2D screenPosToSubPixelPos( Vector2D screenPos ) const;
	Vector2D screenPosToWorldPos( Vector2D screenPos ) const;

	void renderTexture( Transform2D const & transform, Texture const & texture, SDL_RendererFlip flip = SDL_FLIP_NONE ) const;
};
