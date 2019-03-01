#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include "RigidBody.h"
#include "Circle.h"
#include "Line.h"
#include "Rectangle.h"
#include <algorithm>
#include <iostream>
#include <list>

PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0))
{	
}

void PhysicsScene::addActor(PhysicsObject * actor)
{
	m_actors.push_back(actor);
}

bool PhysicsScene::removeActor(PhysicsObject * actor)
{
	for (int i = 0; i < m_actors.size(); ++i)
	{
		if (m_actors[i] == actor)
		{
			m_actors.erase(m_actors.begin() + i);
			return true;
		}
	}
	return false;
}


// Function pointer array for doing collisions
typedef bool(*fn) (PhysicsObject*, PhysicsObject*);

static fn collisionFunctionArray[] =
{
	PhysicsScene::Line2Line, PhysicsScene::Line2Circle, PhysicsScene::Line2Rect,
	PhysicsScene::Circle2Line, PhysicsScene::Circle2Circle, PhysicsScene::Circle2Rect,
	PhysicsScene::Rect2Line, PhysicsScene::Rect2Circle, PhysicsScene::Rect2Rect,
};

void PhysicsScene::checkForCollision()
{
	int actorCount = m_actors.size();

	// Check for collisions against all objects except this one
	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];
			int shapeID1 = object1->getShapeID();
			int shapeID2 = object2->getShapeID();

			int functionIndex = (shapeID1 * SHAPE_COUNT) + shapeID2;
			fn collisionFucntionPtr = collisionFunctionArray[functionIndex];
			if (collisionFucntionPtr != nullptr)
			{
				collisionFucntionPtr(object1, object2);
			}

		}
	}
}

bool PhysicsScene::Line2Line(PhysicsObject * obj1, PhysicsObject * obj2)
{
	return false;
}

bool PhysicsScene::Line2Circle(PhysicsObject *obj1, PhysicsObject * obj2)
{
	return false;
}

bool PhysicsScene::Line2Rect(PhysicsObject *, PhysicsObject *)
{
	return false;
}

bool PhysicsScene::Circle2Line(PhysicsObject * obj1, PhysicsObject * obj2)
{
	Circle *circle = dynamic_cast<Circle*>(obj1);
	Line *line = dynamic_cast<Line*>(obj2);

	if (circle != nullptr && line != nullptr)
	{
		glm::vec2 collisionNormal = line->getNormal();
		float circleToLine = glm::dot(circle->getPosition(), line->getNormal()) - line->getDistance();

		if (circleToLine < 0)
		{
			collisionNormal *= -1;
			circleToLine *= -1;
		}

		float overlap = circle->getRadius() - circleToLine;
		if (overlap > 0)
		{
			
		}
	}
	return false;
}

bool PhysicsScene::Circle2Circle(PhysicsObject * obj1, PhysicsObject * obj2)
{
	Circle *circle1 = dynamic_cast<Circle*>(obj1);
	Circle *circle2 = dynamic_cast<Circle*>(obj2);

	glm::vec2 displacement = circle1->getPosition() - circle2->getPosition();
	glm::vec2 m_normal = glm::normalize(displacement);
	//float overlap = 

	

	if (circle1 != nullptr && circle2 != nullptr)
	{
		glm::vec2 dist = circle1->getPosition() - circle2->getPosition();
		if (glm::length(dist) < (circle1->getRadius() + circle2->getRadius()))
		{



			circle1->resolveCollision(circle2);
			return true;
		}
	}
	return false;
}

bool PhysicsScene::Circle2Rect(PhysicsObject * obj1, PhysicsObject * obj2)
{
	Circle *circle1 = dynamic_cast<Circle*>(obj1);
	Rectangle *rect1 = dynamic_cast<Rectangle*>(obj2);

	if (circle1 != nullptr && rect1 != nullptr)
	{
		glm::vec2 dist = circle1->getPosition() - rect1->getPosition();
		if (glm::length(dist) < circle1->getRadius() + rect1->getSize().x)
		{
			circle1->resolveCollision(rect1);
			
			return true;
		}
	}
	return false;
}

bool PhysicsScene::Rect2Circle(PhysicsObject * obj1, PhysicsObject * obj2)
{
	Rectangle *rect1 = dynamic_cast<Rectangle*>(obj1);
	Circle *circle1 = dynamic_cast<Circle*>(obj2);
	

	if (circle1 != nullptr && rect1 != nullptr)
	{
		glm::vec2 dist = rect1->getPosition() - circle1->getPosition();
		if (glm::length(dist) < rect1->getSize().x + circle1->getRadius())
		{
			rect1->resolveCollision(circle1);

			return true;
		}
	}
	return false;
}

bool PhysicsScene::Rect2Rect(PhysicsObject *, PhysicsObject *)
{
	return false;
}

bool PhysicsScene::Rect2Line(PhysicsObject *, PhysicsObject *)
{
	return false;
}

void PhysicsScene::update(float dt)
{
	static std::list<PhysicsObject*> dirty;
	// Update physics at a fixed time step

	static float accumulatedTime = 0.0f;
	accumulatedTime += dt;

	while (accumulatedTime >= m_timeStep)
	{
		for (auto pActor : m_actors)
		{
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}
		accumulatedTime -= m_timeStep;
	}

	checkForCollision();

	//// check for collisions
	//for (auto pActor : m_actors)
	//{
	//	for (auto pOther : m_actors)
	//	{
	//		if (pActor == pOther)
	//			continue;
	//		if (std::find(dirty.begin(), dirty.end(), pActor) != dirty.end() &&
	//			std::find(dirty.begin(), dirty.end(), pOther) != dirty.end())
	//			continue;

	//		RigidBody* pRigid = dynamic_cast<RigidBody*>(pActor);
	//		if (pRigid->checkCollision(pOther) == true)
	//		{
	//			pRigid->applyForceToActor(dynamic_cast<RigidBody*>(pOther), pRigid->getVelocity() * pRigid->getMass());
	//			dirty.push_back(pRigid);
	//			dirty.push_back(pOther);
	//		}
	//	}
	//}
	//dirty.clear();
}

void PhysicsScene::updateGizmos()
{
	for (auto pActor : m_actors)
	{
		pActor->makeGizmo();
	}
}

void PhysicsScene::debugScene()
{
	int count = 0;
	for (auto pActor : m_actors)
	{
		std::cout << count << " : ";
		pActor->debug();
		count++;
	}
}



PhysicsScene::~PhysicsScene()
{
	for (auto pActor : m_actors)
	{
		delete pActor;
	}
}



