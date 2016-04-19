//
//  physics.cpp
//  Glitter
//
//  Created by Alex Lende on 4/18/16.
//
// Code sourced in part from:
// - http://irrlicht.sourceforge.net/forum/viewtopic.php?t=39007
// -
//

#include "physics.hpp"

namespace ComS342 {

    Physics::Physics() {
        this->init();
    }

    Physics::Physics(btVector3 gravity) {
        this->init();
        this->dynamicsWorld->setGravity(gravity);
    }

    Physics::Physics(btScalar gravity) {
        this->init();
        this->dynamicsWorld->setGravity(btVector3(0.0, gravity, 0.0));
    }

    Physics::~Physics() {
        delete this->dynamicsWorld;
        delete this->solver;
        delete this->dispatcher;
        delete this->broadphase;
        delete this->configuration;
    }
    
    void Physics::init() {
        this->configuration = new btDefaultCollisionConfiguration();
        this->broadphase    = new btDbvtBroadphase();
        this->dispatcher    = new btCollisionDispatcher(configuration);
        this->solver        = new btSequentialImpulseConstraintSolver();
        this->dynamicsWorld = new btDiscreteDynamicsWorld(this->dispatcher, this->broadphase, this->solver, this->configuration);
    }

    void Physics::addRigidBody(btRigidBody* body) {
        this->dynamicsWorld->addRigidBody(body);
    }

    void Physics::update(btScalar timeStep) {
        this->dynamicsWorld->stepSimulation(timeStep);
    }

}