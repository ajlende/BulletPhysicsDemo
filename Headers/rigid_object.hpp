//
//  rigid_object.hpp
//  Glitter
//
//  Created by Alex Lende on 4/18/16.
//
//

#ifndef RIGID_OBJECT_HPP
#define RIGID_OBJECT_HPP
#pragma once

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <BulletCollision/CollisionShapes/btCollisionShape.h>

#include "mesh.hpp"

namespace ComS342 {
    
    class RigidObject {
    private:
        Mesh* mesh;
        btRigidBody*      body;
        btMotionState*    motionState;
        btCollisionShape* collisionShape;
        btVector3*        position;
        btQuaternion*     orientation;
        btScalar scale;
        btScalar mass;
        
        void init();

    public:
        RigidObject(btScalar mass, btScalar scale) {
            this->mass = mass;
            this->scale = scale;
        }
        virtual ~RigidObject();
    };
    
}

#endif /* RIGID_OBJECT_HPP */
