#include <cstdlib>
#include <ctime>
#include "GameObjects.h"
#include "GameManager.h"

Enemy::Enemy(int id)
{
	this->id = id;
}

Enemy::Enemy(int id, float xPos)
{
	this->id = id;

	m_sprite = new Square(m_width, m_height);
	setPosition(m_sprite->bounds.getOffset(Vector(xPos, 0), Vector(0, -1)));

	m_mass = 1;
	m_drag = 0;
	m_gravity = 5;
}

void Enemy::tick(float deltaTime)
{
	auto halfWidth = m_width / 2;
	auto screenWidth = GameManager::instance()->screenWidth;

	iterateMovement(deltaTime);

	//	Enemy bouncing.
	if (m_velocity.x < 0 && m_position.x - halfWidth <= 0)
	{
		m_position.x = 0 + halfWidth;
		bounce();
	}
	else if (m_velocity.x > 0 && m_position.x + halfWidth >= screenWidth)
	{
		m_position.x = screenWidth - halfWidth;
		bounce();
	}

	//	Guard clause for switching force.
	m_timer += deltaTime;
	if (m_timer < m_chosenTime) return;

	//	Giving enemy random constant force.
	auto force = (rand() % (m_maxForceRange * 2)) - m_maxForceRange;
	addForce(Vector(force, 0));

	//	Preparing for new timer.
	m_chosenTime = (float)(m_minSwitchInterval + (rand() % (m_maxSwitchInterval - m_minSwitchInterval))) / 100;
	m_timer = 0;
}

void Enemy::bounce()
{
	m_velocity.x = -m_velocity.x;
	m_actingForce = -m_actingForce;
}