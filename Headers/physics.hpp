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

#include <glad/glad.h>

#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

#include "debugDraw.hpp"
#include "shader.hpp"

#define BIT(x) (1<<(x))

namespace ComS342 {

    enum CollisionTypes {
        COL_NOTHING = 0,   //<Collide with nothing
        COL_BALL = BIT(0), //<Collide with ships
        COL_KEVA = BIT(1), //<Collide with KEVA planks
        COL_WALL = BIT(2), //<Collide with walls
        COL_EVERYTHING = COL_BALL | COL_KEVA | COL_WALL
    };
    
    class Physics {
    private:
        btDbvtBroadphase*         broadphase;
        btCollisionConfiguration* configuration;
        btCollisionDispatcher*    dispatcher;
        btConstraintSolver*       solver;
        btDynamicsWorld*          dynamicsWorld;
        
        DebugDraw* debugDraw;
        Shader* debugShader;
        GLuint vao, vbo[2];
        bool debug;
        
        void init();
    
    public:
        Physics();
        Physics(btScalar gravity);
        Physics(btVector3 gravity);
        
        ~Physics();
        
        void update(btScalar timeStep);
        void addRigidBody(btRigidBody* body);
        void addSoftBody(btSoftBodyFloatData* body);
        
        void toggleDebugWorld();
        void drawLines(std::vector<DebugDraw::LINE> & lines, glm::mat4 const & viewMatrix, glm::mat4 const & projectionMatrix);
        void debugDrawWorld() { this->dynamicsWorld->debugDrawWorld(); }
        
        bool isDebugWorldEnabled() { return debug; }
        DebugDraw* getDebugDraw() { return debugDraw; }
        btDynamicsWorld* getWorld() { return dynamicsWorld; }
    };
    
}

#endif /* PHYSICS_HPP */
