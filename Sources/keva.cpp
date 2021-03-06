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
#include "keva.hpp"

namespace ComS342 {
    KEVAPlank::KEVAPlank(const btVector3 & position, const btQuaternion & orientation)
    : GameObject(new Mesh("keva-plank.dae"),
                 new Shader(),
                 5, // mass
                 1, // scale
                 position,
                 orientation,
                 new btBoxShape(btVector3(0.25, 0.75, 4.5))) {
        (*this->shader).attach("Flat.vert")
        .attach("Flat.frag")
        .link();
    }
}