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
	float m_animationFrameTime = 1.0f/60.0f;
	int m_currentKeyframe;
	bool debugTime = false;
	XMFLOAT4 m_v4LocalRotation = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f); // Euler rotation angles

public:
	std::vector<Keyframe> mKeyframes;
	std::string mAnimationName;
	XMFLOAT4 GetLocalRotation(void) { return m_v4LocalRotation; }
	float GetCurrentAnimationTime(void) { return m_currentAnimationTime; }
	void SetDebugTime(bool value) { debugTime = value; }
};

#endif

