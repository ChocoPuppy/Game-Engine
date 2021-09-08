#pragma once
namespace Framerate
{
	constexpr float millisecondsPerSecond = 1000.0;
	constexpr unsigned long maxFPS = 30;
	constexpr unsigned long minimumFrameTime = millisecondsPerSecond / maxFPS;
}