#include "Keyframe.h"



Keyframe::Keyframe()
{
}


Keyframe::~Keyframe()
{
}

void Keyframe::InterpolateTranslation(float mTime)
{
}

void Keyframe::InterpolateRotation(float mTime, Keyframe mNextKeyframe)
{
	XMVECTOR startRot, endRot, slerp;
	startRot = XMLoadFloat4(&m_v4LocalRotation);
	endRot = XMLoadFloat4(&mNextKeyframe.m_v4LocalRotation);

	slerp = XMQuaternionSlerpV(startRot, endRot, XMLoadFloat(&mTime));

	XMStoreFloat4(&m_v4LocalRotation, slerp);
}
