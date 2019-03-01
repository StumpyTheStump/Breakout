#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <glm\ext.hpp>

class PhysicsScene;

class PhysicsSceneApp : public aie::Application {
public:

	PhysicsSceneApp();
	virtual ~PhysicsSceneApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	//virtual void setupContinuousDemo(glm::vec2 startPos, float inclination, float speed, float gravity);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	PhysicsScene* m_physicsScene;
};