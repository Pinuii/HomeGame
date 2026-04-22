#include "Character.h"

Character::Character()
	: m_texture()
	, m_sprite(m_texture)   // construct sprite with the texture (no default ctor required)
	, m_animManager()
{
	m_sprite.setScale({ 4.f, 4.f });
}

bool Character::loadTexture(const std::string& path)
{
	if (!m_texture.loadFromFile(path))
		return false;

	// assign the freshly-loaded texture to the sprite
	sf::Vector2u size = m_texture.getSize();
	m_sprite.setOrigin({ size.x / 2.f, 0.f });
	m_sprite.setTexture(m_texture);
	return true;
}

void Character::addAnimation(
	const std::string& name,
	const std::string& texturePath,
	int startX, int startY,
	int frameW, int frameH,
	int frameCount,
	float frameTime,
	bool loop)
{
	Animation anim;
	anim.texture.loadFromFile(texturePath);
	anim.frameTime = frameTime;
	anim.loop = loop;

	for (int i = 0; i < frameCount; ++i)
	{
		anim.frames.emplace_back(
			sf::Vector2i(startX, startY + i * frameH),
			sf::Vector2i(frameW, frameH)
		);
	}

	m_animManager.addAnimation(name, anim);
}

void Character::playAnimation(const std::string& name)
{
	m_animManager.play(name);
	m_sprite.setTexture(m_animManager.getCurrentTexture());
}

void Character::setPosition(float x, float y)
{
	m_sprite.setPosition({ x, y });
}

void Character::setScale(float sx, float sy)
{
	m_sprite.setScale({ sx, sy });
}

void Character::handleInput()
{
	m_velocity.x = 0.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		m_velocity.x += m_speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		m_velocity.x -= m_speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && m_onGround)
	{
		m_velocity.y = m_jumpForce;
		m_onGround = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X) && !m_isAttacking)
	{
		m_isAttacking = true;
		m_animManager.play("attack");
	}

	//void Character::setState(const std::string& state)
	//{
	//	if (state == anim.current) // this is a bit hacky, but it works for this simple example
	//		return;
}

void Character::update(float dt)
{
	handleInput();

	if (m_isAttacking)
	{
		m_velocity.x = 0.f;
		m_velocity.y = 0.f;
	}
	m_velocity.y += m_gravity * dt;
	m_sprite.move(m_velocity * dt);

	float groundY = 400.f;
	if (m_sprite.getPosition().y >= groundY)
	{
		m_sprite.setPosition(sf::Vector2f(m_sprite.getPosition().x, groundY));
		m_velocity.y = 0.f;
		m_onGround = true;
	}

	bool justLanded = (!m_wasOnGround && m_onGround);


	if (m_isAttacking && m_animManager.isFinished())
	{
		m_isAttacking = false;
	}
	if (m_velocity.x < 0.f)
		m_facingRight = false;
	else if (m_velocity.x > 0.f)
		m_facingRight = true;

	if (m_facingRight)
		m_sprite.setScale({ 4.f, 4.f });
	else
		m_sprite.setScale({ -4.f, 4.f });

	if (m_isAttacking)
	{
		m_animManager.play("attack");
	}
	else if (justLanded)
	{
		m_animManager.play("landing");
	}
	else if (!m_onGround)
	{
		m_animManager.play("air");
	}
	else if (m_velocity.x != 0.f)
	{
		m_animManager.play("run");
	}
	else
	{
		m_animManager.play("idle");
	}
	m_animManager.update(dt);

	m_sprite.setTexture(m_animManager.getCurrentTexture());
	m_sprite.setTextureRect(m_animManager.getCurrentRect());
}

void Character::draw(sf::RenderTarget& target) const
{
	target.draw(m_sprite);
}