//
//  physics.hpp
//  Glitter
//
//  Created by Alex Lende on 4/18/16.
//
//

#ifndef PHYSICS_HPP
#define PHYSICS_HPP
#pragma once

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

namespace ComS342 {
    
    class Physics {
    private:
        btDbvtBroadphase*         broadphase;
        btCollisionConfiguration* configuration;
        btCollisionDispatcher*    dispatcher;
        btConstraintSolver*       solver;
        btDynamicsWorld*          dynamicsWorld;
        
        void init();
    
    public:
        Physics(btScalar gravity);
        Physics(btVector3 gravity);
        Physics();
        ~Physics();
        void update(btScalar timeStep);
        void addRigidBody(btRigidBody* body);
        void addSoftBody(btSoftBodyFloatData* body);
        
        // Inline functions
        btDynamicsWorld* getWorld() { return dynamicsWorld; }
    };
    
}

#endif /* PHYSICS_HPP */
