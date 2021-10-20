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
	Vector2D _cameraClip = { 1024,1024 };

	Vector2D _getCameraClip() const;
public:
	RenderEngine( SDL::Window * window );

	SDL::Window const & getWindow() const noexcept;

	//Converts the world position to a position in 0-1 screenspace (0 being one edge of the screen, 1 being the other)
	Vector2D worldPosToScreenPos( Vector2D worldPos ) const;
	Vector2D worldPosToSubPixelPos( Vector2D worldPos ) const;
	Coordinates worldPosToPixelPos( Vector2D worldPos ) const;
	//Currently equivalent to screenPosToWorldPos as at the moment world positions are equivalent to pixel positions. I may change that, which is why this has been left here.
	Vector2D screenPosToSubPixelPos( Vector2D screenPos ) const;
	//Converts the screen position in 0-1 screenspace to the equivalent world position.
	Vector2D screenPosToWorldPos( Vector2D screenPos ) const;

	void renderTexture( Transform2D const & transform, Texture const & texture, SDL_RendererFlip flip = SDL_FLIP_NONE );
};
