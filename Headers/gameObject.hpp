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

#include "mesh.hpp"
#include "shader.hpp"

namespace ComS342 {
    
    class GameObject {
    protected:
        // For Drawing
        Mesh*   mesh;
        Shader* shader;
        
        glm::vec3 position;
        glm::vec3 axis;
        float angle;
        float scale;
        
        // For Physics
        btRigidBody*      body;
        btMotionState*    motionState;
        btCollisionShape* shape;
        btScalar mass;
        
        void init();

    public:
        GameObject(Mesh* mesh, Shader* shader, btScalar mass, float scale, const btVector3& position, const btQuaternion& orientation, btCollisionShape* shape);
        ~GameObject();
        
        inline btRigidBody* getBody() {
            return body;
        }
        
        void draw(glm::mat4 const & viewMatrix, glm::mat4 const & projectionMatrix);
        
    };
    
}

#endif /* RIGID_OBJECT_HPP */
