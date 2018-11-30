#ifndef ANIMATION_H
#define ANIMATION_H

#pragma once

#include <vector>
#include "Keyframe.h"

class Animation
{
public:
	Animation();
	~Animation();

	void Update();

private:

	float m_currentAnimationTime;
	float m_currentKeyframe;

public:
	std::vector<Keyframe> mKeyframes;
	std::string mAnimationName;
};

#endif

