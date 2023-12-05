#include "Application.h"

int main(int argc, char* argv[]) {

	Application app;

	app.mainLoop();

	return 0;
}

//#include "bullet/btBulletDynamicsCommon.h"
//#include <iostream>
//
//int main() {
//    // Initialize Bullet world
//    btBroadphaseInterface* broadphase = new btDbvtBroadphase();
//    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
//    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
//    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
//
//    btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
//    dynamicsWorld->setGravity(btVector3(0, -10, 0));
//
//    // Create ground plane
//    btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
//    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
//    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
//    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
//    dynamicsWorld->addRigidBody(groundRigidBody);
//
//    // Create a dynamic cube
//    btCollisionShape* cubeShape = new btBoxShape(btVector3(1, 1, 1)); // Cube of size 2x2x2
//    btDefaultMotionState* cubeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
//    btScalar cubeMass = 1;
//    btVector3 cubeInertia(0, 0, 0);
//    cubeShape->calculateLocalInertia(cubeMass, cubeInertia);
//    btRigidBody::btRigidBodyConstructionInfo cubeRigidBodyCI(cubeMass, cubeMotionState, cubeShape, cubeInertia);
//    btRigidBody* cubeRigidBody = new btRigidBody(cubeRigidBodyCI);
//    dynamicsWorld->addRigidBody(cubeRigidBody);
//
//    // Create a dynamic sphere
//    btCollisionShape* fallShape = new btSphereShape(1);
//    btDefaultMotionState* fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
//    btScalar mass = 1;
//    btVector3 fallInertia(0, 0, 0);
//    fallShape->calculateLocalInertia(mass, fallInertia);
//    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
//    btRigidBody* fallRigidBody = new btRigidBody(fallRigidBodyCI);
//    dynamicsWorld->addRigidBody(fallRigidBody);
//
//    // Simulation loop
//    for (int i = 0; i < 30; i++) {
//        dynamicsWorld->stepSimulation(1 / 60.f, 10);
//
//        btTransform trans;
//        fallRigidBody->getMotionState()->getWorldTransform(trans);
//        std::cout << "sphere height: " << trans.getOrigin().getY() << std::endl;
//
//        cubeRigidBody->getMotionState()->getWorldTransform(trans);
//        std::cout << "cube height: " << trans.getOrigin().getY() << std::endl;
//    }
//
//    // Clean up
//    dynamicsWorld->removeRigidBody(fallRigidBody);
//    delete fallRigidBody->getMotionState();
//    delete fallRigidBody;
//
//    dynamicsWorld->removeRigidBody(cubeRigidBody);
//    delete cubeRigidBody->getMotionState();
//    delete cubeRigidBody;
//
//    dynamicsWorld->removeRigidBody(groundRigidBody);
//    delete groundRigidBody->getMotionState();
//    delete groundRigidBody;
//
//    delete fallShape;
//    delete cubeShape;
//    delete groundShape;
//
//    delete dynamicsWorld;
//    delete solver;
//    delete dispatcher;
//    delete collisionConfiguration;
//    delete broadphase;
//
//    return 0;
//}

