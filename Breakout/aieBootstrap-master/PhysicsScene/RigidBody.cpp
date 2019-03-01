#include "RigidBody.h"



RigidBody::RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass) : 
					 PhysicsObject(shapeID), m_position(position), m_velocity(velocity), m_rotation(rotation), m_mass(mass)
{
}

RigidBody::~RigidBody()
{
}

void RigidBody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	applyForce(gravity * m_mass * timeStep);
	m_position += m_velocity * timeStep;
}

void RigidBody::debug()
{
}

void RigidBody::applyForce(glm::vec2 force)
{
	m_velocity += force / m_mass;
}

void RigidBody::applyForceToActor(RigidBody * actor2, glm::vec2 force)
{
	applyForce(-force);
	actor2->applyForce(force);
}

void RigidBody::setVelocity(glm::vec2 velocity)
{
	m_velocity = velocity;
}

void RigidBody::resolveCollision(RigidBody * actor2)
{
	glm::vec2 normal = glm::normalize(actor2->getPosition() - m_position);
	glm::vec2 relativeVelocity = actor2->getVelocity() - m_velocity;

	float elasticity = (m_elasticity + actor2->getElasticity()) / 2.0f;
	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) / glm::dot(normal, normal* ((1 / m_mass) + (1 / actor2->getMass())));

	glm::vec2 force = normal * j;

	applyForceToActor(actor2, -force);
}
