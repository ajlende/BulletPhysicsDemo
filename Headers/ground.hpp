//
//  keva.hpp
//  Glitter
//
//  Created by Alex Lende on 4/19/16.
//
//

#ifndef ground_hpp
#define ground_hpp

#include <BulletCollision/CollisionShapes/btBoxShape.h>

#include "gameObject.hpp"

namespace ComS342 {
    class Ground : public GameObject {
    public:
        Ground(const btVector3 & position, const btQuaternion & orientation);
        ~Ground();
    };
}

#endif /* ground_hpp */
