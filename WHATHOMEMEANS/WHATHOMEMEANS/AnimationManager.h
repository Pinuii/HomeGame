#pragma once
#include "Animation.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class AnimationManager
{
public:
	void addAnimation(const std::string& name, const Animation& anim);
	void play(const std::string& name);
	void update(float dt);

	const sf::IntRect& getCurrentRect() const;
	const sf::Texture& getCurrentTexture() const;
	bool isFinished() const;

private:
	std::unordered_map<std::string, Animation> m_animations;
	std::string m_current;
	std::size_t m_frameIndex = 0;
	float m_elapsed = 0.f;
	bool m_finished = false;
};