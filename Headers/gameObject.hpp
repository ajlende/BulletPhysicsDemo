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

#include <glm/glm.hpp>

#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <BulletCollision/CollisionShapes/btCollisionShape.h>
#include <LinearMath/btMotionState.h>
#include <LinearMath/btVector3.h>
#include <LinearMath/btScalar.h>
#include <LinearMath/btQuaternion.h>

#include "mesh.hpp"
#include "shader.hpp"

namespace ComS342 {
    
    class GameObject {
    protected:
        // For Drawing
        Mesh*   mesh;
        Shader* shader;
        
        // Bullet -> glm
        glm::vec3 position;
        glm::quat orientation;
        float scale;
        
        // For Physics
        btRigidBody*      body;
        btMotionState*    motionState;
        btCollisionShape* shape;
        btScalar mass;

    public:
        GameObject(Mesh* mesh, Shader* shader, btScalar mass, float scale, const btVector3& position, const btQuaternion& orientation, btCollisionShape* shape);
        ~GameObject();
        inline btRigidBody* getBody() { return body; }
        void draw(glm::mat4 const & viewMatrix, glm::mat4 const & projectionMatrix);
    };
    
}

#endif /* RIGID_OBJECT_HPP */
