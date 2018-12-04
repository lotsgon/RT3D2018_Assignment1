#include "Animation.h"



Animation::Animation()
{
}


Animation::~Animation()
{
}

void Animation::Update()
{
	if (m_currentKeyframe >= mKeyframes.size() -1)
	{
		m_currentKeyframe = 0;
		m_currentAnimationTime = 0;
	}
	else
	{
		mKeyframes[m_currentKeyframe].InterpolateRotation(m_currentAnimationTime/10.0f, mKeyframes[m_currentKeyframe + 1], &m_v4LocalRotation);
	}

	if (m_currentAnimationTime >= mKeyframes[m_currentKeyframe].m_KeyframeTime)
	{
		m_currentKeyframe++;
	}

	if (debugTime)
	{
		m_currentAnimationTime += m_animationFrameTime / 30.0f;
	}
	else
	{
		m_currentAnimationTime += m_animationFrameTime;
	}
}
