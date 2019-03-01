#include "PhysicsSceneApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Circle.h"
#include "Line.h"
#include "Rectangle.h"
#include <glm\ext.hpp>
#include <Gizmos.h>
#include "PhysicsScene.h"

PhysicsSceneApp::PhysicsSceneApp() {

}

PhysicsSceneApp::~PhysicsSceneApp() {

}

bool PhysicsSceneApp::startup() {
	// increase the 2d line count to maximize the number of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(glm::vec2(0, -10));
	m_physicsScene->setTimeStep(0.01f);

	//glm::vec2 startPos(-60, -40);
	//float inclination = 0.5f;
	//float speed = 30;
	//float radius = 1.0f;
	//float time = 0;
	//float timeStep = 0.2f;

	//glm::vec2 velocity(sinf(inclination) + 0.5f * speed, cosf(inclination) * speed);

	//setupContinuousDemo(startPos, inclination, speed, -9.81f);

	//m_physicsScene->addActor(new Circle(startPos, velocity, 1, radius, glm::vec4(1, 0, 0, 1)));*/


		

	Circle* circle1 = new Circle(glm::vec2(0, -20), glm::vec2(0, 0), 4.0f, 4, glm::vec4(1, 0, 0, 1));
	Circle* circle2 = new Circle(glm::vec2(0, 10), glm::vec2(0, 0), 4.0f, 4, glm::vec4(0, 0, 1, 1));
	Line* line1 = new Line(glm::vec2(90, 0), 1.0f, glm::vec4(1, 1, 1, 1));
	Line* line2 = new Line(glm::vec2(-90, 0), 1.0f, glm::vec4(1, 1, 1, 1));
	Line* line3 = new Line(glm::vec2(0, 50), 1.0f, glm::vec4(1, 1, 1, 1));
	Line* line4 = new Line(glm::vec2(0, -50), 1.0f, glm::vec4(1, 1, 1, 1));
	//Rectangle* rect1 = new Rectangle(glm::vec2(0, 50), glm::vec2(0, 0), 4.0f, glm::vec2(5, 5), glm::vec4(0, 0, 1, 1));




	m_physicsScene->addActor(circle1);
	m_physicsScene->addActor(line1);
	m_physicsScene->addActor(line2);
	m_physicsScene->addActor(line3);
	m_physicsScene->addActor(line4);
	m_physicsScene->addActor(circle2);
	circle1->applyForce(glm::vec2(0, 0));
	circle2->applyForce(glm::vec2(0, 0));

	//circle2->applyForce(glm::vec2(-15, 0));

	circle1->applyForceToActor(circle2, glm::vec2(0, 0));
	return true;
}

void PhysicsSceneApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	delete m_physicsScene;
}

void PhysicsSceneApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();
	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizmos();


	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void PhysicsSceneApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16 / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100,
		-100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}




//void PhysicsSceneApp::setupContinuousDemo(glm::vec2 startPos, float inclination, float speed, float gravity)
//{
//	float time = 0;
//	float timeStep = 0.2f;
//	float radius = 1.0f;
//	int segments = 12;
//	glm::vec4 colour = glm::vec4(1, 1, 0, 1);
//
//	glm::vec2 velocity(sinf(inclination) * speed, cosf(inclination) * speed);
//
//	while (time <= 8)
//	{
//		//velocity.y += gravity * timeStep;
//		//startPos += velocity * timeStep;
//
//		//p = sp  + u * t + 0.5 * a * T *T
//		glm::vec2 position = startPos + velocity * time + 0.5f * glm::vec2(0, gravity) * time * time;
//
//		aie::Gizmos::add2DCircle(position, radius, segments, colour);
//		time += timeStep;
//	}
//}