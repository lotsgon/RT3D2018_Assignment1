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

void Keyframe::InterpolateRotation(float mTime, Keyframe mNextKeyframe, XMFLOAT4* mAnimationRotation)
{
	XMVECTOR startRot, endRot, slerp, lerp;
	startRot = XMLoadFloat4(&m_v4LocalRotation);
	endRot = XMLoadFloat4(&mNextKeyframe.m_v4LocalRotation);

	slerp = XMQuaternionSlerp(startRot, endRot, mTime);

	XMStoreFloat4(mAnimationRotation, slerp);
}
