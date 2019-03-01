#include "Rectangle.h"
#include <Gizmos.h>

Rectangle::Rectangle(glm::vec2 position, glm::vec2 velocity, float mass, glm::vec2 size, glm::vec4 colour) : RigidBody(RECTANGLE, position, velocity, 0, mass)
{
	m_position = position;
	m_size = size;
	m_colour = colour;
}

Rectangle::~Rectangle()
{
}

void Rectangle::makeGizmo()
{
	aie::Gizmos::add2DAABBFilled(m_position, m_size, m_colour);
}

bool Rectangle::checkCollision(PhysicsObject * pOther)
{
	return false;
}
