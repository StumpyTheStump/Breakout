#pragma 
#include "RigidBody.h"
#include <glm\ext.hpp>

class Rectangle : public RigidBody
{
public:
	Rectangle(glm::vec2 position, glm::vec2 velocity, float mass, glm::vec2 size, glm::vec4 colour);
	~Rectangle();

	virtual void makeGizmo();
	virtual bool checkCollision(PhysicsObject* pOther);

	glm::vec2 getSize() { return m_size; }
	glm::vec4 getColour() { return m_colour; }

protected:
    glm::vec2 m_size;
	glm::vec4 m_colour;

};

