//
//  ball.cpp
//  Glitter
//
//  Created by Alex Lende on 4/20/16.
//
//


#include <LinearMath/btVector3.h>
#include <LinearMath/btQuaternion.h>
#include <BulletCollision/CollisionShapes/btSphereShape.h>

#include "shader.hpp"
#include "mesh.hpp"
#include "ball.hpp"

#define RADIUS 5

namespace ComS342 {
    Ball::Ball(const btVector3 & position, const btQuaternion & orientation)
    : GameObject(new Mesh("ball.dae"),
                 new Shader(),
                 10,     // mass
                 RADIUS, // scale
                 position,
                 orientation,
                 new btSphereShape(RADIUS*0.75)) {
        (*this->shader).attach("Phong.vert")
        .attach("Phong.frag")
        .link();
    }
}