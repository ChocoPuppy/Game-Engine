#pragma once
#include "Vector2D.h"
template<class _T = Vector2D>
struct Lerp
{
	using LerpType = _T;

	LerpType origin;
	LerpType target;
	//The time of the lerp, if this is 1, getCurrentPoint will return target, if this is 0, getCurrentPoint will return origin.
	float currentTime;

	void update( float addTime )
	{
		currentTime += addTime;
	}
	LerpType getCurrentPoint() const
	{
		LerpType const difference = target - origin;
		LerpType const differenceAtCurrentPoint = difference * currentTime;
		LerpType const currentPoint = origin + differenceAtCurrentPoint;
		return currentPoint;
	}
	bool isComplete() const
	{
		return currentTime >= 1;
	}
};
