//
//  debugDraw.cpp
//  Glitter
//
//  Borrowed from https://github.com/david-sabata/UniversityRacer
//
//

#include <glm/glm.hpp>

#include "debugDraw.hpp"

namespace ComS342 {
    
    void DebugDraw::drawLine(const btVector3& from,const btVector3& to,const btVector3& color)
    {
        glm::vec3 src(from.x(), from.y(), from.z());
        glm::vec3 dst(to.x(), to.y(), to.z());
        glm::vec3 col(color.x(), color.y(), color.z());
        
        LINE l(src, dst, col);    
        lines.push_back(l);
    }
}