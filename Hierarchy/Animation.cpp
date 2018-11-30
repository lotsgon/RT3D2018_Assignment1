#include "Animation.h"



Animation::Animation()
{
}


Animation::~Animation()
{
}

void Animation::Update()
{
	if (m_currentKeyframe >= mKeyframes.size)
	{
		m_currentKeyframe = 0;
	}

	mKeyframes[m_currentKeyframe].InterpolateRotation(m_currentAnimationTime, mKeyframes[m_currentKeyframe + 1]);
}
