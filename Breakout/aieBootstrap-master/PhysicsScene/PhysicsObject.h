#pragma once
#include <glm\ext.hpp>

#ifndef SHAPE_COUNT
	#define SHAPE_COUNT 3
#endif // !SHAPE_COUNT

enum ShapeType
{
	LINE = 0,
	CIRCLE,
	RECTANGLE

};

class PhysicsObject
{
protected:
		PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {}
public:
	
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	virtual void debug() = 0;
	virtual void makeGizmo() = 0;
	virtual void resetPosition() {};
	ShapeType getShapeID() { return m_shapeID; }

	

protected:
	ShapeType m_shapeID;
};

