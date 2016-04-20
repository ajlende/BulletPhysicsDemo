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
#include "keva.hpp"

namespace ComS342 {
    class KEVAPlank : public GameObject {
    public:
        KEVAPlank(const btVector3& position, const btQuaternion& orientation) :
        GameObject(new Mesh("keva-plank.dae"), new Shader(), 5, 1, position,
                      orientation, new btBoxShape(btVector3(0.25, 4.5, 0.75))) {
            (*this->shader).attach("Flat.vert")
            .attach("Flat.frag")
            .link();
        }
        ~KEVAPlank();
    };
}

#endif /* keva_hpp */
