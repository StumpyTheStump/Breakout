#pragma once
#include <glm\ext.hpp>
#include <vector>

class PhysicsObject;

class PhysicsScene
{
public:
	PhysicsScene();
	~PhysicsScene();

	void addActor(PhysicsObject* actor);
	bool removeActor(PhysicsObject* actor);
	void update(float dt);
	void updateGizmos();
	void debugScene();

	void setGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	glm::vec2 getGravity() const { return m_gravity; }

	void setTimeStep(const float timeStep) { m_timeStep = timeStep; }
	float getTimeStep() const { return m_timeStep; }

	void checkForCollision();

	static bool Line2Line(PhysicsObject*, PhysicsObject*);
	static bool Line2Circle(PhysicsObject*, PhysicsObject*);
	static bool Line2Rect(PhysicsObject*, PhysicsObject*);
	static bool Circle2Line(PhysicsObject*, PhysicsObject*);
	static bool Circle2Circle(PhysicsObject*, PhysicsObject*);
	static bool Circle2Rect(PhysicsObject*, PhysicsObject*);
	static bool Rect2Circle(PhysicsObject*, PhysicsObject*);
	static bool Rect2Rect(PhysicsObject*, PhysicsObject*);
	static bool Rect2Line(PhysicsObject*, PhysicsObject*);
	
protected:
	glm::vec2 m_gravity;
	glm::vec2 m_velocity;
	glm::vec2 m_normal;
	float overlap;
	float m_timeStep;
	std::vector<PhysicsObject*> m_actors;
};

