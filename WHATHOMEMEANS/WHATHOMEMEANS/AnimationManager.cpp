#include "AnimationManager.h"
#include <cassert>

void AnimationManager::addAnimation(const std::string& name, const Animation& anim)
{
	m_animations[name] = anim;
}

void AnimationManager::play(const std::string& name)
{
	if (m_current == name)
		return;

	assert(m_animations.count(name) && "ff");//j'ai un assert chui content
	m_current = name;
	m_frameIndex = 0;
	m_elapsed = 0.f;
	m_finished = false;
}

void AnimationManager::update(float dt)
{
	if (m_current.empty() || m_finished)
		return;

	auto& anim = m_animations.at(m_current);
	m_elapsed += dt;

	while (m_elapsed >= anim.frameTime)
	{
		m_elapsed -= anim.frameTime;
		m_frameIndex++;

		if (m_frameIndex >= anim.frames.size())
		{
			if (anim.loop)
				m_frameIndex = 0;
			else
			{
				m_frameIndex = anim.frames.size() - 1;
				m_finished = true;
				break;
			}
		}
	}
}

const sf::IntRect& AnimationManager::getCurrentRect() const
{
	return m_animations.at(m_current).frames[m_frameIndex];
}
const sf::Texture& AnimationManager::getCurrentTexture() const
{
	return m_animations.at(m_current).texture;
}

bool AnimationManager::isFinished() const
{
	return m_finished;
}