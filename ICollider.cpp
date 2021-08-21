#include "ICollider.h"
#include "AssetManager.h"
#include "Renderer.h"
#include "TextureWrapper.h"
#include "Transform2D.h"
#include "Size.h"
#include "RenderEngine.h"
void Collision::ICollider::render( Transform2D const & transform, AssetManager const & assets, RenderEngine const & renderer ) const
{
	renderer.renderTexture( transform, *assets.getAsset<Texture>( getTextureID() ) );
}