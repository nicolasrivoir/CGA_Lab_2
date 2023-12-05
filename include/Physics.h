#ifndef PHYSICS_H
#define PHYSICS_H

#include "bullet/btBulletDynamicsCommon.h"

class Physics
{

private:
    //Bullet world
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;

    // Create a dynamic sphere
    btCollisionShape* fallShape;
    btDefaultMotionState* fallMotionState;
    btRigidBody* fallRigidBody;
public:

	Physics();
	void CleanUp();
    void Update(float seconds);
    btDiscreteDynamicsWorld* dynamicsWorld;
};

#endif