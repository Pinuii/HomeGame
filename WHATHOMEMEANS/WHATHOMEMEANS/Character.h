#pragma once
#include "AnimationManager.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Character
{
public:
	Character();

	bool loadTexture(const std::string& path);

	void addAnimation(
		const std::string& name,
		const std::string& texturePath,
		int startX, int startY,
		int frameW, int frameH,
		int frameCount,
		float frameTime = 0.1f,
		bool loop = true);

	void playAnimation(const std::string& name);

	void setPosition(float x, float y);
	void setScale(float sx, float sy);
	void handleInput();
	//void setState(const std::string& state);

	void update(float dt);
	void draw(sf::RenderTarget& target) const;

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	AnimationManager m_animManager;

	sf::Vector2f m_velocity;

	float m_speed = 150.f;

	float m_gravity = 800.f;
	float m_jumpForce = -450.f;

	bool m_wasOnGround = true;
	bool m_onGround = true;
	bool m_facingRight = true;
	bool m_isAttacking = false;
};