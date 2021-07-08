#pragma once
#include "SDLBase.h"
#include "Coordinates.h"
#include "Size.h"

#include <memory>
#include <string>
namespace SDL
{
	class Renderer;
	class Window;
	class WindowBuilder
	{
		typedef std::unique_ptr<Window> WindowPointer;
		WindowPointer _window;

	public:

		WindowBuilder();

		void setPosition( Coordinates );
		void setSize( Size );
		void setIsFullscreen( bool state );
		void setIsDesktopFullscreen( bool state );
		void setIsBorderless( bool state );
		void setIsResizable( bool state );
		void setHighDPI( bool state );
		void setTitle( const std::string & title );

		void reset();

		Window * getWindow();
	};
	class Window
	{
		friend WindowBuilder;
		friend Renderer;
		SDL_Window * _window;

		Window();

		SDL_Window * _getWindow() const;
		SDL_Window * _getWindow();

		Uint32 getFlags() const;
		static SDL_bool convertBool( bool );
	public:

		~Window();

		void setPosition( Coordinates );
		void setSize( Size );
		void setIsFullscreen( bool state );
		void setIsDesktopFullscreen( bool state );
		void setIsBorderless( bool state );
		void setIsResizable( bool state );
		void setTitle( const std::string & title );

		void minimize();
		void maximize();
		void hide();
		void show();
		void restore();

		Coordinates getPosition() const;
		Size getSize() const;
		bool getIsFullscreen() const;
		bool getIsDesktopFullscreen() const;
		bool getIsBorderless() const;
		bool getIsResizable() const;
		bool getIsMinimised() const;
		bool getIsMaximised() const;
	};
}
