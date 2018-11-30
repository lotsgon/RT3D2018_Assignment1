#ifndef KEYFRAME_H
#define KEYFRAME_H

#pragma once

#include "D3DHelpers.h"

class Keyframe
{
public:
	Keyframe();
	~Keyframe();

private:
	void InterpolateTranslation(float mTime);

public:

	XMFLOAT4 m_v4LocalRotation; // Euler rotation angles
	XMFLOAT4 m_v4LocalPosition; // Local position
	float m_KeyframeTime;

	void InterpolateRotation(float mTime, Keyframe mNextKeyframe);


};

#endif

