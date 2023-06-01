#pragma once
#include <cmath>
#include "SFML/Graphics.hpp"
#include "Shapes.h"

class Object
{
protected:
	sf::Vector2f position;

	/// This needs to be a pointer, for when creating an object, we want polymorphism when passing in the sprite.
	/// Without this being a pointer, virtual functions will not work.
	/// Must do more research on preventing memory leaks with pointers.
	Shape* sprite;

public:
	Object();

	Object(Shape* shape, float xPos, float yPos);

	~Object();

	void setPosition(float xPos, float yPos);

	void move(float xOffset, float yOffset);

	void draw(sf::RenderWindow& window);
};



class DynamicObject : public Object
{
protected:
	sf::Vector2f velocity;

public:
	DynamicObject();

	DynamicObject(Shape* shape, float xPos, float yPos, float xVel, float yVel);

	virtual void iterateMovement(float deltaTime);
};



class PhysicsObject : public DynamicObject
{
protected:
	float mass;
	float drag;
	sf::Vector2f acceleration;
	sf::Vector2f force;

public:
	PhysicsObject();

	PhysicsObject(Shape* shape, sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f acceleration);

	PhysicsObject(Shape* shape, sf::Vector2f pos, float ma, float dr);

	PhysicsObject(Shape* shape, float xPos, float yPos);

	void iterateMovement(float deltaTime) override;
};

class InputObject : public DynamicObject
{
protected:
	float speed;
	float grip;
	sf::Vector2f desiredVelocity;

public:
	InputObject();

	InputObject(Shape* shape, sf::Vector2f pos, float sp, float gr);

	void iterateMovement(float deltaTime) override;
};