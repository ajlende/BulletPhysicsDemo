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

#include <iostream>

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <BulletCollision/CollisionShapes/btCollisionShape.h>
#include <BulletCollision/CollisionShapes/btEmptyShape.h>

#include "mesh.hpp"
#include "shader.hpp"

namespace ComS342 {
    
    class PhysicsObject {
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
        PhysicsObject(Mesh* mesh, Shader* shader, btScalar mass = 0, float scale = 1, const btVector3& position = btVector3(0,0,0), const btQuaternion& orientation = btQuaternion::getIdentity(), btCollisionShape* shape = nullptr) {
            this->mesh = mesh;
            this->shader = shader;
            
            this->mass  = mass;
            this->scale = scale;
            
            this->shape = (shape != nullptr) ? shape : new btEmptyShape();
            
            this->motionState = new btDefaultMotionState(btTransform(orientation, position));
            
            btRigidBody::btRigidBodyConstructionInfo constructionInfo(
                this->mass,        // mass > 0 will move and mass == 0 will not be affected by physical forces (ex. gravity)
                this->motionState, // initial position information
                this->shape,       // collision shape of the body
                btVector3(0,0,0)); // local inertia
            
            this->body = new btRigidBody(constructionInfo);
        }
        
        ~PhysicsObject() {
            delete body;
            delete shape;
            delete motionState;
            delete mesh;
            delete shader;
        }
        
        btRigidBody* getBody() {
            return body;
        }
        
        void update() {
            
        }
        
        void draw(glm::mat4 const & viewMatrix, glm::mat4 const & projectionMatrix) {
            
            btScalar btAngle = body->getOrientation().getAngle();
            btVector3 btAxis = body->getOrientation().getAxis();
            btVector3 btPos = body->getCenterOfMassPosition();
            
            angle = (float)btAngle;
            axis = glm::vec3(btAxis.getX(), btAxis.getY(), btAxis.getZ());
            position = glm::vec3(btPos.getX(), btPos.getY(), btPos.getZ());
            
            std::cout << position.x << " " << position.y << " " << position.z << std::endl;

            auto modelMatrix = glm::mat4(1.0);
            modelMatrix = glm::translate(modelMatrix, position);
            modelMatrix = glm::rotate(modelMatrix, angle, axis);
            modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));
            
            shader->activate();
            
            shader->bind("model", modelMatrix);
            shader->bind("view", viewMatrix);
            shader->bind("projection", projectionMatrix);
            
            mesh->draw(shader->get());
            
            shader->deactivate();
        }
        
    };
    
}

#endif /* RIGID_OBJECT_HPP */
