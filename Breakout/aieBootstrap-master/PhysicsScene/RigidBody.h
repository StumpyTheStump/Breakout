#pragma once
#include "PhysicsObject.h"
#include <glm\ext.hpp>

class RigidBody : public PhysicsObject
{
public:
	RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass);
	~RigidBody();

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void debug();
	void applyForce(glm::vec2 force);
	void applyForceToActor(RigidBody* actor2, glm::vec2 force);
	
	void resolveCollision(RigidBody* actor2);

	virtual bool checkCollision(PhysicsObject* pOther) = 0;
	glm::vec2 getPosition() { return m_position; }
	float getRotation() { return m_rotation; }
	glm::vec2 getVelocity() { return m_velocity; }
	float getMass() { return m_mass; }
	void setVelocity(glm::vec2 velocity);
	float getElasticity() { return m_elasticity; }

protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_elasticity;
	float m_mass;
	float m_rotation; // single float for 2D
};

