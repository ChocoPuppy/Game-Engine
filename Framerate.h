#pragma once
namespace Framerate
{
	constexpr unsigned long millisecondsPerSecond = 1000;
	constexpr unsigned long maxFPS = 30;
	constexpr unsigned long minimumFrameTime = millisecondsPerSecond / maxFPS;
}