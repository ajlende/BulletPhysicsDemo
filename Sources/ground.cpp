//
//  keva.cpp
//  Glitter
//
//  Created by Alex Lende on 4/19/16.
//
//

#include <LinearMath/btVector3.h>
#include <LinearMath/btQuaternion.h>
#include <BulletCollision/CollisionShapes/btBoxShape.h>

#include "shader.hpp"
#include "mesh.hpp"
#include "ground.hpp"

namespace ComS342 {
    Ground::Ground(const btVector3 & position, const btQuaternion & orientation)
    : GameObject(new Mesh("ground.dae"),
                 new Shader(),
                 0, // stationary
                 2, // scale
                 position,
                 orientation,
                 new btBoxShape(btVector3(100.0, 0.4, 100.0))) {
        (*this->shader).attach("Flat.vert")
        .attach("Flat.frag")
        .link();
    }
}