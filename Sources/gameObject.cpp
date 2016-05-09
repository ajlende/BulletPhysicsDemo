//
//  gameObject.cpp
//  Glitter
//
//  Created by Alex Lende on 4/20/16.
//
//

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <BulletCollision/CollisionShapes/btCollisionShape.h>
#include <BulletCollision/CollisionShapes/btEmptyShape.h>

#include "mesh.hpp"
#include "shader.hpp"

#include "gameObject.hpp"

namespace ComS342 {
    // For converting beween Bullet and GLM
    glm::mat4 convertBulletTransformToGLM(btTransform& transform) {
        float data[16];
        transform.getOpenGLMatrix(data);
        return glm::make_mat4(data);
    }
    
    btTransform convertGLMTransformToBullet(glm::mat4 transform) {
        const float* data = glm::value_ptr(transform);
        btTransform bulletTransform;
        bulletTransform.setFromOpenGLMatrix(data);
        return bulletTransform;
    }
    
    btVector3 convertGLMVectorToBullet(glm::vec3 vector) {
        return btVector3(vector.x,vector.y,vector.z);
    }
    
    glm::vec3 convertBulletVectorToGLM(btVector3 vector) {
        return glm::vec3(vector.getX(),vector.getY(),vector.getZ());
    }
    
    glm::quat convertBulletQuaternionToGLM(btQuaternion quaternion) {
        return glm::quat(quaternion.getW(), quaternion.getX(), quaternion.getY(), quaternion.getZ());
    }
    
    GameObject::GameObject(Mesh* mesh, Shader* shader, btScalar mass = 0, float scale = 1, const btVector3& position = btVector3(0,0,0), const btQuaternion& orientation = btQuaternion::getIdentity(), btCollisionShape* shape = nullptr) {
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
    
    GameObject::~GameObject() {
        delete body;
        delete shape;
        delete motionState;
        delete mesh;
        delete shader;
    }
    
    void GameObject::draw(glm::mat4 const & viewMatrix, glm::mat4 const & projectionMatrix) {
        
        // Convert body info into something usable by OpenGL
        orientation = convertBulletQuaternionToGLM(body->getOrientation());
        position = convertBulletVectorToGLM(body->getCenterOfMassPosition());
        
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, position);
        modelMatrix = glm::mat4_cast(orientation) * modelMatrix;
        modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));
        
        shader->activate();
        
        shader->bind("model", modelMatrix);
        shader->bind("view", viewMatrix);
        shader->bind("projection", projectionMatrix);
        
        mesh->draw(shader->get());
        
        shader->deactivate();
    }

}