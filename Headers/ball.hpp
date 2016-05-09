//
//  ball.hpp
//  Glitter
//
//  Created by Alex Lende on 4/20/16.
//
//

#ifndef BALL_HPP
#define BALL_HPP

#include <btBulletCollisionCommon.h>

#include "gameObject.hpp"

namespace ComS342 {
    class Ball : public GameObject {
    public:
        Ball(const btVector3 & position, const btQuaternion & orientation);
        ~Ball();
    };
}

#endif /* BALL_HPP */
