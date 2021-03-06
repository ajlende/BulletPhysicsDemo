//
//  keva.hpp
//  Glitter
//
//  Created by Alex Lende on 4/19/16.
//
//

#ifndef keva_hpp
#define keva_hpp

#include <BulletCollision/CollisionShapes/btBoxShape.h>

#include "gameObject.hpp"

namespace ComS342 {
    class KEVAPlank : public GameObject {
    public:
        KEVAPlank(const btVector3 & position, const btQuaternion & orientation);
        ~KEVAPlank();
    };
}

#endif /* keva_hpp */
