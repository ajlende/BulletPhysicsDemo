//
//  physics.cpp
//  Glitter
//
//  Created by Alex Lende on 4/18/16.
//
// Code sourced in part from:
// - http://irrlicht.sourceforge.net/forum/viewtopic.php?t=39007
// - http://bulletphysics.org/Bullet/phpBB3/viewtopic.php?t=10071
// - 
//
//

#include "debugDraw.hpp"
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
        delete this->debugShader;
    }
    
    void Physics::init() {
        this->configuration = new btDefaultCollisionConfiguration();
        this->broadphase    = new btDbvtBroadphase();
        this->dispatcher    = new btCollisionDispatcher(configuration);
        this->solver        = new btSequentialImpulseConstraintSolver();
        this->dynamicsWorld = new btDiscreteDynamicsWorld(this->dispatcher, this->broadphase, this->solver, this->configuration);
        
        this->debugDraw     = new DebugDraw();
        this->dynamicsWorld->setDebugDrawer(this->debugDraw);
        this->debug = false;
        
        this->toggleDebugWorld();
        
        this->debugShader = new Shader();
        (*this->debugShader).attach("Line.vert").attach("Line.frag").link();
    }

    void Physics::addRigidBody(btRigidBody* body) {
        this->dynamicsWorld->addRigidBody(body);
    }

    void Physics::update(btScalar timeStep) {
        this->dynamicsWorld->stepSimulation(timeStep);
    }
    
    void Physics::toggleDebugWorld() {
        debug = !debug;
        if (debug) {
            this->debugDraw->setDebugMode(btIDebugDraw::DBG_DrawWireframe |
                                          btIDebugDraw::DBG_DrawAabb);
        } else {
            this->debugDraw->setDebugMode(btIDebugDraw::DBG_NoDebug);
        }
    }
    
    void Physics::drawLines(std::vector<DebugDraw::LINE> & lines, glm::mat4 const & viewMatrix, glm::mat4 const & projectionMatrix) {
        glDisable(GL_CULL_FACE);
        
        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;
        unsigned int indexI = 0;
        
        for (std::vector<DebugDraw::LINE>::iterator it = lines.begin(); it != lines.end(); it++) {
            DebugDraw::LINE l = (*it);
            vertices.push_back(l.a.x);
            vertices.push_back(l.a.y);
            vertices.push_back(l.a.z);
            
            vertices.push_back(l.b.x);
            vertices.push_back(l.b.y);
            vertices.push_back(l.b.z);
            
            indices.push_back(indexI);
            indices.push_back(indexI + 1);
            indexI += 2;
        }
        
        auto shaderProg = debugShader->get();
        
        auto normalAttrib = glGetAttribLocation(shaderProg, "normal");
        auto uvAttrib = glGetAttribLocation(shaderProg, "uv");
        glDisableVertexAttribArray(normalAttrib);
        glDisableVertexAttribArray(uvAttrib);
        
        auto positionAttrib = glGetAttribLocation(shaderProg, "position");
        glEnableVertexAttribArray(positionAttrib);
        glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, 0, (void*)&(vertices.at(0)));
        
        glm::mat4 modelMatrix(1.0);
        debugShader->bind("model", modelMatrix);
        debugShader->bind("view", viewMatrix);
        debugShader->bind("projection", projectionMatrix);

        glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, (void*)&(indices.at(0)));
        
        lines.clear();
        
        debugShader->deactivate();
    }
}