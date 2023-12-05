#include "Physics.h"
#include <iostream>

Physics::Physics() {

    // Initialize Bullet world
    broadphase = new btDbvtBroadphase();
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    solver = new btSequentialImpulseConstraintSolver;

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0, -10, 0));

    // Create ground plane
    btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
    dynamicsWorld->addRigidBody(groundRigidBody);

    // Create a dynamic cube
    //btCollisionShape* cubeShape = new btBoxShape(btVector3(1, 1, 1)); // Cube of size 2x2x2
    //btDefaultMotionState* cubeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
    //btScalar cubeMass = 1;
    //btVector3 cubeInertia(0, 0, 0);
    //cubeShape->calculateLocalInertia(cubeMass, cubeInertia);
    //btRigidBody::btRigidBodyConstructionInfo cubeRigidBodyCI(cubeMass, cubeMotionState, cubeShape, cubeInertia);
    //btRigidBody* cubeRigidBody = new btRigidBody(cubeRigidBodyCI);
    //dynamicsWorld->addRigidBody(cubeRigidBody);

    // Create a dynamic sphere
    //fallShape = new btSphereShape(1);
    //fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
    //btScalar mass = 1;
    //btVector3 fallInertia(0, 0, 0);
    //fallShape->calculateLocalInertia(mass, fallInertia);
    //btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
    //fallRigidBody = new btRigidBody(fallRigidBodyCI);
    //dynamicsWorld->addRigidBody(fallRigidBody);

}

void Physics::Update(float seconds) {
    dynamicsWorld->stepSimulation(seconds, 10);

    //btTransform trans;
    //fallRigidBody->getMotionState()->getWorldTransform(trans);
    //std::cout << "sphere height: " << trans.getOrigin().getY() << std::endl;

    //cubeRigidBody->getMotionState()->getWorldTransform(trans);
    //std::cout << "cube height: " << trans.getOrigin().getY() << std::endl;  
}

void Physics::CleanUp() {
    // Clean up
    //dynamicsWorld->removeRigidBody(fallRigidBody);
    //delete fallRigidBody->getMotionState();
    //delete fallRigidBody;

    //dynamicsWorld->removeRigidBody(cubeRigidBody);
    //delete cubeRigidBody->getMotionState();
    //delete cubeRigidBody;

    //dynamicsWorld->removeRigidBody(groundRigidBody);
    //delete groundRigidBody->getMotionState();
    //delete groundRigidBody;

    //delete fallShape;
    //delete cubeShape;
    //delete groundShape;

    delete dynamicsWorld;
    delete solver;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;
}