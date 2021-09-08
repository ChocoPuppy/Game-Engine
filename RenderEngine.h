#pragma once
#include "Renderer.h"
struct Transform2D;
class Texture;
class RenderEngine : public SDL::Renderer
{
public:
	RenderEngine( SDL::Window * window );

	void renderTexture( Transform2D const & transform, Texture const & texture ) const;
};
